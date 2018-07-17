

#================================================================
#   Copyright (C) 2018  All rights reserved.
#   
#   文件名称：Makefile
#   创 建 者：echo echoxj233@gmail.com
#   创建日期：2018年07月10日
#   描    述：
#

#================================================================
all:server.c
#	gcc -m32 read_serial.c -l serial server.c -l pthread -g	
	gcc camera_final.c read_serial.c -l serial  server.c -o server -lcam -m32 -L ./ubuntu_jpeg/lib/ -ljpeg -lpthread -g
a.out:
	gcc camera_final.c read_serial.c -l serial  server.c -o a.out -lcam -m32 -L ./ubuntu_jpeg/lib/ -ljpeg -lpthread -g
clean:
	rm server a.out

