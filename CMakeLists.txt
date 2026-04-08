cmake_minimum_required(VERSION 3.8)
project(M1OEP-cldiego)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(M1OEP-cldiego
        main.cpp
        website.cpp)