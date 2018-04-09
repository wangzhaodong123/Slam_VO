#include "../include/slam_vo/mainwindow.h"
#include "ui_mainwindow.h"


//主窗口（主线程）
MainWindow::MainWindow(const ros::NodeHandle nd,QWidget *parent) :nodehandle(nd),QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //实例化订阅线程
    mythread = new MyThread(nodehandle,this);
    //将两个函数连接起来
    connect( mythread, SIGNAL(sendqimage(QImage)),this,SLOT(displayqimage(QImage)));
    //开启订阅线程
    mythread->start();
}

//主窗口析构函数
MainWindow::~MainWindow()
{
  delete ui;
  delete mythread;
}

//槽的接收端
void MainWindow::displayqimage( QImage qiamge )
{
  //向label中填充收到的图片
  this->ui->label->setPixmap( ( QPixmap::fromImage(qiamge) ).scaled(this->ui->label->size()) );
}
