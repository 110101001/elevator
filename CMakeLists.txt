cmake_minimum_required(VERSION 2.8)
SET(CMAKE_BUILD_TYPE "Debug") 
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
aux_source_directory(. DIR_TOOT_SRCS)
add_executable(ele ${DIR_TOOT_SRCS})

