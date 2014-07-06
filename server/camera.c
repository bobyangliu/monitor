#include "camera.h"


//打开摄像头设备
int open_camer_device()
{
	int fd;

	if((fd = open("/dev/video0",O_RDWR | O_NONBLOCK)) < 0)
	{
		perror("Fail to open");
		exit(EXIT_FAILURE);
	} 

	return fd;
}

int init_mmap(struct globData *args)
{
	int i = 0;
	struct v4l2_requestbuffers reqbuf;

	bzero(&reqbuf,sizeof(reqbuf));
	reqbuf.count = 4;
	reqbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	reqbuf.memory = V4L2_MEMORY_MMAP;
	
	//申请视频缓冲区(这个缓冲区位于内核空间，需要通过mmap映射)
	//这一步操作可能会修改reqbuf.count的值，修改为实际成功申请缓冲区个数
	if(-1 == ioctl(args->camera_fd,VIDIOC_REQBUFS,&reqbuf))
	{
		perror("Fail to ioctl 'VIDIOC_REQBUFS'");
		exit(EXIT_FAILURE);
	}
	
	args->n_buffer = reqbuf.count;
	
	printf("n_buffer = %d\n",args->n_buffer);

	args->userBuf = calloc(reqbuf.count+2, sizeof(*(args->userBuf)));
	args->tmpBuf = &(args->userBuf[reqbuf.count]);
	args->sendBuf = &(args->userBuf[reqbuf.count+1]);
	//args->tmpBuf = calloc(1, sizeof(*(args->tmpBuf)));

	if(args->userBuf == NULL){
		fprintf(stderr,"Out of memory\n");
		exit(EXIT_FAILURE);
	}

	//将内核缓冲区映射到用户进程空间
	for(i = 0; i < reqbuf.count; i ++)
	{
		struct v4l2_buffer buf;
		
		bzero(&buf,sizeof(buf));
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;
		buf.index = i;
		//查询申请到内核缓冲区的信息
		if(-1 == ioctl(args->camera_fd,VIDIOC_QUERYBUF,&buf))
		{
			perror("Fail to ioctl : VIDIOC_QUERYBUF");
			exit(EXIT_FAILURE);
		}

		args->userBuf[i].length = buf.length;
		args->userBuf[i].start =
			mmap(
					NULL,/*start anywhere*/
					buf.length,
					PROT_READ | PROT_WRITE,
					MAP_SHARED,
					args->camera_fd,buf.m.offset
				);
		if(MAP_FAILED == args->userBuf[i].start)
		{
			perror("Fail to mmap");
			exit(EXIT_FAILURE);
		}
	}

	args->tmpBuf->start = calloc(1, args->userBuf[0].length);
	args->sendBuf->start = calloc(1, args->userBuf[0].length);
	args->tmpBuf->length = args->userBuf[0].length;
	args->sendBuf->length = args->tmpBuf->length;

	return 0;
}

//初始化视频设备
int init_camer_device(struct globData *args)
{
	struct v4l2_fmtdesc fmt;
	struct v4l2_capability cap;
	struct v4l2_format stream_fmt;
	int ret;
	
	//当前视频设备支持的视频格式
	memset(&fmt,0,sizeof(fmt));
	fmt.index = 0;
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	while((ret = ioctl(args->camera_fd,VIDIOC_ENUM_FMT,&fmt)) == 0)
	{
		fmt.index ++ ;

		printf("{pixelformat = %c%c%c%c},description = '%s'\n",
				fmt.pixelformat & 0xff,(fmt.pixelformat >> 8)&0xff,
				(fmt.pixelformat >> 16) & 0xff,(fmt.pixelformat >> 24)&0xff,
				fmt.description);
	}

	//查询视频设备驱动的功能
	ret = ioctl(args->camera_fd,VIDIOC_QUERYCAP,&cap);
	if(ret < 0){
		perror("FAIL to ioctl VIDIOC_QUERYCAP");
		exit(EXIT_FAILURE);
	}

	//判断是否是一个视频捕捉设备
	if(!(cap.capabilities & V4L2_BUF_TYPE_VIDEO_CAPTURE))
	{
		printf("The Current device is not a video capture device\n");
		exit(EXIT_FAILURE);
	
	}

	//判断是否支持视频流形式
	if(!(cap.capabilities & V4L2_CAP_STREAMING))
	{
		printf("The Current device does not support streaming i/o\n");
		exit(EXIT_FAILURE);
	}

	//设置摄像头采集数据格式，如设置采集数据的
	//长,宽，图像格式(JPEG,YUYV,MJPEG等格式)
	stream_fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	stream_fmt.fmt.pix.width = 320;
	stream_fmt.fmt.pix.height = 240;
	stream_fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
	stream_fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;

	if(-1 == ioctl(args->camera_fd,VIDIOC_S_FMT,&stream_fmt))
	{
		perror("Fail to ioctl");
		exit(EXIT_FAILURE);
	}
	
	//初始化视频采集方式(mmap)
	if(init_mmap(args))
	{
		printf("init_mmap failed!\n");
	}

	return 0;
}

int start_capturing(struct globData *args)
{
	unsigned int i;
	enum v4l2_buf_type type;

	//将申请的内核缓冲区放入一个队列中
	for(i = 0;i < args->n_buffer;i ++)
	{
		struct v4l2_buffer buf;

		bzero(&buf,sizeof(buf));
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;
		buf.index = i;
		
		if(-1 == ioctl(args->camera_fd,VIDIOC_QBUF,&buf))
		{
			perror("Fail to ioctl 'VIDIOC_QBUF'");
			exit(EXIT_FAILURE);
		}
	}

	//开始采集数据
	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if(-1 == ioctl(args->camera_fd,VIDIOC_STREAMON,&type))
	{
		printf("i = %d.\n",i);
		perror("Fail to ioctl 'VIDIOC_STREAMON'");
		exit(EXIT_FAILURE);
	}

	return 0;
}

//将采集好的数据放到文件中
//void *process_image(void *args)
//{
//	FILE *fp;
//	static int num = 0;
//	char picture_name[20];
//	void *addr = tmpbuf->start;
//	int length = tmpbuf->length;
//
//	sprintf(picture_name,"picture%d.jpg",num ++);
//
//	if((fp = fopen(picture_name,"w")) == NULL)
//	{
//		perror("Fail to fopen");
//		exit(EXIT_FAILURE);
//	}
//
//	pthread_mutex_lock(&capture_lock);
//	pthread_cond_wait(&capture_cond, &capture_lock);
//	fwrite(addr,length,1,fp);
//	//usleep(500);
//	pthread_mutex_unlock(&capture_lock);
//
//	fclose(fp);
//
//	return 0;
//}

int read_frame(struct globData *args)
{
	struct v4l2_buffer buf;
	unsigned int i;

	bzero(&buf,sizeof(buf));
	buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	buf.memory = V4L2_MEMORY_MMAP;
	
	if (-1 == ioctl(args->camera_fd, VIDIOC_DQBUF, &buf))
	{ 
		switch (errno) 
		{ 
			case EAGAIN: 
				return 1;
			case EIO: 
			/* Could ignore EIO, see spec. */ 
			/* fall through */ 
			default: 
				//errno_exit("VIDIOC_DQBUF");
				perror("Fail to ioctl 'VIDIOC_DQBUF'");
				exit(EXIT_FAILURE);
		} 
	}  
	assert(buf.index < args->n_buffer);
	//读取进程空间的数据
	memcpy(args->tmpBuf->start, (args->userBuf)[buf.index].start, (args->userBuf)[buf.index].length);
	
	if(-1 == ioctl(args->camera_fd,VIDIOC_QBUF,&buf))
	{
		perror("Fail to ioctl 'VIDIOC_QBUF'");
		exit(EXIT_FAILURE);
	}

	return 0;
}



void stop_capturing(struct globData *args)
{
	enum v4l2_buf_type type;
	
	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if(-1 == ioctl(args->camera_fd,VIDIOC_STREAMOFF,&type))
	{
		perror("Fail to ioctl 'VIDIOC_STREAMOFF'\n");
		exit(EXIT_FAILURE);
	}//stream off
	
	unsigned int i;

	for(i = 0;i < args->n_buffer;i ++)
	{
		if(-1 == munmap(args->userBuf[i].start,args->userBuf[i].length))
		{
			exit(EXIT_FAILURE);
		}
	}//cancle the mmap
	

	free(args->tmpBuf->start);
	free(args->sendBuf->start);
	free(args->userBuf);

	if(-1 == close(args->camera_fd))
	{
		perror("Fail to close fd");
		exit(EXIT_FAILURE);
	}

	return;
}

int captureInit(struct globData *args)
{
	args->camera_fd = open_camer_device();

	init_camer_device(args);
	
	start_capturing(args);

	return 0;
}

//int main()
//{
//	int fd;
//	pthread_t threadCampture, threadReadFrame;
//	void *camptureRtn, *readFrameRtn;
//
//	fd = captureInit();
//
//	pthread_create(&threadCampture, NULL, camptureThread, (void *)&fd);
//	pthread_create(&threadReadFrame, NULL, process_image, NULL);
//
//	pthread_join(threadCampture, &camptureRtn);
//	pthread_join(threadReadFrame, &readFrameRtn);
//
//	stop_capturing(fd);
//
//	return 0;
//}

