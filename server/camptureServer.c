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
//			pthread_mutex_lock(&(data->campture_lock));
//			memcpy(data->sendBuf->start, data->tmpBuf->start, data->tmpBuf->length);
//			pthread_cond_signal(&(data->campture_cond));
//			pthread_mutex_unlock(&(data->campture_lock));
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
 				pthread_mutex_lock(&(data->campture_lock));
 				pthread_cond_signal(&(data->campture_cond));
 				pthread_mutex_unlock(&(data->campture_lock));
 				return NULL;
 			}

 			if(!read_frame(data))
 			{
 				printf("start to copy the frame data to send buffer!\n");
 				pthread_mutex_lock(&(data->campture_lock));
 				memcpy(data->sendBuf->start, data->tmpBuf->start, data->tmpBuf->length);
 				pthread_cond_signal(&(data->campture_cond));
 				pthread_mutex_unlock(&(data->campture_lock));
 				printf("copy frame data is complete!\n");
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
//	pthread_mutex_lock(&glob->campture_lock);
//	pthread_cond_wait(&glob->campture_cond, &glob->campture_lock);
//
//	if (send(*(int *)new_fd, tmpbuf->start, tmpbuf->length, 0) == -1)
//	{
//		perror("send");/* 如果错误,则给出错误提示,然后关闭这个新连接,退出 */
//		close(*(int *)new_fd);
//		exit(0);
//	}
//
//	pthread_mutex_unlock(&campture_lock);
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
	struct sockaddr_in their_addr;/* 连接者的地址信息*/
	pthread_t threadChild;//同时发起几个链接时有问题
	void *childThreadRtn;
	struct globData *glob = (struct globData *)args;

	sin_size = sizeof(struct sockaddr_in);

	while(1)
	{
		/* 这里是主 accept()循环 */
		if ((new_fd = accept(glob->sock_fd, (struct sockaddr *)&their_addr, &sin_size)) == -1)
		{
			perror("accept");/* 如果调用 accept()出现错误,则给出错误提示,进入下一个循环 */
			continue;
		}

		printf("server: got connection from %s\n", inet_ntoa(their_addr.sin_addr));/* 服务器给出出现连接的信息 */
		printf("send frame size : %d \n", glob->sendBuf->length);
//		pthread_create(&threadChild, NULL, childThread, (void *)&new_fd);
		pthread_mutex_lock(&glob->campture_lock);
		pthread_cond_wait(&glob->campture_cond, &glob->campture_lock);
		printf("start send the buf data!\n");
		if (send(new_fd, glob->sendBuf->start, glob->sendBuf->length, 0) == -1)
		{
			perror("send");/* 如果错误,则给出错误提示,然后关闭这个新连接,退出 */
			close(new_fd);
			pthread_exit(0);
		}
		pthread_mutex_unlock(&glob->campture_lock);
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

	pthread_mutex_init(&(globargs.campture_lock), NULL);
	pthread_cond_init(&(globargs.campture_cond), NULL);

	pthread_create(&globargs.threadAccept, NULL, acceptThread, (void *)&globargs);
	pthread_create(&globargs.threadCampture, NULL, camptureThread, (void *)&globargs);
	
	if(pthread_join(globargs.threadAccept, &globargs.acceptThreadRtn))
	{
		printf("accept thread quit return 1\n");
	}
	else
	{
		printf("accept thread quit return 0\n");
	}

	if(pthread_join(globargs.threadCampture, &globargs.camptureThreadRtn))
	{
		printf("accept thread quit return 1\n");
	}
	else
	{
		printf("accept thread quit return 0\n");
	}

	stop_capturing(&globargs);

	return 0;
}
