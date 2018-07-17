/*================================================================
*   Copyright (C) 2018  All rights reserved.
*   
*   文件名称：server.c
*   创 建 者：echo (echoxj233@gmail.com)
*   创建日期：2018年07月09日
*   描    述：
*
================================================================*/

#include "server.h"

void *serial_thread()
{
    char buff[BUFFERSIZE] = {0};
    char status[32] = {0};
    int server_sockfd_serial;
    int connect_sockfd_serial;
    int sin_size = 0;
    struct sockaddr_in server_addr_serial;
    struct sockaddr_in connect_addr_serial;

    /* 创建 serial 套接字 */
    if ((server_sockfd_serial = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("serial socket");
        exit(-1);
    }
    printf("serial socket create success\n");

    server_addr_serial.sin_family = AF_INET;
    server_addr_serial.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    server_addr_serial.sin_port = htons(PORT_SERIAL);

    /* 绑定 */

    if (bind(server_sockfd_serial, (struct sockaddr *)&server_addr_serial, sizeof(server_addr_serial)) < 0)
    {
        perror("server socket bind");
        exit(-2);
    }
    printf("serial bind success\n");

    DATA_T env_data;
    int ctrl = 0; //控制

    sin_size = sizeof(connect_addr_serial);
    while (1)
    {
        int fan_ctrl[2] = {1, 2};
        int bee_ctrl[2] = {3, 4};
        int i_fan = 0;
        int j_bee = 0;

        /* 监听 */
        if (listen(server_sockfd_serial, 5) < 0)
        {
            perror("serial listen success\n");
        }

        if ((connect_sockfd_serial = accept(server_sockfd_serial, (struct sockaddr *)&connect_addr_serial, (socklen_t *)&sin_size)) < 0)
        {
            perror("serial accept");
            exit(-3);
        }
        printf("serial accept success\n");
        strcpy(status, "serial connected\n");
        printf("%s\n", status);
        memset(status, 0, sizeof(status));
        //        write(connect_sockfd_serial , status , sizeof(status));
        int len = 0;
        while ((len = recv(connect_sockfd_serial, status, sizeof(status), 0)) > 0)
        {
            printf("operation:   %s\n", status);
            if (strstr(status, "GET_ENV"))
            {
                serial_data(&env_data);
                //env_data.tem = 23;
                //env_data.hum = 54;
                //env_data.light = 234;
                memset(buff, 0, sizeof(buff));
                sprintf(buff, "%dt%dh%dl", env_data.tem, env_data.hum, env_data.light);
                printf("debug---------%s\n",buff);
                write(connect_sockfd_serial, buff, sizeof(buff));
                memset(status, 0, sizeof(status));
            }

            if (strstr(status, "DISCONNECT"))
            {
                memset(buff, 0, BUFFERSIZE);
                printf("disconnected\n");
                close(connect_sockfd_serial);
                break;
            }

            /*      接收控制命令并对控制字结构体赋值        */
            if (strstr(status, "CTRL"))
            {
                //                memset(status,0,sizeof(status));
                //                read(connect_sockfd_serial , status , sizeof(status));
                printf("%s\n", status);
                if (strstr(status, "FAN"))
                {
                    ctrl = fan_ctrl[(i_fan++) % 2];
                    printf("ctrl:%d\n", ctrl);
                }
                if (strstr(status, "BEE"))
                {
                    ctrl = bee_ctrl[(j_bee++) % 2];
                    printf("ctrl:%d\n", ctrl);
                }
                serial_ctr(&ctrl);
                memset(status, 0, sizeof(status));
            }
        }
    }

    pthread_exit(NULL);
}


void thread_create()
{
    int temp;

    memset(&thread_serial_t, 0, sizeof(serial_thread));
    if ((temp = pthread_create(&thread_serial_t, NULL, serial_thread, NULL)) != 0)
    {
        perror("serial thread");
        exit(-3);
    }
    else
    {
        printf("serial thread create success\n");
    }


    memset(&thread_camera_t, 0, sizeof(camera_open));
    if ((temp =  pthread_create(&thread_camera_t, NULL, camera_open, NULL)) != 0)
    {
        perror("camera thread");
        exit(-4);
    }
    else
    {
        printf("camera thread create success\n");
    }


}

void thread_wait()
{
    if (thread_serial_t != 0)
    {
        pthread_join(thread_serial_t, NULL);
        printf("serial thread end\n");
    }

    if (thread_camera_t != 0)
    {
        pthread_join(thread_camera_t, NULL);
        printf("camera thread end\n");
    }
}

int main(int argc, char **argv)
{
    thread_create();
    thread_wait();
    return 0;
}
