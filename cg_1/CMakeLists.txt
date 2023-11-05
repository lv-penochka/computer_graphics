add_subdirectory(libs)

project("lab_1")

file(GLOB_RECURSE HEADERS "*.h")
file(GLOB_RECURSE SOURCES "*.cpp")

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})