add_executable(tcp_server tcp_server.cpp)

target_link_libraries(tcp_server PRIVATE Qt5::Network)
