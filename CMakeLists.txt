project(neural)

add_executable(neural neural.cpp)

install(TARGETS neural RUNTIME DESTINATION bin)
