#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>


void my_err1(int error)
{
	printf("error:  %s with errno: %d\n",strerror(error),error);
//	exit(1);
}

void my_err2(const char* err_string,int line)
{
	fprintf(stderr,"error:  line:%d ",line);
	perror(err_string);
//	exit(1);
}
void my_err3(const char* err_string,int line,int error)
{
	printf("error:  line:%d %s():%s with errno:%d\n",line,err_string,strerror(error),error);
//      exit(1);
}


int main()
{
	int fd;
	if((fd=open("example_test.c",O_CREAT|O_EXCL,S_IRUSR|S_IWUSR))==-1)
	{
		my_err1(errno);
		my_err2("open",__LINE__);
		my_err3("open",__LINE__,errno);
	}
	close(fd);
	return 0;
}
