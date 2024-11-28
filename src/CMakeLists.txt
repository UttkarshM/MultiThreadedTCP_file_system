# set(CLIENT_SOURCES client.cpp)
# set(SERVER_SOURCES main.cpp)
#
#
# add_executable(client ${CLIENT_SOURCES})
# add_executable(server ${SERVER_SOURCES})
#
# target_link_libraries(client PUBLIC client_libs image_lib)
# target_link_libraries(server PUBLIC server_libs image_lib)


# src/CMakeLists.txt

# Set the source files for client and server
set(CLIENT_SOURCES client.cpp)
set(SERVER_SOURCES main.cpp)

# Create executables for client and server
add_executable(client ${CLIENT_SOURCES})
add_executable(server ${SERVER_SOURCES})

# Link the client and server executables to the corresponding libraries
target_link_libraries(client PUBLIC client_lib )
target_link_libraries(server PUBLIC server_lib )

# Optionally include directories if needed (e.g., if headers are elsewhere)
target_include_directories(client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


