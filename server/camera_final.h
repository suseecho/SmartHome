#ifndef __CAMERA_H__
#define	__CAMERA_H__

#define CAMERA_USB "/dev/video0"
#define JPG_MAX_SIZE (1024*1024 - sizeof(unsigned int))

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>
#define IP_ADDRESS "127.0.0.1"
#define PORT_CAMERA 6666


char jpg_buf[JPG_MAX_SIZE];
unsigned int jpg_size;

int camera_init(char *devpath, unsigned int *width, unsigned int *height, unsigned int *size, unsigned int *ismjpeg);
int camera_start(int fd);
int camera_dqbuf(int fd, void **buf, unsigned int *size, unsigned int *index);
int camera_eqbuf(int fd, unsigned int index);
int camera_stop(int fd);
int camera_exit(int fd);
int camera_on();

void convert_yuv_to_rgb(void *yuv, void *rgb, unsigned int width, unsigned int height, unsigned int bps);
void convert_rgb_to_jpg_init(void);
int convert_rgb_to_jpg_work(void *rgb, void *jpeg, unsigned int width, unsigned int height, unsigned int bpp, int quality);
void convert_rgb_to_jpg_exit(void);

void *camera_open();


pthread_t pthread1;
pthread_mutex_t mutex;

#endif