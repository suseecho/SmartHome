/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *camera_Button;
    QPushButton *env_Button;
    QPushButton *connect_Button;
    QLabel *light;
    QLabel *humi;
    QLabel *tem;
    QLabel *ip;
    QLabel *port;
    QLineEdit *light_text;
    QLineEdit *hum_text;
    QLineEdit *tem_text;
    QLineEdit *ip_text;
    QLineEdit *port_text;
    QLabel *camera_view;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *led_Button;
    QPushButton *fan_Button;
    QPushButton *bee_Button;
    QPushButton *close;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1131, 815);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        camera_Button = new QPushButton(centralWidget);
        camera_Button->setObjectName(QStringLiteral("camera_Button"));
        camera_Button->setGeometry(QRect(160, 40, 93, 28));
        env_Button = new QPushButton(centralWidget);
        env_Button->setObjectName(QStringLiteral("env_Button"));
        env_Button->setGeometry(QRect(922, 320, 93, 28));
        connect_Button = new QPushButton(centralWidget);
        connect_Button->setObjectName(QStringLiteral("connect_Button"));
        connect_Button->setGeometry(QRect(910, 680, 93, 28));
        light = new QLabel(centralWidget);
        light->setObjectName(QStringLiteral("light"));
        light->setGeometry(QRect(850, 370, 72, 15));
        humi = new QLabel(centralWidget);
        humi->setObjectName(QStringLiteral("humi"));
        humi->setGeometry(QRect(850, 410, 72, 15));
        tem = new QLabel(centralWidget);
        tem->setObjectName(QStringLiteral("tem"));
        tem->setGeometry(QRect(850, 450, 72, 15));
        ip = new QLabel(centralWidget);
        ip->setObjectName(QStringLiteral("ip"));
        ip->setGeometry(QRect(850, 600, 72, 15));
        port = new QLabel(centralWidget);
        port->setObjectName(QStringLiteral("port"));
        port->setGeometry(QRect(840, 640, 72, 15));
        light_text = new QLineEdit(centralWidget);
        light_text->setObjectName(QStringLiteral("light_text"));
        light_text->setGeometry(QRect(902, 370, 151, 21));
        hum_text = new QLineEdit(centralWidget);
        hum_text->setObjectName(QStringLiteral("hum_text"));
        hum_text->setGeometry(QRect(900, 410, 151, 21));
        tem_text = new QLineEdit(centralWidget);
        tem_text->setObjectName(QStringLiteral("tem_text"));
        tem_text->setGeometry(QRect(902, 450, 151, 21));
        ip_text = new QLineEdit(centralWidget);
        ip_text->setObjectName(QStringLiteral("ip_text"));
        ip_text->setGeometry(QRect(892, 600, 151, 21));
        port_text = new QLineEdit(centralWidget);
        port_text->setObjectName(QStringLiteral("port_text"));
        port_text->setGeometry(QRect(892, 640, 151, 21));
        camera_view = new QLabel(centralWidget);
        camera_view->setObjectName(QStringLiteral("camera_view"));
        camera_view->setGeometry(QRect(40, 100, 721, 591));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(802, 510, 311, 41));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        led_Button = new QPushButton(layoutWidget);
        led_Button->setObjectName(QStringLiteral("led_Button"));

        horizontalLayout->addWidget(led_Button);

        fan_Button = new QPushButton(layoutWidget);
        fan_Button->setObjectName(QStringLiteral("fan_Button"));

        horizontalLayout->addWidget(fan_Button);

        bee_Button = new QPushButton(layoutWidget);
        bee_Button->setObjectName(QStringLiteral("bee_Button"));

        horizontalLayout->addWidget(bee_Button);

        close = new QPushButton(centralWidget);
        close->setObjectName(QStringLiteral("close"));
        close->setGeometry(QRect(940, 30, 93, 28));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1131, 28));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        camera_Button->setText(QApplication::translate("MainWindow", "\346\221\204\345\203\217\345\244\264", nullptr));
        env_Button->setText(QApplication::translate("MainWindow", "\347\216\257\345\242\203\344\277\241\346\201\257", nullptr));
        connect_Button->setText(QApplication::translate("MainWindow", "\350\277\236\346\216\245", nullptr));
        light->setText(QApplication::translate("MainWindow", "\344\272\256\345\272\246", nullptr));
        humi->setText(QApplication::translate("MainWindow", "\346\271\277\345\272\246", nullptr));
        tem->setText(QApplication::translate("MainWindow", "\346\270\251\345\272\246", nullptr));
        ip->setText(QApplication::translate("MainWindow", "IP", nullptr));
        port->setText(QApplication::translate("MainWindow", "\347\253\257\345\217\243", nullptr));
        ip_text->setText(QApplication::translate("MainWindow", "127.0.0.1", nullptr));
        port_text->setText(QApplication::translate("MainWindow", "2333", nullptr));
        camera_view->setText(QApplication::translate("MainWindow", "\347\224\273\351\235\242", nullptr));
        led_Button->setText(QApplication::translate("MainWindow", "LED", nullptr));
        fan_Button->setText(QApplication::translate("MainWindow", "\351\243\216\346\211\207", nullptr));
        bee_Button->setText(QApplication::translate("MainWindow", "\350\234\202\351\270\243\345\231\250", nullptr));
        close->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
