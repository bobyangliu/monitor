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
#include "camptureServer.h"

int open_camer_device();
int init_mmap(struct globData *args);
int init_camer_device(struct globData *args);
int start_capturing(struct globData *args);

int read_frame(struct globData *args);
//void *camptureThread(void *);
void stop_capturing(struct globData *args);
int captureInit(struct globData *args);

#endif

