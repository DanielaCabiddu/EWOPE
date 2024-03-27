cmake_minimum_required(VERSION 3.14)

project(src LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

ENABLE_LANGUAGE(C)

add_definitions(-DMUSE_USES_CEREAL)

include_directories(BEFORE "${CMAKE_CURRENT_SOURCE_DIR}/include")

#####
# tclap
include_directories(BEFORE "${CMAKE_CURRENT_SOURCE_DIR}/external/tclap/include")

#####
# cereal
include_directories(BEFORE "${CMAKE_CURRENT_SOURCE_DIR}/external/cereal/include")


add_executable(${PROJECT_NAME}
  src/main.cpp
)
target_link_libraries(${PROJECT_NAME})
