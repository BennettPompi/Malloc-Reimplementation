cmake_minimum_required(VERSION 3.22)
project(malloc-indexed)

set(CMAKE_CXX_STANDARD 14)

add_executable(bip7-malloc-indexed main.cpp TestEntry.cpp TestEntry.h main.h malloc.cpp malloc.h smallMalloc.h
smallMalloc.cpp largeMalloc.h largeMalloc.cpp allocMap.cpp allocMap.h timer.cpp timer.h)