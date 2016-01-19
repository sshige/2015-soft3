cmake_minimum_required(VERSION 2.8.3)
project(enshu_20151209)

find_package(catkin REQUIRED COMPONENTS)
catkin_package()

add_executable(graphsearch src/graphsearch.cpp)
