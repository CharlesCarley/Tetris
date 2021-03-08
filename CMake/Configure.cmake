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
include(StaticRuntime)
include(ExternalTarget)

set_static_runtime()
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(Tetris_COPY_BIN            "Copy binary to the bin directory." ON)
option(Tetris_BACKEND_OPENGL      "Build the OpenGL backend." ON)
option(Tetris_USE_SDL             "Build with SDL" OFF)
option(Tetris_NO_PALETTE          "Disable builtin palette" OFF)
option(Tetris_OP_CHECKS           "Check function parameters" ON)
option(Tetris_EXTRA_BUILTIN_FONTS "Include extra fonts in the build. https://fonts.google.com/" OFF)

if (WIN32)
    option(Tetris_WIN_MAIN "Wrap main function for WinMain." ON)
    set(Window_DEFINE_WINMAIN ${Tetris_WIN_MAIN} CACHE BOOL "" FORCE)
endif()
  
set(Window_WITH_SDL               ${Tetris_USE_SDL}             CACHE BOOL "" FORCE)
set(Graphics_USE_SDL              ${Tetris_USE_SDL}             CACHE BOOL "" FORCE)
set(Graphics_NO_PALETTE           ${Tetris_NO_PALETTE}          CACHE BOOL "" FORCE)
set(Graphics_OP_CHECKS            ${Tetris_OP_CHECKS}           CACHE BOOL "" FORCE)
set(Graphics_EXTRA_BUILTIN_FONTS  ${Tetris_EXTRA_BUILTIN_FONTS} CACHE BOOL "" FORCE)
set(Graphics_BACKEND_OPENGL       ${Tetris_BACKEND_OPENGL}      CACHE BOOL "" FORCE)




set(FreeImage_SILENT TRUE)
set(Tetris_SILENT TRUE)


# Define the extern path relative to 
# the Tetris source directory
set(Extern ${Tetris_SOURCE_DIR}/Extern)

DefineExternalTarget(Data2Array    Extern "${Extern}/Data2Array")
DefineExternalTarget(Utils         Extern "${Extern}")
DefineExternalTarget(Math          Extern "${Extern}")
DefineExternalTarget(FreeType      Extern "${Extern}/FreeType/Source/2.10.4/include")
DefineExternalTarget(FreeImage     Extern "${Extern}/FreeImage/Source")
DefineExternalTarget(Image         Extern "${Extern}/Image")
DefineExternalTarget(Graphics      Extern "${Extern}/Graphics")

if (Tetris_USE_SDL AND Tetris_BACKEND_OPENGL)
    set(SDL_FOLDER Extern)
    set(SDL_LIBRARY SDL2main SDL2-static)
    set(SDL_INCLUDE ${Extern}/SDL/SDL)
endif()

if (Tetris_BACKEND_OPENGL)
    DefineExternalTarget(Window        Extern "${Extern}/Window")

    set(OpenGL_GL_PREFERENCE GLVND)

    find_package(OpenGL REQUIRED)
    set(OpenGL_LIB ${OPENGL_LIBRARIES})
endif()


set(Graphics_INCLUDE
    ${Extern}/Graphics/
    ${Tetris_BINARY_DIR}
    ${Utils_INCLUDE} 
    ${Math_INCLUDE} 
    ${Window_INCLUDE} 
    ${Image_INCLUDE} 
    ${FreeType_INCLUDE} 
    ${FreeImage_INCLUDE} 
    ${SDL_INCLUDE}
)

set(Graphics_LIBRARY
    Graphics
    ${Utils_LIBRARY} 
    ${Math_LIBRARY} 
    ${Window_LIBRARY} 
    ${Image_LIBRARY} 
    ${FreeType_LIBRARY} 
    ${FreeImage_LIBRARY}
    ${SDL_LIBRARY}
)

