#include "server.h"
#include "camera.h"
#include "camptureServer.h"

//void *camptureThread(void *args)
//{
//	struct globData *data = (struct globData *)args;
//
//	while(data->isRun)
//	{
//		if(!read_frame(data))
//		{
//			pthread_mutex_lock(&(data->capture_lock));
//			memcpy(data->sendBuf->start, data->tmpBuf->start, data->tmpBuf->length);
//			pthread_cond_signal(&(data->capture_cond));
//			pthread_mutex_unlock(&(data->capture_lock));
//			break;
//		}
//	}
//
//	pthread_exit(0);//return 0;
//}
 void *camptureThread(void *args)
 {
 	struct globData *data = (struct globData *)args;
 	int count = 1;

 	fd_set fds;
 	struct timeval tv;
 	int r;

 	while(data->isRun)
 	{
 		for(;;)
 		{
 			FD_ZERO(&fds);
 			FD_SET(data->camera_fd, &fds);

 			/*Timeout*/
 			tv.tv_sec = 2;
 			tv.tv_usec = 0;

 			r = select(data->camera_fd + 1, &fds, NULL, NULL, &tv);

 			if(-1 == r)
 			{
 				if(EINTR == errno)
 					continue;

 				perror("Fail to select");
 				//pthread_exit(1);
 				return NULL;
 			}

 			if(0 == r)
 			{
 				fprintf(stderr,"select Timeout\n");
 				pthread_mutex_lock(&(data->capture_lock));
 				pthread_cond_signal(&(data->capture_cond));
 				pthread_mutex_unlock(&(data->capture_lock));
 				return NULL;
 			}

 			if(!read_frame(data))
 			{
 				//printf("start to copy the frame data to send buffer!\n");
 				pthread_mutex_lock(&(data->capture_lock));
 				memcpy(data->sendBuf->start, data->tmpBuf->start, data->tmpBuf->length);
 				pthread_cond_signal(&(data->capture_cond));
 				pthread_mutex_unlock(&(data->capture_lock));
 				//printf("copy frame data is complete!\n");
 				break;
 			}

 		}
 	}
 	pthread_exit(0);//return 0;
 }
//void *childThread(void *args)
//{
//	globData *glob = (globData *)args;
//	/* 这里是 thread */
//	pthread_mutex_lock(&glob->capture_lock);
//	pthread_cond_wait(&glob->capture_cond, &glob->capture_lock);
//
//	if (send(*(int *)new_fd, tmpbuf->start, tmpbuf->length, 0) == -1)
//	{
//		perror("send");/* 如果错误,则给出错误提示,然后关闭这个新连接,退出 */
//		close(*(int *)new_fd);
//		exit(0);
//	}
//
//	pthread_mutex_unlock(&capture_lock);
//
//	close(*(int *)new_fd);/* 关闭 new_fd 代表的这个套接字连接 */
//
//	pthread_exit(0);
//
//}

void *acceptThread(void *args)
{
	int sin_size;
	int new_fd;
	int send_size;
	struct sockaddr_in their_addr;/* 连接者的地址信息*/
	pthread_t threadChild;//同时发起几个链接时有问题
	void *childThreadRtn;
	struct globData *glob = (struct globData *)args;

	sin_size = sizeof(struct sockaddr_in);

	if ((new_fd = accept(glob->sock_fd, (struct sockaddr *)&their_addr, &sin_size)) == -1)
	{
		perror("accept");/* 如果调用 accept()出现错误,则给出错误提示,进入下一个循环 */
	}
	close(glob->sock_fd);
	printf("server: got connection from %s\n", inet_ntoa(their_addr.sin_addr));/* 服务器给出出现连接的信息 */

	while(1)
	{
		printf("send frame size : %d \n", glob->sendBuf->length);
//		pthread_create(&threadChild, NULL, childThread, (void *)&new_fd);
		pthread_mutex_lock(&glob->capture_lock);
		pthread_cond_wait(&glob->capture_cond, &glob->capture_lock);
		printf("start send the buf data!\n");
		if ((send_size = send(new_fd, glob->sendBuf->start, glob->sendBuf->length, 0)) == -1)
		{
			perror("send");/* 如果错误,则给出错误提示,然后关闭这个新连接,退出 */
			pthread_mutex_unlock(&glob->capture_lock);
			break;
		}
		printf("send size: %d\n", send_size);
		pthread_mutex_unlock(&glob->capture_lock);
		usleep(50);
		if (4 == recv(new_fd, glob->control, 4, 0))
		{
			printf("recv: %s", glob->control);

			continue;
		}

		break;
	}
	glob->isRun = 0;
	close(new_fd);
	pthread_exit(0);
}

int main(int args, char *argv[])
{

	struct globData globargs;
	memset(&globargs, 0, sizeof(globargs));

	captureInit(&globargs);
	globargs.isRun = 1;
	globargs.sock_fd = serverInit(MYPORT);

	pthread_mutex_init(&(globargs.capture_lock), NULL);
	pthread_cond_init(&(globargs.capture_cond), NULL);

	pthread_create(&globargs.threadAccept, NULL, acceptThread, (void *)&globargs);
	pthread_create(&globargs.threadCapture, NULL, camptureThread, (void *)&globargs);
	
	if(pthread_join(globargs.threadAccept, &globargs.acceptThreadRtn))
	{
		close(globargs.sock_fd);
		printf("accept thread quit return 1\n");
	}
	else
	{
		close(globargs.sock_fd);
		printf("accept thread quit return 0\n");
	}

	if(pthread_join(globargs.threadCapture, &globargs.camptureThreadRtn))
	{
		printf("Capture thread quit return 1\n");
	}
	else
	{

		printf("Capture thread quit return 0\n");
	}

	stop_capturing(&globargs);

	return 0;
}
