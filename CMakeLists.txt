
cmake_minimum_required(VERSION 3.5)
project(CAS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(HEADERS src/ExprNode.h src/Shape.h src/DumpAble.h src/ValidAble.h)


add_executable(cas_app main.cpp ${HEADERS})



