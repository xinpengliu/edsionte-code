#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <asm/io.h>
#include <asm/system.h>
#include <asm/uaccess.h>

#define GLOBALMEM_SIZE 0x1000
#define MEM_CLEAR 0x1
#define GLOBALMEM_MAJOR 0/*预设的globalmem的主设备号*/

static int globalmem_major=GLOBALMEM_MAJOR;
/*globalmem设备结构体*/
struct globalmem_dev
{
	struct cdev cdev;
	unsigned char mem[GLOBALMEM_SIZE];/*全局内存*/
};

struct globalmem_dev* globalmem_devp;
/*文件打开函数*/
int globalmem_open(struct inode *inode, struct file *filp)
{
  /*将设备结构体指针赋值给文件私有数据指针*/
  printk("open the file..\n");
  filp->private_data = globalmem_devp;
  return 0;
}
/*文件释放函数*/
int globalmem_release(struct inode *inode, struct file *filp)
{
  return 0;
}

/*ioctl设备控制函数*/
static int globalmem_ioctl(struct inode *inodep, struct file *filp, unsigned
  int cmd, unsigned long arg)
{
  struct globalmem_dev *dev = filp->private_data;/*获得设备结构体指针*/

  switch (cmd)
  {
    case MEM_CLEAR:
      memset(dev->mem, 0, GLOBALMEM_SIZE);      
      printk(KERN_INFO "globalmem is set to zero\n");
      break;

    default:
      return  - EINVAL;
  }
  return 0;
}

/*读函数*/
static ssize_t globalmem_read(struct file *filp, char __user *buf, size_t size,
  loff_t *ppos)
{
  unsigned long p =  *ppos;
  unsigned int count = size;
  int ret = 0;
  struct globalmem_dev *dev = filp->private_data; /*获得设备结构体指针*/

  /*分析获取有效的写长度*/
  if (p >= GLOBALMEM_SIZE)
    return count ?  - ENXIO: 0;
  if (count > GLOBALMEM_SIZE - p)
    count = GLOBALMEM_SIZE - p;

  /*从内核空间向用户空间写数据*/
  if (copy_to_user(buf, (void*)(dev->mem + p), count))
  {
    ret =  - EFAULT;
  }
  else
  {
    *ppos += count;
    ret = count;
    
    printk(KERN_INFO "read %d bytes(s) from %d\n", count, p);
  }

  return ret;
}

/*写函数*/
static ssize_t globalmem_write(struct file *filp, const char __user *buf,
  size_t size, loff_t *ppos)
{
  unsigned long p =  *ppos;
  unsigned int count = size;
  int ret = 0;
  struct globalmem_dev *dev = filp->private_data; /*获得设备结构体指针*/
  
  /*分析和获取有效的写长度*/
  if (p >= GLOBALMEM_SIZE)
    return count ?  - ENXIO: 0;
  if (count > GLOBALMEM_SIZE - p)
    count = GLOBALMEM_SIZE - p;
    
  /*从用户空间向内核空间写数据*/
  if (copy_from_user(dev->mem + p, buf, count))
    ret =  - EFAULT;
  else
  {
    *ppos += count;
    ret = count;
    
    printk(KERN_INFO "written %d bytes(s) from %d\n", count, p);
  }

  return ret;
}

/* seek文件定位函数*/
static loff_t globalmem_llseek(struct file *filp, loff_t offset, int orig)
{
  loff_t ret = 0;
  switch (orig)
  {
    case 0:   /*相对文件开始位置便宜*/
      if (offset < 0)
      {
        ret =  - EINVAL;
        break;
      }
      if ((unsigned int)offset > GLOBALMEM_SIZE)
      {
        ret =  - EINVAL;
        break;
      }
      //f_pos文件当前的读写位置
      //SEEK_SET
      filp->f_pos = (unsigned int)offset;
      ret = filp->f_pos;
      break;
    case 1:   /*相对文件当前位置偏移*/
      if ((filp->f_pos + offset) > GLOBALMEM_SIZE)
      {
        ret =  - EINVAL;
        break;
      }
      if ((filp->f_pos + offset) < 0)
      {
        ret =  - EINVAL;
        break;
      }
      /*SEEK_CUR*/
      filp->f_pos += offset;
      ret = filp->f_pos;
      break;
    default:
      ret =  - EINVAL;
      break;
  }
  return ret;
}

/*文件操作结构体*/
static const struct file_operations globalmem_fops =
{
  .owner = THIS_MODULE,
  .llseek = globalmem_llseek,
  .read = globalmem_read,
  .write = globalmem_write,
  .ioctl = globalmem_ioctl,
  .open = globalmem_open,
  .release = globalmem_release,
};

void globalmem_setup_cdev(struct globalmem_dev *dev,int index)
{
	int err;
	int devno=MKDEV(globalmem_major,index);

	cdev_init(&dev->cdev,&globalmem_fops);
	dev->cdev.owner=THIS_MODULE;
	dev->cdev.ops=&globalmem_fops;
	err=cdev_add(&dev->cdev,devno,1);
	if(err)
	{
		printk(KERN_NOTICE "ERROR %d adding LED%D",err,index);
	}
}

/*字符设备驱动加载函数*/
static int __init globalmem_init(void)
{
	int result;
	dev_t devno=MKDEV(globalmem_major,0);

	/*申请设备号*/
	if(globalmem_major)
	{
		result=register_chrdev_region(devno,1,"globalmem");
	}
	else
	{
		result=alloc_chrdev_region(&devno,0,1,"globalmem");
		globalmem_major=MAJOR(devno);
	}
	if(result<0)
	{
		return result;
	}
	printk("The character device's number:%d\n",MAJOR(devno));
	/*动态申请设备结构体的内存*/
	globalmem_devp=kmalloc(sizeof(struct globalmem_dev),GFP_KERNEL);
	if(!globalmem_devp)
	{
		result=-ENOMEM;
		goto fail_malloc;
	}

	memset(globalmem_devp,0,sizeof(struct globalmem_dev));

	globalmem_setup_cdev(globalmem_devp,0);
	return 0;
fail_malloc: unregister_chrdev_region(devno,1);
	return result;
}

static void __exit globalmem_exit(void)
{
	cdev_del(&globalmem_devp->cdev);
	kfree(globalmem_devp);
	unregister_chrdev_region(MKDEV(globalmem_major,0),1);
}

MODULE_LICENSE("GPL");
module_init(globalmem_init);
module_exit(globalmem_exit);
