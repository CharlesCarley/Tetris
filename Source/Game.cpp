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
#include "Game.h"
#include "Board.h"
#include "GameManager.h"
#include "GameOver.h"
#include "RenderUtils.h"
#include "Threads/skCriticalSection.h"
#include "Utils/skRandom.h"
#include "Utils/skString.h"
#include "Window/skKeyboard.h"

using R = Resources;

Game::Game(GameManager* owner) :
    State(owner),
    m_blockSize(0),
    m_cursorX(0),
    m_cursorY(0),
    m_level(R::LevelSpeedMax),
    m_score(0),
    m_breakCount(0),
    m_board(nullptr),
    m_counter(nullptr)
{
    Game::initialize();
}

Game::~Game()
{
    Game::finalize();
}

void Game::finalize()
{
    if (m_counter)
        m_counter->end();

    delete m_counter;
    m_counter = nullptr;

    delete m_board;
    m_board = nullptr;
}

void Game::initialize()
{
    m_counter = new skTimedCallback(this, m_level);
    updateScore(5);

    m_board = new Board(m_owner->getSettings().gridType);
}

void Game::tickStart()
{
    ++m_cursorY;

    {
        SK_LOCK_SCOPE(&m_mutex);
        refresh();
    }
}

void Game::onPush()
{
    SK_ASSERT(m_counter);
    m_counter->begin();

    calculateBoardSize();
    m_board->drop();

    refresh();
}

void Game::onPop()
{
    m_owner->mergeScore(m_score);
    if (m_counter)
        m_counter->end();
}

void Game::handle(const skEventType& evt)
{
    if (evt == SK_WIN_DESTROY)
        m_counter->end();
    else if (evt == SK_KEY_PRESSED)
        handleKeyboard();
}

void Game::handleKeyboard()
{
    bool handled = false;
    switch (getKey())
    {
    case KC_RIGHT:
        handled = true;
        ++m_cursorX;
        break;
    case KC_LEFT:
        handled = true;
        --m_cursorX;
        break;
    case KC_DOWN:
        handled = true;
        ++m_cursorY;
        break;
    case KC_UP:
        handled = true;
        m_score -= 1;
        if (m_score < 0)
            m_score = 0;
        updateScoreString();
        --m_cursorY;
        break;
    case KC_SPACE:
        handled = true;
        m_board->rotate();
        break;
    case KC_R:
        handled   = true;
        m_cursorY = 0;
        m_score -= 200;

        if (m_score < 0)
            m_score = 0;
        updateScoreString();

        m_board->clear();
        m_board->drop();

        break;
    case KC_PAD_SUB:
        stepLevel();
        break;
    case KC_Q:
        handled   = true;
        m_cursorY = 0;
        m_score   = 0;
        updateScoreString();
        m_level = R::LevelSpeedMax;
        m_counter->setInterval(m_level);
        m_board->reset();
        break;
    default:
        break;
    }

    if (handled)
        refresh();
}

void Game::calculateBoardSize()
{
    // calculate the main rectangle as a ratio from
    // the window size and the predetermined grid size.
    skVector2 sz;
    skGetContext2f(SK_CONTEXT_SIZE, sz.ptr());

    // Center it in The window
    m_gameRect.setPosition(0, 0);
    m_gameRect.setSize(sz.x / 3.33333f, 0);

    // Find the number of blocks that will fit in the width
    m_blockSize = m_gameRect.width / skScalar(m_board->getBoardWidth());

    /// scale that to the height
    m_gameRect.height = m_blockSize * skScalar(m_board->getBoardHeight());

    // center it into the window
    m_gameRect.x = sz.x / 2 - m_gameRect.width / 2;
    m_gameRect.y = sz.y / 2 - m_gameRect.height / 2;

    m_nextRect.x      = m_gameRect.getRight() + 3 * m_blockSize;
    m_nextRect.y      = m_gameRect.y;
    m_nextRect.width  = 5 * m_blockSize;
    m_nextRect.height = m_nextRect.width;
}

void Game::fillBackDrops()
{
    const Resources& R = Resources::getSingleton();

    skRectangle tmpRct = m_gameRect;
    tmpRct.expand(8, 8);

    skRect(tmpRct.x, tmpRct.y, tmpRct.width, tmpRct.height);
    skColor1ui(Resources::DarkerShadow);
    skFill();

    skColor1ui(Resources::TextFaded);
    skStroke();
    tmpRct.expand(2, 2);
    skRect(tmpRct.x, tmpRct.y, tmpRct.width, tmpRct.height);

    skColor1ui(Resources::DarkBorder);
    skStroke();

    // next block
    tmpRct = m_nextRect;
    tmpRct.expand(8, 8);

    skRect(tmpRct.x, tmpRct.y, tmpRct.width, tmpRct.height);
    skColor1ui(Resources::DarkerShadow);
    skFill();

    skColor1ui(Resources::TextFaded);
    skStroke();
    tmpRct.expand(2, 2);
    skRect(tmpRct.x, tmpRct.y, tmpRct.width, tmpRct.height);
    skColor1ui(Resources::DarkBorder);
    skStroke();

    if (m_levelStr.empty())
        updateLevelString();

    skSetFont1f(R.Font, SK_FONT_SIZE, skScalar(Resources::menuTextSize / 1.75));

    RU::displayDropShadow(R,
                          m_gameRect.x,
                          m_gameRect.y - skScalar(Resources::menuTextSize),
                          m_levelStr);

    RU::displayDropShadow(R,
                          m_nextRect.getLeft(),
                          m_nextRect.getBottom() + skScalar(Resources::menuTextSize),
                          m_scoreStr);
}

void Game::updateCursor()
{
    SKint32 l, t, r, b, w, h;
    m_board->getPieceBoundingBox(l, t, r, b, w, h);

    if (m_cursorX + l < 0)
        m_cursorX = -l;
    if (m_cursorY + t < 0)
        m_cursorY = -t;
    if (m_cursorX + r > w - 1)
        m_cursorX = w - r - 1;
    if (m_cursorY + b > h - 1)
        m_cursorY = h - b - 1;
}

void Game::stepLevel()
{
    m_level -= R::LevelStep;

    if (m_level < R::LevelSpeedMin)
    {
        m_level = R::LevelSpeedMin + R::LevelStep;
        m_counter->setInterval(m_level);
    }
    else
        m_counter->setInterval(m_level);

    updateLevelString();
    refresh();
}

void Game::updateLevelString()
{
    m_levelStr = skString::format("Level: %d", 1 + (R::LevelSpeedMax - m_level) / R::LevelStep);
}

void Game::updateScore(int numBlocks)
{
    if (numBlocks > 0)
    {
        const int levelFac = 1 + (R::LevelSpeedMax - m_level) / R::LevelStep;

        switch (numBlocks)
        {
        case 1:
            m_score += 10 * levelFac;
            break;
        case 2:
            m_score += 30 * levelFac;
            break;
        case 3:
            m_score += 50 * levelFac;
            break;
        case 4:
            m_score += 80 * levelFac;
            break;
        default:
            m_score = 0;
            break;
        }
    }

    updateScoreString();
}

void Game::updateScoreString()
{
    m_scoreStr = skString::format("Score: %d", m_score);
}

void Game::preUpdate()
{
    RU::displayBlockArt(Resources::GameBackground, true);
}

void Game::update()
{
    // clear the current piece
    m_board->clear();

    updateCursor();

    if (m_board->isGameOver())
    {
        finalize();
        popState();
        pushState(new GameOver(m_owner));
        return;
    }

    m_board->movePiece(m_cursorX, m_cursorY);

    if (m_board->hasCollisions(m_cursorX, m_cursorY))
    {
        m_board->mergePiece(m_cursorX, m_cursorY);
        m_cursorY = 0;

        m_board->mergeAndShift();
        m_board->drop();

        const SKint32 mc = m_board->getLastMergeCount();

        if (mc > 0)
        {
            m_breakCount++;
            stepLevel();
        }

        updateScore(m_board->getLastMergeCount());
        refresh();
    }

    fillBackDrops();

    // fill the screen
    m_board->fill(m_gameRect, m_blockSize);
    m_board->showNext(m_nextRect, m_blockSize);
}
