/*
-------------------------------------------------------------------------------
    Copyright (c) Charles Carley.

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/
#ifndef _Game_h_
#define _Game_h_

#include "Math/skRectangle.h"
#include "State.h"
#include "Threads/skTimedCallback.h"
#include "Threads/skMutex.h"
#include "Utils/skString.h"

class RefreshRunner;
class Board;

class Game : public State, public skTimedCallback::Listener
{
private:
    skRectangle      m_gameRect;
    skRectangle      m_nextRect;
    skScalar         m_blockSize;
    SKint32          m_cursorX;
    SKint32          m_cursorY;
    SKint32          m_level;
    skString         m_levelStr;
    skString         m_scoreStr;
    SKint32          m_score;
    SKint32          m_breakCount;
    Board*           m_board;
    skTimedCallback* m_counter;
    skMutex          m_mutex;


    void fillBackDrops();

    void calculateBoardSize();

    void tickStart() override;

    void handle(const skEventType& evt) override;

    void handleKeyboard();

    void updateCursor();

    void stepLevel();

    void updateLevelString();

    void updateScore(int numBlocks);

    void updateScoreString();

    void onPush() override;

    void onPop() override;

public:
    Game(GameManager* owner);

    ~Game() override;

    void finalize() override;

    void initialize() override;

    void preUpdate() override;

    void update() override;
};

#endif  //_Game_h_
