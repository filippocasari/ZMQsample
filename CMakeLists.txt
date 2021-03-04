cmake_minimum_required(VERSION 3.7)
project(ZMQsample C)

set(CMAKE_C_STANDARD 11)

add_executable(server "Echo Server-Client/serverZMQ.c")
add_executable(client "Echo Server-Client/clientZMQ.c")
add_executable(pub "Pub-sub Sample/Pub.c")
add_executable(sub "Pub-sub Sample/Sub.c")
target_link_libraries(server zmq)
target_link_libraries(client zmq)
target_link_libraries(pub zmq)
target_link_libraries(sub zmq)