# add_library(image_lib STATIC stb_image.c)
# target_include_directories(image_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# external/CMakeLists.txt
add_library(image_lib STATIC stb_image.c)
target_include_directories(image_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

