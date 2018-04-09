## version an project name
cmake_minimum_required(VERSION 2.8.3)
project(slam_vo)

## c++11
set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-std=c++11 -O3 -Wno-deprecated" )

## package depended
find_package(catkin REQUIRED COMPONENTS
  qt_build
  roscpp
  qt_build
  geometry_msgs
  message_generation
  roscpp
  rospy
  std_msgs
  tf
  image_transport
)

catkin_package()

## QT4
rosbuild_prepare_qt4(QtCore QtGui)
find_package( OpenCV REQUIRED )
find_package( Qt4 REQUIRED )

## directories
include_directories(  ${catkin_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS} )
set( CMAKE_INCLUDE_CURRENT_DIR ON )

## compile
set( QT_SOURCES_UI ui/mainwindow.ui )
set( QT_SOURCES_QRC logo/images.qrc )
set( QT_SOURCES_HEADER include/slam_vo/mainwindow.h include/slam_vo/mythread.h )
set( QT_SOURCES_CPP test/test.cpp src/mainwindow.cpp src/mythread.cpp ${QT_SOURCES_QRC} )


QT4_WRAP_UI(QT_UI_MOC ${QT_SOURCES_UI})
QT4_ADD_RESOURCES(QT_RESOURCES ${QT_SOURCES_QRC})
QT4_WRAP_CPP(QT_HEADER_MOC ${QT_SOURCES_HEADER})

add_executable(slam_vo ${QT_UI_MOC} ${QT_SOURCES_CPP} ${QT_SOURCES_HEADER} ${QT_RESOURCES} ${QT_HEADER_MOC} )
target_link_libraries(slam_vo ${QT_LIBRARIES} ${catkin_LIBRARIES} ${OpenCV_LIBS} /opt/ros/indigo/lib/libcv_bridge.so)
