
cmake_minimum_required(VERSION 3.5)
project(CAS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


include(cmake/compile_option.cmake)

option(REQUIRE_GTEST "Require uses googletest UT framework" OFF)
if (REQUIRE_GTEST)
    enable_testing()
endif ()

set(HEADERS src/Node.h src/Shape.h src/DumpAble.h src/ValidAble.h src/Var.h src/Memory.h src/IDMixin.hpp src/TreeAlg.h src/TreeUpdater.h)
set(SRCS src/Node.cpp src/TreeAlg.cpp src/TreeUpdater.cpp)

add_library(cas ${SRCS} ${HEADERS})


add_executable(cas_app main.cpp)

target_link_libraries(cas_app PRIVATE cas)


if (REQUIRE_GTEST)
    set(UT_SRCS src/NodeTest.cpp)
    add_executable(CASTest ${UT_SRCS})
    target_include_directories(CASTest PRIVATE /opt/homebrew/opt/googletest/include)
    target_link_directories(CASTest PRIVATE /opt/homebrew/opt/googletest/lib)
    target_link_libraries(CASTest PRIVATE cas gtest gtest_main ${Boost_LIBRARIES})
endif ()

