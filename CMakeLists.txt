cmake_minimum_required(VERSION 3.16)
project(TCP_FILE_SYSTEM)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)#fPIC

# Windows-specific libraries
if(WIN32)
    find_library(WS2_32_LIBRARY ws2_32)
    find_library(WSOCK32_LIBRARY wsock32)
endif()

add_subdirectory(external)
add_subdirectory(libs)
add_subdirectory(src)
