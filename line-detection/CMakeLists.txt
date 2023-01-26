cmake_minimum_required(VERSION 3.16)

project(OpenCV)

find_package(OpenCV REQUIRED)

add_executable(main main.cpp linedetect.cpp)

set (OPENCV_INCLUDE_DIR "/usr/local/include/opencv4")
set (OPENCV_LIB_DIR "/usr/local/lib/")


target_include_directories(main PUBLIC ${OPENCV_INCLUDE_DIR})

target_include_directories(main PUBLIC ${OPENCV_LIB_DIR})

target_link_libraries(main ${OpenCV_LIBS})