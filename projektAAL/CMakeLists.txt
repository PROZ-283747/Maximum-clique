cmake_minimum_required(VERSION 3.12)
project(projektAAL)

set(CMAKE_CXX_STANDARD 14)

add_executable(projektAAL main.cpp graphGenerator.cpp graphGenerator.h graph.cpp graph.h interface.cpp interface.h logic_old.cpp logic_old.h fileManager.cpp fileManager.h logic.cpp logic.h)