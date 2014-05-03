#ifndef _CAMPTURESERVER_H_
#define _CAMPTURESERVER_H_


struct frameBuf{
	void *start;
	int length;
};

struct globData{
	struct frameBuf *userBuf;
	struct frameBuf *tmpBuf;
	struct frameBuf *sendBuf;

	int sock_fd;
	int camera_fd;

	pthread_mutex_t campture_lock;
	pthread_cond_t campture_cond;

	pthread_t threadAccept;
	pthread_t threadCampture;

	void *acceptThreadRtn;
	void *camptureThreadRtn;

	int n_buffer;
	int isRun;
};


#endif
