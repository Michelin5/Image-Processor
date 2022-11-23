cmake_minimum_required(VERSION 3.17)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(image_processor
    image_processor.cpp
        BMPReader.h Image.h Parser.h Filters.h Parser.cpp BMPReader.cpp Filters.cpp ImageProcessing.h ImageProcessing.cpp)
