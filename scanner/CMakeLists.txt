cmake_minimum_required(VERSION 3.10)
PROJECT(scanner)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)

find_package(raspicam REQUIRED)
find_package(OpenCV REQUIRED core imgproc)

add_executable (scanner src/main.cpp include/helpers.h include/webcam.h)  
target_include_directories(scanner PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries (scanner ${raspicam_CV_LIBS})
