#ifndef _CAMPTURESERVER_H_
#define _CAMPTURESERVER_H_

#define CONTROL_ARRAY_SIZE 4

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

	pthread_mutex_t capture_lock;
	pthread_cond_t capture_cond;

	pthread_t threadAccept;
	pthread_t threadCapture;

	void *acceptThreadRtn;
	void *camptureThreadRtn;

	int n_buffer;
	int isRun;
	char control[CONTROL_ARRAY_SIZE];
};


#endif
