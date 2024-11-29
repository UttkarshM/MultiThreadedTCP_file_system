set(CLIENT_SOURCES client.cpp)
set(SERVER_SOURCES main.cpp)
add_executable(client ${CLIENT_SOURCES})
add_executable(server ${SERVER_SOURCES})
target_link_libraries(client PUBLIC client_lib )
target_link_libraries(server PUBLIC server_lib )
target_include_directories(client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


