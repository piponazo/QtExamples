add_library(tcp
    TcpServer.h
    TcpServer.cpp
    TcpClient.h
    TcpClient.cpp
)

set_target_properties(tcp PROPERTIES AUTOMOC ON)
target_link_libraries(tcp PUBLIC Qt5::Network)

add_executable(tcp_server tcp_server.cpp)
add_executable(tcp_client tcp_client.cpp)


target_link_libraries(tcp_server PRIVATE tcp)
target_link_libraries(tcp_client PRIVATE tcp)
