#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <ros/ros.h>

#include "mythread.h"

namespace Ui { class MainWindow; }

//主窗口类声明
class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  //构造函数，因为要将nodehandle传入mythread，所以参数有一个nd
  explicit MainWindow(const ros::NodeHandle nd, QWidget *parent = 0);
  ~MainWindow();
private:
  Ui::MainWindow *ui;
  //订阅线程从这个主线程中启动，所以，MyThread是mainwindow的一个成员
  MyThread *mythread;
  ros::NodeHandle nodehandle;
private Q_SLOTS:
  //槽的接收函数
  void displayqimage( QImage qiamge );

};

#endif // MAINWINDOW_H
