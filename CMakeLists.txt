cmake_minimum_required(VERSION 3.15)
project(GenericServerSide)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS -pthread)

add_executable(GenericServerSide MySerialServer.cpp ClientHandler.h Solver.h HandlerTypes.h CacheManager.h ServerTypes.h SolverTypes.h StringReverser.cpp CacheManagerTypes.h main.cpp State.h Searchable.h Searcher.h BestFirstSearch.h MatrixProblem.h ObjectAdapter.h MyParallelServer.cpp)