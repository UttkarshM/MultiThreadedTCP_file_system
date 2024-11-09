set(CLIENT_LIBS Client.cpp)
set(SERVER_LIBS Server.cpp)

add_library(client_libs STATIC ${CLIENT_LIBS})

add_library(server_libs STATIC ${SERVER_LIBS})

target_include_directories(client_libs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(server_libs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
