cmake_minimum_required(VERSION 2.8.3)
project(enshu_20151104)

find_package(catkin REQUIRED COMPONENTS
  jsk_recognition_msgs
  jsk_perception
  image_view2
  roseus
)

catkin_package()
