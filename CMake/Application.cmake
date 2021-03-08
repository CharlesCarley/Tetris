# -----------------------------------------------------------------------------
#
#   Copyright (c) Charles Carley.
#
#   This software is provided 'as-is', without any express or implied
# warranty. In no event will the authors be held liable for any damages
# arising from the use of this software.
#
#   Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgment in the product documentation would be
#    appreciated but is not required.
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.
# ------------------------------------------------------------------------------
include (CopyTarget)

macro(add_application TARGETNAME)

    if(NOT GraphicsTemplate_SILENT)
        message(STATUS "Configuring: ${TARGETNAME}")
        message(STATUS "${TARGETNAME}_SRC ==> ${${TARGETNAME}_SRC}")
        message(STATUS "${TARGETNAME}_INC ==> ${${TARGETNAME}_INC}")
        message(STATUS "${TARGETNAME}_LIB ==> ${${TARGETNAME}_LIB}")
    endif()

    include_directories(. ${Graphics_INCLUDE} ${${TARGETNAME}_INC})
    if (GraphicsTemplate_WIN_MAIN)
        add_executable(${TARGETNAME}  WIN32 ${${TARGETNAME}_SRC})
    else()
        add_executable(${TARGETNAME} ${${TARGETNAME}_SRC})
    endif()

    target_link_libraries(
        ${TARGETNAME}
        ${Graphics_LIBRARY}
        ${${TARGETNAME}_LIB}
       )

    if (${TARGETNAME}_COPY_BIN) 
    
        copy_target(${TARGETNAME} ${CMAKE_SOURCE_DIR}/Bin) 

    endif()
endmacro()
