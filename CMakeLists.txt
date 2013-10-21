cmake_minimum_required(VERSION 2.8)

project(neural)

add_executable(neural neural.cpp)

install(TARGETS neural RUNTIME DESTINATION bin)
