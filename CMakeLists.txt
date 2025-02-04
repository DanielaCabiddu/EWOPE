cmake_minimum_required(VERSION 3.14)

project(EWOPE LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CORE_SUFFIX "core")
set(CHECK_SUFFIX "check")

set(CORE_TARGET_NAME ${PROJECT_NAME}_${CORE_SUFFIX})
set(CHECK_TARGET_NAME ${PROJECT_NAME}_${CHECK_SUFFIX})

ENABLE_LANGUAGE(C)

add_definitions(-DEWOPE_USES_CEREAL)
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/include)

#####
# tclap
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/external/tclap/include)

#####
# cereal
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/external/cereal/include)

## build
add_executable(${CORE_TARGET_NAME} src/main.cpp )
add_executable(${CHECK_TARGET_NAME} src/main_check.cpp)

# target_link_libraries(${PROJECT_NAME})
