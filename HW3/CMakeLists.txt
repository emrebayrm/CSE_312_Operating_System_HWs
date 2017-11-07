cmake_minimum_required(VERSION 3.5)
project(OsHw3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp 8080emu.cpp 8080emuCPP.h Process.cpp Process.h gtuos.cpp gtuos.h memory.h memory.cpp memoryBase.h HardDrive.cpp HardDrive.h Page.cpp Page.h)
add_executable(OsHw3 ${SOURCE_FILES})