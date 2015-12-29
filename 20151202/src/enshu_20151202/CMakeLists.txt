cmake_minimum_required(VERSION 2.8.3)
project(enshu_20151202)

find_package(catkin REQUIRED COMPONENTS)
catkin_package()

add_executable(GCTest src/GCTest.cpp)
target_link_libraries(GCTest pthread gtest)

if(NOT EXISTS GCTest.gc.log)
  message(FATAL "java -cp src -verbosegc -Xloggc:GCTest.gc.log GCTest")
endif()
if(NOT EXISTS GCTest.incgc.log)
  message(FATAL "java -cp src -Xincgc -verbosegc -Xloggc:GCTest.incgc.log GCTest")
endif()
