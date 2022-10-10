cmake_minimum_required(VERSION 3.0.2)
project(vedio_pub)

SET(OpenCV_DIR /usr/share/OpenCV)
find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  sensor_msgs
  roscpp
  std_msgs
  OpenCV
)
# find_package(OpenCV REQUIRED)

include_directories(
  ${OpenCV_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}
)

catkin_package(
  # INCLUDE_DIRS include
  # LIBRARIES ${PROJECT_NAME}
  # CATKIN_DEPENDS roscpp 
  # DEPENDS  opencv
)

## Declare a C++ library
# add_library(${PROJECT_NAME}
#   src/pub_vedio.cpp
# )s
add_executable(vedio_pub_node src/vedio_pub.cpp)
target_link_libraries( vedio_pub_node
        ${catkin_LIBRARIES}
        ${OpenCV_LIBRARIES}
        )
        