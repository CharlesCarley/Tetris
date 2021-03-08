# -----------------------------------------------------------------------------
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
include(Application)
set(TargetName_RES Resource/AppIcon.rc)

set(Tetris_SRC 
    Application.h
    Board.h
    Game.h
    GameManager.h
    GameOver.h
    HighScores.h
    MainMenu.h
    Piece.h
    RenderUtils.h
    Resources.h
    Settings.h
    Splash.h
    State.h
    
    Application.cpp
    Board.cpp
    Game.cpp
    GameManager.cpp
    GameOver.cpp
    HighScores.cpp
    MainMenu.cpp
    Piece.cpp
    RenderUtils.cpp
    Resources.cpp
    Settings.cpp
    Splash.cpp
    State.cpp
    ${TargetName_RES}
)

set(Tetris_DAT
    Content/Orbitron-SemiBold.ttf
)

add_application(Tetris)