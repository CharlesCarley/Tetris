cmake_minimum_required(VERSION 3.0)
project(Tetris)

# Set the module path to include scripts
list(APPEND CMAKE_MODULE_PATH  ${Tetris_SOURCE_DIR}/CMake ${Tetris_SOURCE_DIR}/CMake/Modules)
list(APPEND CMAKE_MODULE_PATH  ${Tetris_SOURCE_DIR}/Extern/Data2Array/CMake)
include(Configure)
subdirs(CMake)
subdirs(Extern)

set(TargetName Tetris)

set(Tetris_INCLUDE  ${Tetris_SOURCE_DIR}/Source)
set(Tetris_LIBRARY  ${TargetName})
subdirs(Source)


if (Tetris_BUILD_TEST)
    set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
    add_subdirectory(${Tetris_SOURCE_DIR}/Test/googletest/)

    
    add_external_test(Utils Tests)
    add_external_test(Json Test)
    add_external_test(Threads Test)
    add_external_test(Graphics Tests)

endif()
