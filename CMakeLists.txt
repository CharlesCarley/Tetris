cmake_minimum_required(VERSION 3.0)
project(GraphicsTemplate)

# Set the module path to include scripts
list(APPEND CMAKE_MODULE_PATH  ${GraphicsTemplate_SOURCE_DIR}/CMake)
list(APPEND CMAKE_MODULE_PATH  ${GraphicsTemplate_SOURCE_DIR}/Extern/Data2Array/CMake)
include(Configure)
subdirs(CMake)
subdirs(Extern)

set(TargetName GraphicsTemplate)

set(GraphicsTemplate_INCLUDE  ${GraphicsTemplate_SOURCE_DIR}/Source)
set(GraphicsTemplate_LIBRARY  ${TargetName})
subdirs(Source)
