
#  CMake file for GoogleTest example repo
#
#  UKAEA
#  J. Morris
#  31/07/19
#

# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.5)

# Specify CMake root location
include(${CMAKE_ROOT}/Modules/CMakeDetermineCompiler.cmake)
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

# Set CMake stadard to be 11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS  -std=c++11)

# Setup GoogleTest options
set(GTEST_LIBRARY $ENV{GTEST})
# set(GTEST_INCLUDE_DIR $ENV{GTEST}/include)
# include_directories(${GTEST_INCLUDE_DIR})
set(GTEST_MAIN_LIBRARY $ENV{GTEST})

# Choose gfortran as compiler
set(CMAKE_Fortran_Compiler gfortran)

# Project's name
project(fortran-googletest LANGUAGES Fortran CXX)

# Setup file extension preferences
set(FORT_EXT .F90)

# Define directories for source etc.
set(FORT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/fortran)
set(CPP_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/cpp)
set(GTEST_DIR ${CMAKE_SOURCE_DIR}/src/cpp)
set(BLD_DIR ${CMAKE_BINARY_DIR})
set(CMAKE_INSTALL_RPATH ${CMAKE_BINARY_DIR})
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# Setup C and C++ compilers
find_program(CMAKE_C_COMPILER NAMES $ENV{CC} gcc PATHS ENV PATH NO_DEFAULT_PATH)
find_program(CMAKE_CXX_COMPILER NAMES $ENV{CXX} g++ PATHS ENV PATH NO_DEFAULT_PATH)

# Set CMake compiler flags
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,/usr/local/lib64")

# Set default fortran compiler flags
set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} -cpp -g -fcheck=bounds \
  -fbacktrace")

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Set library path
set(CMAKE_LIBRARY_PATH /usr/lib)

# Set output path
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# The following folders will be included
file(GLOB all_sources ${FORT_SOURCE_DIR}/*.f90 ${FORT_SOURCE_DIR}/*.f)

# Create dynamic library/shared object
add_library(fortran-googletest SHARED ${all_sources})
set_target_properties(fortran-googletest PROPERTIES LINKER_LANGUAGE Fortran)

# Setup for Google test software (CPP executable)
add_executable(GTest.exe ${GTEST_DIR}/main.cpp)
target_link_libraries(GTest.exe fortran-googletest)
target_link_libraries(GTest.exe lapack)
target_link_libraries(GTest.exe $ENV{GTEST}/lib/libgtest.a pthread)
