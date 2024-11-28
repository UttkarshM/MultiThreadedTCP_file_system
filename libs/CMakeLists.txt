set(CLIENT_LIBS Client.cpp)
set(SERVER_LIBS Server.cpp)

add_library(server_lib STATIC ${SERVER_LIBS})
add_library(client_lib STATIC ${CLIENT_LIBS})

target_link_libraries(client_lib PUBLIC image_lib)
target_link_libraries(server_lib PUBLIC image_lib)

target_include_directories(client_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(server_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

