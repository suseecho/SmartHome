/*===============================================================
*   Copyright (C) 2018 All rights reserved.
*   
*   文件名称：read_serial.c
*   创 建 者： taosi
*   创建日期：2018年07月09日
*   描    述：
*
*   更新日志：
*
================================================================*/
#include "server.h"
#define DEVPATH "/dev/ttyUSB0"
int serial_data(DATA_T *data)//传入控制字与温度的结构体
{
	int serial_fd,read_fd,l,h,f,r;
	char serial_path[48]=DEVPATH;
	char read_buf[36]={0};
	char buf[4];
	if((serial_fd=serial_init(serial_path))<0)
	{
		perror("serial_init()");
		return -1;
	}
	if((read_fd=serial_recv_exact_nbytes(serial_fd,read_buf,sizeof(read_buf)))<0)
	{
		perror("serial_recv_exact_nbytes\n");
		return -1;
	}
	l=(int)read_buf[4];
	h=(int)read_buf[5];
      	data->tem=h+l;
	l=(int)read_buf[6];
	h=(int)read_buf[7];
	data->hum=h+l;
	l=read_buf[23];
	l=l<<8;
	l=l^read_buf[22];
	l=l<<8;
	l=l^read_buf[21];
	l=l<<8;
	l=l^read_buf[20];
	data->light=l;
	data->led=(int)read_buf[24];
	data->fan=(int)read_buf[25];
	data->buzz=(int)read_buf[26];
	data->led7=(int)read_buf[27];
	printf("read serial:  tem:%d\thum:%d\tlight:%d\n",data->tem,data->hum,data->light);
	printf("%s\n",read_buf);
	return 0;
}
int serial_ctr(int *ctr)//控制字用一个int来存，1风扇开，2风扇关，3蜂鸣器叫，4不叫
{
	char ctr_buf[36]={0};
	int serial_fd,read_fd,i;
	char fan[10],bee[10];
	 char serial_path[48]=DEVPATH;
	ctr_buf[0]=0xdd;
	ctr_buf[1]=0x08;
	ctr_buf[2]=0x24;
	ctr_buf[3]=0x00;
	printf("开始");
	switch(*ctr)
	{
		case 1:
			ctr_buf[4]=0x04;
			break;
		case 2:
			ctr_buf[4]=0x08;
			break;
		case 3:
			ctr_buf[4]=0x02;
			break;
		case 4:
			ctr_buf[4]=0x03;
			break;
		case 5:
			ctr_buf[4]=0x00;
			break;
		case 6:
			ctr_buf[4]=0x01;
			break;
		default:
			break;
	}
	ctr_buf[5]=0x00;
	for(i=6;i<36;i++)
	{
		ctr_buf[i]=0;
	}
		if((serial_fd=serial_init(serial_path))<0)
	{
		perror("serial_init()");
		return -1;
	}
	
	if((read_fd=serial_send_exact_nbytes(serial_fd,ctr_buf,sizeof(ctr_buf)))<0)
	{
		perror("serial_send");
		return -1;
	}
	
}
