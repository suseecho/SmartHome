#include "camera_final.h"

int camera_fd = 0;
int ret = 0;
unsigned int width = 480;
unsigned int height = 640;
unsigned int size = 640 * 480;
unsigned int ismjpeg;
unsigned int flags = 1;
char *yuv;
char *rgb;
struct jpg_buf_t *jpg;

int camera_on()
{
    camera_fd = camera_init(CAMERA_USB, &width, &height, &size, &ismjpeg);
    if (camera_fd == -1)
    {
        printf("init failed\n");
        exit(0);
    }

    ret = camera_start(camera_fd);
    if (ismjpeg != 0)
    {
        printf("format:yuyv\n");
        rgb = malloc(width * height * 3);
        convert_rgb_to_jpg_init();
    }
    return camera_fd;
}

void *camera_open()
{
    pthread_mutex_lock(&mutex);
    memset(&pthread1, 0, sizeof(pthread1));
    unsigned int index;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("camera socket");
        exit(1);
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    server.sin_port = htons(PORT_CAMERA);

    socklen_t len = sizeof(server);

    if (bind(sockfd, (struct sockaddr *)&server, len) == -1)
    {
        perror("camera bind");
        exit(2);
    }

    struct sockaddr_in cliaddr;
    memset(&cliaddr, 0, sizeof(cliaddr));

    char temp[15];
    strcpy(temp, "GET_PIC");

    camera_fd = camera_on();
    if (listen(sockfd, 10) == -1)
    {
        perror("camera listen");
        exit(3);
    }
    printf("listening\n");
    len = sizeof(cliaddr);

    int connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &len);

    while (1)
    {
        memset(temp, 0, sizeof(temp));
        //read(connfd, temp, sizeof(temp));
        //printf("debug:  %s\n", temp);
        //printf("client IP: %s, Port: %d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
        char pic_size[32] = {0};
        ret = camera_dqbuf(camera_fd, (void **)&yuv, &size, &index);
        memset(jpg_buf, 0, sizeof(jpg_buf));

        if (ret == -1)
        {
            printf("fail to get picture\n");
            goto END;
        }
        if (ismjpeg == 0)
        {
            memcpy(jpg_buf, yuv, size);
            jpg_size = size;
        }
        else
        {
            convert_yuv_to_rgb(yuv, rgb, width, height, 24);
            jpg_size = convert_rgb_to_jpg_work(rgb, jpg_buf + 20, width, height, 24, 80);
        }

        snprintf(jpg_buf, 20, "%dlen", jpg_size);

        if (ret < 0)
        {
            printf("fail to write\n");
            goto END;
        }

        ret = write(connfd, jpg_buf, jpg_size);
//        usleep(50000);

        ret = camera_eqbuf(camera_fd, index);

        if (ret == -1)
        {
            printf("fail to load\n");
            break;
        }
    }
END:
    pthread_mutex_unlock(&mutex);
    free(jpg);
    convert_rgb_to_jpg_exit();
    camera_stop(camera_fd);
    camera_exit(camera_fd);
    close(connfd);
    close(sockfd);
    return 0;
}