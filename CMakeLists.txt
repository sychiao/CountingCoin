cmake_minimum_required(VERSION 2.8)
project( CountingCoin )
find_package( OpenCV REQUIRED )

SET(CMAKE_BUILD_TYPE DEBUG)

add_executable( DisplayImage opencv_sample.cpp )
target_link_libraries( DisplayImage ${OpenCV_LIBS} )


add_executable( CountingCoin main.cpp sobel.cpp hough.cpp erode.cpp )
target_link_libraries( CountingCoin ${OpenCV_LIBS} )
