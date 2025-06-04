cmake_minimum_required(VERSION 3.21.1)
project(lab7)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp
    lib/stack.cpp
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

if(ENABLE_DEBUG)
    target_compile_options(${PROJECT_NAME} PRIVATE -g)
endif()

file(GLOB_RECURSE ALL_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

add_custom_target(
    clang-format
    COMMAND clang-format --dry-run -Werror ${ALL_SOURCES}
)
