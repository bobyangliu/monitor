#ifndef _SERVER_H_
#define _SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/wait.h>

#define MYPORT 4000/* 服务器要监听的本地端口 */
#define BACKLOG 10/* 能够同时接受多少没有 accept 的连接 */

struct SendDataHead{
	int length;
};

int serverInit(int myPort);
#endif
