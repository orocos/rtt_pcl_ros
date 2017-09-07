cmake_minimum_required(VERSION 2.8.3)
project(rtt_pcl_ros)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS rtt_roscomm pcl_ros)

## Set default build type to MinSizeRel
if(NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CMAKE_BUILD_TYPE MinSizeRel)
endif()

###################################
## catkin specific configuration ##
###################################
catkin_package(
  CATKIN_DEPENDS rtt_roscomm pcl_ros
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  ${catkin_INCLUDE_DIRS}
)

## Orocos transport plugin
orocos_typekit(rtt_pcl-ros-transport
  src/transport.cpp
)
target_link_libraries(rtt_pcl-ros-transport ${catkin_LIBRARIES})

#############
## Install ##
#############

## Generate Orocos package
orocos_generate_package(
  DEPENDS_TARGETS rtt_pcl rtt_roscomm
)

