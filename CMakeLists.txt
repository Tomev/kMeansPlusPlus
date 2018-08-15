cmake_minimum_required(VERSION 3.12)
project(kMeans__)

set(CMAKE_CXX_STANDARD 17)

add_library(kMeans__ SHARED src/kMeans.cpp src/kMeans.h)

include_directories(src)
include_directories(src/lib)
