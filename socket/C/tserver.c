#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <pthread.h>

#define SERV_PORT 4508
#define BACKLOG 10
#define DATA_MAX 1024

void *config_thread(void *);

char buf[DATA_MAX] = {"UsrFileAccRight:MyFiles,rwxd;\nFileCtrlFld:MyFiles:/home/zhangsan/file1.txt;\nFileCtrlFld:/home/zhangsan/file2.doc,/home/zhangsan/Designs;"};

int main()
{
	int sockfd, client_fd, sin_size;
	struct sockaddr_in my_addr;
	struct sockaddr_in remote_addr;
        pthread_t tid;

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
	
		printf("socket error!\n");
		exit(1);
	}

	memset(&my_addr, 0, sizeof(struct sockaddr_in));
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(SERV_PORT);
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(sockfd, (struct sockaddr *)&my_addr, 
				sizeof(struct sockaddr_in)) == -1) {
	
		printf("bind error!\n");
		exit(1);
	}

	if(listen(sockfd, BACKLOG) == -1) {
	
		printf("listen error!\n");
		exit(1);
	}

	while(1) {
		sin_size = sizeof(struct sockaddr_in);
		if ((client_fd = accept(sockfd, (struct sockaddr *)&remote_addr,
						&sin_size)) == -1) {
			printf("accept error!\n");
			continue;
		}
		printf("Server received a connection from: %s\n", inet_ntoa(remote_addr.sin_addr));

		if (pthread_create(&tid, NULL, (void *)config_thread, (void *)&client_fd) != 0) {
			printf("Thread creation failed\n");
			exit(1);
		}
	}

	return 0;
}

void *config_thread(void *arg)
{
	int *client_fd = (int *)arg;
	int d = 5;

	while(1) {
		if (send(*client_fd, buf, sizeof(buf), 0) == -1) {
			printf("send error!\n");
			exit(1);
		}

		if (recv(*client_fd, buf, DATA_MAX, 0) < 0) {
			printf("recvbuf error!\n");
			exit(1);
		} else {
			if(strcmp(buf, "exit") == 0) {
            			printf("buf!!:%s\n", buf);
				break;
		        } else {
				printf("recvbuf: %s\n", buf);
			}
		}
	}

		close(client_fd);
		exit(0);
}

