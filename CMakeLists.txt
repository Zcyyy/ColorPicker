cmake_minimum_required(VERSION 2.8.3)
project(test_opencv)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(OpenCV 4 REQUIRED)
find_package(yaml-cpp REQUIRED)
include_directories(include ${OpenCV_INCLUDE_DIRS} ${catkin_INCLUDE_DIRS} ${YAML_CPP_INCLUDE_DIRS})

add_executable(colorPicker src/colorPicker.cpp)
target_link_libraries(colorPicker ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} yaml-cpp)

