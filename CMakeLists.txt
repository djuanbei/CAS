
cmake_minimum_required(VERSION 3.5)
project(CAS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(HEADERS src/Node.h src/Shape.h src/DumpAble.h src/ValidAble.h src/Var.h src/Memory.h src/IDMixin.hpp src/TreeAlg.h)
set(SRCS src/Node.cpp src/TreeAlg.cpp)


add_executable(cas_app main.cpp ${SRCS} ${HEADERS})



