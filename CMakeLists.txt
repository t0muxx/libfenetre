cmake_minimum_required(VERSION 3.1...3.28)


project(
    libfenetre
  VERSION 1.0
  LANGUAGES CXX)


add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
    PUBLIC
    dll_injection.cpp
    process.cpp
    errors.cpp
)