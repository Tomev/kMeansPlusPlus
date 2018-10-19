cmake_minimum_required(VERSION 3.12)
project(kMeans__)

set(CMAKE_CXX_STANDARD 17)

add_library(kMeans__ SHARED src/kMeans.cpp src/kMeans.h
            src/meansInitializationAlgorithms/classicalMeansInitializationAlgorithm.cpp
            src/meansInitializationAlgorithms/classicalMeansInitializationAlgorithm.h
            src/meansInitializationAlgorithms/kPlusPlusInitializationAlgorithm.cpp
            src/meansInitializationAlgorithms/kPlusPlusInitializationAlgorithm.h)

include_directories(src)
include_directories(src/lib)
include_directories(src/meansInitializationAlgorithms)