cmake_minimum_required(VERSION 2.6)

project(fourbar)

set(VTK_DIR /Users/dillon/Downloads/VTK-build/)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

SET(EXTRA_CXX_COMPILE_FLAGS "-std=c++11 -I./src -I./test -I/opt/local/include -O2 -Werror -Wall")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${EXTRA_CXX_COMPILE_FLAGS}")

INCLUDE_DIRECTORIES(./src/)

SET(FOURBAR_CPPS ./src/vec2.cpp
		 ./src/quadrilateral.cpp)

add_library(fourbar ${FOURBAR_CPPS})

SET(TEST_FILES ./test/vec2_tests.cpp
	       ./test/position_solver_tests.cpp)

add_executable(all-tests ${TEST_FILES})
target_link_libraries(all-tests fourbar)

######### VTK Example ##########

# Make command:
# /opt/local/bin/cmake -DVTK_DIR:PATH=/Users/dillon/Downloads/VTK-build/ -DCMAKE_BUILD_TYPE=Debug . 

if(VTK_LIBRARIES)
#  target_link_libraries(AddCell ${VTK_LIBRARIES})
else()
#  target_link_libraries(AddCell vtkHybrid vtkWidgets)
endif()
