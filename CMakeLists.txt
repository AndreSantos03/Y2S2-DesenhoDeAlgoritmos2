cmake_minimum_required(VERSION 3.24)
project(DA_Project2)

set(CMAKE_CXX_STANDARD 17)

add_executable(DA_Project2 projeto/main.cpp projeto/src/information_management/ReadData.cpp projeto/include/information_management/ReadData.h projeto/src/graph/Graph.cpp projeto/include/graph/Graph.h projeto/src/graph/VertexEdge.cpp projeto/include/graph/VertexEdge.h projeto/src/graph/Algorithms.cpp projeto/include/graph/Algorithms.h projeto/src/Menu.cpp projeto/include/Menu.h projeto/include/graph/MutablePriorityQueue.h)
