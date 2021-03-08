cmake_minimum_required(VERSION 3.0)
project(Tetris)

# Set the module path to include scripts
list(APPEND CMAKE_MODULE_PATH  ${Tetris_SOURCE_DIR}/CMake)
list(APPEND CMAKE_MODULE_PATH  ${Tetris_SOURCE_DIR}/Extern/Data2Array/CMake)
include(Configure)
subdirs(CMake)
subdirs(Extern)

set(TargetName Tetris)

set(Tetris_INCLUDE  ${Tetris_SOURCE_DIR}/Source)
set(Tetris_LIBRARY  ${TargetName})
subdirs(Source)
