#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sockfd = NULL;
    sockfd_pic = NULL;
    timer = NULL;
    timer_pic = NULL;

    if(sockfd==NULL)
    {
        ui->env_Button->setEnabled(false);
        ui->camera_Button->setEnabled(false);
        ui->led_Button->setEnabled(false);
        ui->fan_Button->setEnabled(false);
        ui->bee_Button->setEnabled(false);
    }
    else
    {
        connect(ui->env_Button, SIGNAL(clicked()), this, SLOT(send_env()));//点击获取环境信息
        connect(sockfd, SIGNAL(readyRead()), this, SLOT(recv_env()));

        connect(ui->camera_Button,SIGNAL(clicked()),this,SLOT(send_cam()));//点击连接摄像头
        connect(sockfd_pic, SIGNAL(readyRead()), this, SLOT(recv_cam()));

        connect(ui->fan_Button,SIGNAL(clicked()),this,SLOT(send_fan()));//点击控制风扇
        connect(sockfd, SIGNAL(readyRead()), this, SLOT(recv_fan()));

        connect(ui->bee_Button,SIGNAL(clicked()),this,SLOT(send_bee()));//点击控制蜂鸣器
        connect(sockfd, SIGNAL(readyRead()), this, SLOT(recv_bee()));
    }

    connect(ui->connect_Button, SIGNAL(clicked()), this, SLOT(req_connect_serve()));//点击连接服务器
    connect(ui->close,SIGNAL(clicked()),this,SLOT(win_close()));//点击关闭
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::win_close()
{
    if(sockfd == NULL  && sockfd_pic == NULL)
    {

        close();
    }
    else
    {
        sockfd->close();
        char req_buf[15] = "CAM_END";
        sockfd_pic->write(req_buf,sizeof(req_buf));
        sockfd_pic->flush();
        sockfd_pic->close();
        close();
    }
}

void MainWindow::req_connect_serve()//请求连接服务器
{
    QString ip = ui->ip_text->text();
    int port = ui->port_text->text().toInt();
    int port_pic = 6666;
    if(sockfd == NULL)
    {
        sockfd = new QTcpSocket();
        sockfd->connectToHost(ip, port);
        connect(sockfd, SIGNAL(connected()),this,SLOT(su_connect()));
        connect(sockfd, SIGNAL(readyRead()), this, SLOT(recv_env()));
    }

    if(sockfd_pic == NULL)
    {
        sockfd_pic = new QTcpSocket();
        sockfd_pic->connectToHost(ip,port_pic);
        connect(sockfd_pic , SIGNAL(connected()),this, SLOT(su_connect_pic()));
        connect(sockfd_pic , SIGNAL(readyRead()),this, SLOT(recv_cam()));
    }
}


//发送请求获取环境信息字段
void MainWindow::send_env()
{
    char req_buf[15] = "GET_ENV";
    sockfd->write(req_buf, sizeof(req_buf));
    sockfd->flush();

}

void MainWindow::recv_mg()
{
    int ret = 0;
    char recv_buf[36] = {0};
    ret = sockfd->read(recv_buf, sizeof(recv_buf));
    if(ret < 0)
    {
        qDebug()<<"read env fail";
        sockfd->close();
        timer->stop();
    }
    sscanf(recv_buf, "%dt%dh%dl", &data_env.tem, &data_env.hum, &data_env.light);
    char env_buf[5] = {0};
    sprintf(env_buf, "%d", data_env.tem);
    ui->tem_text->setText(env_buf);
    sprintf(env_buf, "%d", data_env.hum);
    ui->hum_text->setText(env_buf);
    sprintf(env_buf, "%d", data_env.light);
    ui->light_text->setText(env_buf);

}

//接收返回的环境信息
void MainWindow::recv_env()
{

    //改变按钮的可点击性
    ui->env_Button->setEnabled(true);
    ui->camera_Button->setEnabled(true);
    ui->led_Button->setEnabled(true);
    ui->fan_Button->setEnabled(true);
    ui->bee_Button->setEnabled(true);

    int ret = 0;
    char recv_buf[36] = {0};
    ret = sockfd->read(recv_buf, sizeof(recv_buf));
    if(ret < 0)
    {
        qDebug()<<"read env fail";
        sockfd->close();
        timer->stop();
    }
    sscanf(recv_buf, "%dt%dh%dl", &data_env.tem, &data_env.hum, &data_env.light);
    char env_buf[5] = {0};
    sprintf(env_buf, "%d", data_env.tem);
    ui->tem_text->setText(env_buf);
    sprintf(env_buf, "%d", data_env.hum);
    ui->hum_text->setText(env_buf);
    sprintf(env_buf, "%d", data_env.light);
    ui->light_text->setText(env_buf);

}
//发送控制摄像头信息字段
void MainWindow::send_cam()
{
    char req_buf[15] = "CTRL_CAM";
    sockfd->write(req_buf, sizeof(req_buf));
    sockfd->flush();
}
//接收返回的摄像头信息

void MainWindow::get_cam()
{
    char req_buf[15] = "GET_PIC";
    sockfd_pic->write(req_buf,sizeof(req_buf));
    sockfd_pic->flush();
}

void MainWindow::recv_cam()
{
    QPixmap pic;
    long len = 0;
    sockfd_pic->read(buff_pic , sizeof(buff_pic));
    sscanf(buff_pic,"%ldlen",&len);
//    qDebug("len:%ld\n",len);
    pic.loadFromData((uchar *)(buff_pic+20),len);
    ui->camera_view->setPixmap(pic);
}


//发送请求获取风扇信息字段
void MainWindow::send_fan()
{
    char req_buf[15] = "CTRL FAN";
    sockfd->write(req_buf, sizeof(req_buf));
    sockfd->flush();
}

//发送请求获取蜂鸣器信息字段
void MainWindow::send_bee()
{
    char req_buf[15] = "CTRL BEE";
    sockfd->write(req_buf, sizeof(req_buf));
    sockfd->flush();
}

void MainWindow::su_connect()
{
    qDebug()<<"connect success";

    if(timer == NULL)
    {
        timer = new QTimer;
        timer->start(2000);
        connect(timer, SIGNAL(timeout()), this, SLOT(send_env()));//获取环境信息
    }


}

void MainWindow::su_connect_pic()
{
    qDebug() << " pic connect success";
    /*
    if(timer_pic == NULL)
    {
        timer_pic = new QTimer;
        timer_pic->start(2000);
        connect(timer_pic , SIGNAL(timeout()),this,SLOT(get_cam()));
    }
    */
}
