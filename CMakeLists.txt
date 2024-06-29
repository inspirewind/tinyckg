cmake_minimum_required(VERSION 3.10)

list(APPEND CMAKE_PREFIX_PATH /usr/bin /usr/local/bin)

find_program(CLANGXX clang++ PATHS /usr/bin /usr/local/bin NO_DEFAULT_PATH)
find_program(GXX g++ PATHS /usr/bin /usr/local/bin NO_DEFAULT_PATH)

if(CLANGXX)
    message(STATUS "Found clang++: ${CLANGXX}")
    set(CMAKE_CXX_COMPILER ${CLANGXX})
elseif(GXX)
    message(STATUS "Found g++: ${GXX}")
    set(CMAKE_CXX_COMPILER ${GXX})
else()
    message(FATAL_ERROR "Neither clang++ nor g++ found")
endif()

find_program(CLANG clang PATHS /usr/bin /usr/local/bin NO_DEFAULT_PATH)
find_program(GCC gcc PATHS /usr/bin /usr/local/bin NO_DEFAULT_PATH)

if(CLANG)
    message(STATUS "Found clang: ${CLANG}")
    set(CMAKE_C_COMPILER ${CLANG})
elseif(GCC)
    message(STATUS "Found gcc: ${GCC}")
    set(CMAKE_C_COMPILER ${GCC})
else()
    message(FATAL_ERROR "Neither clang nor gcc found")
endif()

project(tinyckg)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(tinyckg main.cpp FastaReader.cpp KmerGenerator.cpp KmerHash.cpp KmerStats.cpp)
