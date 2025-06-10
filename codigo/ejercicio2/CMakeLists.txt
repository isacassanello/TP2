cmake_minimum_required(VERSION 3.10)

project(drones) # Nombre del proyecto

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES "src/*.cpp" "examples/main.cpp")

add_executable(main ${SOURCES})

target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/include)

set_target_properties(main PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)