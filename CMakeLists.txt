cmake_minimum_required(VERSION 3.29)
project(Red_Black_Tree)

set(CMAKE_CXX_STANDARD 20)

add_executable(Red_Black_Tree
        main.cpp
        RedBlackTree.cpp
        RedBlackTree.h
        map.cpp
        map.h
)

add_executable(Map_Test
        mapTest.cc
        RedBlackTree.cpp
        RedBlackTree.h
        map.cpp
        map.h
)