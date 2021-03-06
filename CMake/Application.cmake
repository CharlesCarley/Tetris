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
include (FindVSEmscripten)

macro(add_application TARGETNAME)

    if(NOT Tetris_SILENT)
        message(STATUS "Configuring: ${TARGETNAME}")
        message(STATUS "${TARGETNAME}_SRC ==> ${${TARGETNAME}_SRC}")
        message(STATUS "${TARGETNAME}_INC ==> ${${TARGETNAME}_INC}")
        message(STATUS "${TARGETNAME}_LIB ==> ${${TARGETNAME}_LIB}")
    endif()

    include_directories(. ${Graphics_INCLUDE} ${${TARGETNAME}_INC})
    if (USING_EMSCRIPTEN)
        set(BIN_DIR ${CMAKE_SOURCE_DIR}/docs)
        add_executable(${TargetName}   ${BIN_DIR}/index.html ${${TARGETNAME}_SRC})
        
        enable_emscripten_html_executable(${TargetName})

        set_target_properties(${TargetName} PROPERTIES VS_GLOBAL_EmSdlVersion        2)
        set_target_properties(${TargetName} PROPERTIES VS_GLOBAL_EmUseFullOpenGles2  true)

        set_target_properties(${TargetName} 
            PROPERTIES VS_GLOBAL_EmEmbeddedFile  
            "${CMAKE_CURRENT_SOURCE_DIR}/Content@/Content")

        emscripten_copy_wasm_target_wasm_js(${TargetName} ${BIN_DIR}) 

    elseif (Tetris_WIN_MAIN)
        add_executable(${TARGETNAME}  WIN32 ${${TARGETNAME}_SRC})
        if (${TARGETNAME}_COPY_BIN) 
    
            copy_target(${TARGETNAME} ${CMAKE_SOURCE_DIR}/Bin) 
            copy_content(${TARGETNAME} ${CMAKE_SOURCE_DIR}/Bin ${${TARGETNAME}_DAT})

            if (MSVC)
                set_target_properties(
                    ${TARGETNAME} 
                    PROPERTIES 
                    VS_DEBUGGER_WORKING_DIRECTORY  
                    ${CMAKE_SOURCE_DIR}/Bin
                )
            endif()
        endif()
    else()
        add_executable(${TARGETNAME} ${${TARGETNAME}_SRC})
        if (${TARGETNAME}_COPY_BIN) 
    
            copy_target(${TARGETNAME} ${CMAKE_SOURCE_DIR}/Bin) 
            copy_content(${TARGETNAME} ${CMAKE_SOURCE_DIR}/Bin ${${TARGETNAME}_DAT})

            if (MSVC)
                set_target_properties(
                    ${TARGETNAME} 
                    PROPERTIES 
                    VS_DEBUGGER_WORKING_DIRECTORY  
                    ${CMAKE_SOURCE_DIR}/Bin
                )
            endif()
        endif()
    endif()

    target_link_libraries(
        ${TARGETNAME}
        ${Graphics_LIBRARY}
        ${${TARGETNAME}_LIB}
       )

endmacro()
