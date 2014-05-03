#include "server.h"

int serverInit( int myPort )
{
	int sock_fd;
	struct sockaddr_in my_addr;

	if((sock_fd=socket(AF_INET, SOCK_STREAM, 0)) == -1)/* 这里就是我们一直强调的错误检查.如果调用 socket() 出错,则返回 */ 
	{
		perror("socket");/* 输出错误提示并退出 */
		exit(1);
	}
	
	my_addr.sin_family = AF_INET;/* 主机字节顺序 */	
	my_addr.sin_port = htons(myPort)/* 网络字节顺序,短整型 */;	
	my_addr.sin_addr.s_addr = INADDR_ANY;/* 将运行程序机器的 IP 填充入 s_addr */	
	bzero(&(my_addr.sin_zero), 8);/* 将此结构的其余空间清零 */

	if (bind(sock_fd, (struct sockaddr *)&my_addr,sizeof(struct sockaddr)) == -1)
	{
		perror("bind");/* 如果调用 bind()失败,则给出错误提示,退出 */
		exit(1);
	}
	if (listen(sock_fd, BACKLOG) == -1)
	{
		perror("listen");/* 如果调用 listen 失败,则给出错误提示,退出 */
		exit(1);
	}

	return sock_fd;
}



// void main()
// {
	
// 	int sock_fd;
// 	pthread_t threadAccept;
// 	void *acceptThreadRtn;

// 	sock_fd = serverInit(MYPORT);

// 	pthread_create(&threadAccept, NULL, acceptThread, (void *)&sock_fd);
// 	if(pthread_join(threadAccept, &acceptThreadRtn))
// 	{
// 		printf("accept thread quit return 1\n");
// 	}
// 	else
// 	{
// 		printf("accept thread quit return 0\n");
// 	}

// }
