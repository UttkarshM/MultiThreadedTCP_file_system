set(CLIENT_SOURCES client.cpp)
set(SERVER_SOURCES main.cpp)
add_executable(client ${CLIENT_SOURCES})
add_executable(server ${SERVER_SOURCES})

target_link_libraries(client PUBLIC client_libs)
target_link_libraries(server PUBLIC server_libs)
