#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <assert.h>
#include <linux/videodev2.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>

typedef struct
{
	void *start;
	int length;
}frameBuf;

int n_buffer = 0;
pthread_mutex_t campture_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t campture_cond = PTHREAD_COND_INITIALIZER;

int open_camer_device();
int init_mmap(int fd);
int init_camer_device(int fd);
int start_capturing(int fd);
void *process_image(void *);
int read_frame(int fd);
void *camputureThread(void *);
void stop_capturing(int fd);
int captureInit();

#endif

