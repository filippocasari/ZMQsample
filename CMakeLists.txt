cmake_minimum_required(VERSION 3.7)
project(ZMQsample C)

set(CMAKE_C_STANDARD 99)

add_executable(server serverZMQ.c)
add_executable(client clientZMQ.c)
target_link_libraries(server zmq)
target_link_libraries(client zmq)