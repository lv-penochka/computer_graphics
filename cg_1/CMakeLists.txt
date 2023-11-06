add_subdirectory(libs)

project("lab_1")

add_executable(${PROJECT_NAME} "main.cpp" "stb_image.hpp" "stb_image_write.hpp" "image.h" "image.cpp" "Histogram.h" "Histogram.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC matplot)
target_include_directories(${PROJECT_NAME} PUBLIC matplot)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)