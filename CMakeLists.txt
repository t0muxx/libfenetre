cmake_minimum_required(VERSION 3.1...3.28)


project(
    libfenetre
  VERSION 1.0
  LANGUAGES CXX)


add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
    PRIVATE
    process.cpp
    errors.cpp
)