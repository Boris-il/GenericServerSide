cmake_minimum_required(VERSION 3.15)
project(GenericServerSide)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS -pthread)

add_executable(GenericServerSide main.cpp ClientHandler.h Solver.h HandlerTypes.h CacheManager.h ServerTypes.h MySerialServer.cpp)