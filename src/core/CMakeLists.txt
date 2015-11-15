cmake_minimum_required(VERSION 3.0)
project(tb)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
SET(CMAKE_CXX_WARNING_LEVEL 4)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set(SOURCE_FILES Atom.cpp Atom.h Chain.cpp Chain.h Insulator.cpp Insulator.h Lead.cpp Lead.h lib.cpp lib.h general.h TB.h)


# Setting SWIG

    FIND_PACKAGE(SWIG REQUIRED)
    INCLUDE(${SWIG_USE_FILE})

    FIND_PACKAGE(PythonLibs)
    INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})
    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

    SET(CMAKE_SWIG_FLAGS "-Wall")
    SET(CMAKE_SWIG_OUTDIR ${CMAKE_BINARY_DIR}/lib)

    SET_SOURCE_FILES_PROPERTIES(tb.i PROPERTIES CPLUSPLUS ON)
    SET_PROPERTY(SOURCE tb.i PROPERTY SWIG_FLAGS "-builtin")


# Generate "libtb.so"
add_library(tb SHARED ${SOURCE_FILES})


# Generate "tbpy.py" and "_tbpy.so"
#SWIG_ADD_MODULE(tbpy python tb.i ${SOURCES_FILES})
#SWIG_LINK_LIBRARIES(tbpy tb armadillo ${PYTHON_LIBRARIES})
