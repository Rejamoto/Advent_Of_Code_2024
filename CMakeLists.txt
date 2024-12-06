cmake_minimum_required(VERSION 3.30)
project(Advent_Of_Code_2024)

set(CMAKE_CXX_STANDARD 26)

add_executable(Advent_Of_Code_2024 main.cpp
               Day_01/Day_01.cpp
               Day_01/Day_01.h
               Day_02/Day_02.cpp
               Day_02/Day_02.h
               Day_03/Day_03.cpp
               Day_03/Day_03.h
               Day_Base.h
               Day_04/Day_04.cpp
               Day_04/Day_04.h
)
