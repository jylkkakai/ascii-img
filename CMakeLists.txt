cmake_minimum_required(VERSION 2.8)
project( asciiImg )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( asciiImg main.cpp )
target_link_libraries( asciiImg ${OpenCV_LIBS} )
