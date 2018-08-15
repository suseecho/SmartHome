#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    char buff_pic[1024*100] = {0};
    ~MainWindow();

private slots:

    void win_close();

    void recv_mg();

    //请求连接服务器
    void req_connect_serve();
    void su_connect();
    void su_connect_pic();
    //环境信息交互
    void send_env();
    void recv_env();
    //摄像头信息交互
    void send_cam();
    void get_cam();
    void recv_cam();
    //风扇交互
    void send_fan();
    void recv_fan();
    //蜂鸣器交互
    void send_bee();
    void recv_bee();

private:
    Ui::MainWindow *ui;
    QTcpSocket *sockfd;             //串口 socket
    QTcpSocket *sockfd_pic;         //图像 socket
    QTimer *timer;
    QTimer * timer_pic;
    struct data
    {
        int tem=0,light=0,hum=0;
        int led_flag=1,fan_flag=1,bee_flag=1;
    }data_env;
};

#endif // MAINWINDOW_H
