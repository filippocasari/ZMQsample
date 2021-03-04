cmake_minimum_required(VERSION 3.7)
project(ZMQsample C)

set(CMAKE_C_STANDARD 11)

add_executable(server serverZMQ.c)
add_executable(client clientZMQ.c)
add_executable(pub Pub.c)
add_executable(sub Sub.c)
target_link_libraries(server zmq)
target_link_libraries(client zmq)
target_link_libraries(pub zmq)
target_link_libraries(sub zmq)