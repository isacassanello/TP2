# Definir la version de CMake a utilizar
cmake_minimum_required(VERSION 3.10)

project(pokedex) # Nombre del proyecto

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES "../sources/* ../examples/main.cpp")

add_executable(main ${SOURCES})

# Siguientes pasos:
# 1- Crear el folder build y accederlo
# 2- Ejecutar: cmake .. (esto ejecuta el archivo CMakeList.txt que está en el folder superior, por eso se utilizan los ..)
# 3- Ejecutar: make (esto ejecuta el Makefile que generó CMake y crea el ejecutable cmHelloWorld)
# 4- Ejecutar: ./cmHelloWorld