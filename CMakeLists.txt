cmake_minimum_required(VERSION 3.5)
project(S_DLV_Client)

# pugixml 1.7 root directory
set(PUGIXML_DIR "")

# CXX flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory("src")