cmake_minimum_required(VERSION 2.8)

project(neural)

add_definitions(-std=c++11)

add_executable(${PROJECT_NAME} neural.cpp)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
