cmake_minimum_required(VERSION 3.5)
project(S_DLV_Client)

# Read and edit this file before proceeding
include("Dependencies.cmake")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

add_subdirectory("src")