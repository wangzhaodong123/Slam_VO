#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QImage>

#include <cv_bridge/cv_bridge.h>
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>

#include <iostream>

namespace Ui { class MyThread; }

//订阅rgb和depth图像的进程
class MyThread : public QThread
{
  Q_OBJECT
public:
  //构造函数
  MyThread( const ros::NodeHandle nd,QObject *parent = 0 );
  void run();
  QImage MatToQImage(cv::Mat mtx);
  //接收到rgb和depth后的回调函数
  void MessageCallBack(const sensor_msgs::ImageConstPtr& msgRGB, const sensor_msgs::ImageConstPtr& msgD );
  QImage qimage;
private:
  //统计回调次数的变量
  int count;
  //QImage qimage;
  //ros节点句柄
  ros::NodeHandle nodehandle;
  //定义两个分别订阅深度图和彩色图的对象
  message_filters::Subscriber<sensor_msgs::Image>* rgb_sub;
  message_filters::Subscriber<sensor_msgs::Image>* depth_sub;
  //消息滤波器，进行时间同步
  message_filters::Synchronizer<message_filters::sync_policies::ApproximateTime<sensor_msgs::Image, sensor_msgs::Image>>* sync;

 Q_SIGNALS:
  //槽的发送函数 
  void sendqimage( QImage );

};

#endif
