cmake_minimum_required(VERSION 3.10)
project(tinyckg)

set(CMAKE_CXX_STANDARD 11)

# Specify the Homebrew-installed Clang compiler
set(CMAKE_C_COMPILER "/opt/homebrew/opt/llvm/bin/clang")
set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++")

add_executable(tinyckg main.cpp FastaReader.cpp KmerGenerator.cpp KmerHash.cpp KmerStats.cpp)
