cmake_minimum_required(VERSION 3.15)
project(GenericServerSide)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS -pthread)

add_executable(GenericServerSide MySerialServer.cpp MyTestClientHandler.cpp ClientHandler.h Solver.h HandlerTypes.h CacheManager.h ServerTypes.h SolverTypes.h StringReverser.cpp FileCacheManager.cpp CacheManagerTypes.h main.cpp State.h Searchable.h Searcher.h BestFirstSearch.h MatrixProblem.h MyClientHandler.cpp ObjectAdapter.h)