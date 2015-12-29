cmake_minimum_required(VERSION 2.8.3)
project(enshu_20151111)

find_package(catkin REQUIRED COMPONENTS)
catkin_package()

execute_process(COMMAND make -C ${PROJECT_SOURCE_DIR})



