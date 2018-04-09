#include "../include/slam_vo/mythread.h"


//订阅rgb和depth图像的进程
MyThread::MyThread(const ros::NodeHandle nd, QObject *parent ): nodehandle(nd), QThread(parent)
{
  //实例化对象，分别订阅rgb和depth话题
  typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Image, sensor_msgs::Image> sync_pol;
  rgb_sub = new message_filters::Subscriber<sensor_msgs::Image>(nodehandle, "/camera/rgb/image_color", 1);
  depth_sub = new message_filters::Subscriber<sensor_msgs::Image>(nodehandle, "camera/depth_registered/image_raw", 1);

  //回调函数为本类的一个成员函数
  sync = new message_filters::Synchronizer<sync_pol>(sync_pol(10), *rgb_sub,*depth_sub);
  sync->registerCallback(boost::bind(&MyThread::MessageCallBack,this,_1,_2));
}

//进程的run()函数，其实就是ros的spin()
void MyThread::run()
{
  ros::spin();
}

//将opencv的mat类数据转化为qt的qimage类型数据
QImage MyThread::MatToQImage(cv::Mat mtx)
{
    switch (mtx.type())
    {
    case CV_8UC1:
        {
            QImage img((const unsigned char *)(mtx.data), mtx.cols, mtx.rows, mtx.cols, QImage::Format_Mono);
            return img;
        }
        break;
    case CV_8UC3:
        {
            QImage img((const unsigned char *)(mtx.data), mtx.cols, mtx.rows, mtx.cols * 3, QImage::Format_RGB888);
            return img.rgbSwapped();
        }
        break;
    case CV_8UC4:
        {
            QImage img((const unsigned char *)(mtx.data), mtx.cols, mtx.rows, mtx.cols * 4, QImage::Format_ARGB32);
            return img;
        }
        break;
    default:
        {
            QImage img;
            return img;
        }
        break;
    }
}

//回调函数，处理时间同步后的图片，并将信号发布到槽中
void MyThread::MessageCallBack(const sensor_msgs::ImageConstPtr& msgRGB, const sensor_msgs::ImageConstPtr& msgD )
{
  //将ros下的图像转换到opencv下
  //cv_bridge对象
  cv_bridge::CvImagePtr cv_ptrRGB;
  //类型转换
  try
  {
    cv_ptrRGB = cv_bridge::toCvCopy(msgRGB,sensor_msgs::image_encodings::BGR8);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("cv_bridge exception: %s", e.what());
    return;
  }
  cv_bridge::CvImagePtr cv_ptrD;
  try
  {
    cv_ptrD = cv_bridge::toCvCopy(msgD,sensor_msgs::image_encodings::TYPE_32FC1);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("cv_bridge exception: %s", e.what());
    return;
  }

  //计数并显示
  count++;
  std::cout<<count<<std::endl;

  //数据类型转换
  this->qimage =  MatToQImage( cv_ptrRGB->image);

  //调用槽函数，向槽中发送数据
  Q_EMIT sendqimage(this->qimage);
}
