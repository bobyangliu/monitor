#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

/* 服务器程序监听的端口号 */
#define PORT 4000
/* 我们一次所能够接收的最大字节数 */
#define MAXDATASIZE 43770
int main(int argc, char *argv[])
{
	
	int sockfd, numbytes;/* 套接字描述符 */
	char buf[MAXDATASIZE];
	struct hostent *he;
	struct sockaddr_in their_addr;/* 连接者的主机信息 */
	
	if ((he=gethostbyname("127.0.0.1")) == NULL)/* 取得主机信息 */
	{
		/* 如果 gethostbyname()发生错误,则显示错误信息并退出 */
		perror("gethostbyname");
		exit(1);
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
	{
		perror("socket");/* 如果 socket()调用出现错误则显示错误信息并退出 */
		exit(1);
	}
	
	their_addr.sin_family = AF_INET;/* 主机字节顺序 */	
	their_addr.sin_port = htons(PORT);/* 网络字节顺序,短整型 */
	their_addr.sin_addr = *((struct in_addr *)he->h_addr);	
	bzero(&(their_addr.sin_zero), 8);/* 将结构剩下的部分清零*/
	
	if(connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1)
	{
		perror("connect");/* 如果 connect()建立连接错误,则显示出错误信息,退出 */
		exit(1);
	}
	

	FILE *fp;
	static int num = 0;
	char picture_name[20];
	int over = 1;

	sprintf(picture_name,"picture%d.jpg",num ++);

	if((fp = fopen(picture_name,"w")) == NULL)
	{
		perror("Fail to fopen");
		exit(EXIT_FAILURE);
	}
	while(over)
	{
		if((numbytes=recv(sockfd, buf, MAXDATASIZE, 0)) == -1)
		{
			perror("recv");/* 如果接收数据错误,则显示错误信息并退出 */
			exit(1);
		}
		if (numbytes < MAXDATASIZE)
		{
			over = 0;/* code */
		}

		fwrite(buf,numbytes,1,fp);
		memset(buf, 0, sizeof(buf));
	}	
	//usleep(500);
	fclose(fp);
	printf("Received data size: %d\n",numbytes);
	close(sockfd);
	return 0;
}
