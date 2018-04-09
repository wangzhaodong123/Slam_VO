/*
 *  qt and ros test
 *
*/

// QT
#include "../include/slam_vo/mainwindow.h"
#include <QApplication>

// COMMON
#include <iostream>

// ROS
#include <ros/ros.h>


// NAMESPACE
using namespace std;
using namespace cv;

//MAIN
int main(int argc, char **argv)
{
  // ROS
  ros::init(argc, argv, "sub_rgb_depth");
  ros::NodeHandle nodehandle;
  // QT
  QApplication a(argc, argv);
  MainWindow w(nodehandle);
  w.show();
  return a.exec();
}
