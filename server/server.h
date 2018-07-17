/*================================================================
*   Copyright (C) 2018  All rights reserved.
*   
*   文件名称：server.h
*   创 建 者：echo (echoxj233@gmail.com)
*   创建日期：2018年07月09日
*   描    述：
*
================================================================*/
#ifndef __SERVER_H
#define __SERVER_H
#include "serial.h"
#include "camera_final.h"
#include "cam.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#define BUFFERSIZE 256

#define IP_ADDRESS "127.0.0.1"
#define PORT_SERIAL    2333
#define PORT_CAMERA    6666

pthread_t thread_serial_t;
pthread_t thread_camera_t;

/* 环境数据结构体 */
typedef struct
{
	int light;
	int hum;
	int tem;
	int led;
	int fan;
	int buzz;
	int led7;
}DATA_T;



/* 控制字 */




#endif