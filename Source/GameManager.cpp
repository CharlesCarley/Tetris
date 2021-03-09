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
#include "GameManager.h"
#include "RenderUtils.h"
#include "Splash.h"
#include "Utils/skLogger.h"
#include "Window/skKeyboard.h"

GameManager::GameManager(skWindow* window) :
    m_context(nullptr),
    m_cBlock(nullptr),
    m_window(window),
    m_settings({})
{
    initialize();
}

GameManager::~GameManager()
{
    finalize();
}

void GameManager::pushState(State* state)
{
    SK_ASSERT(state);

    m_cBlock = state;
    m_cBlock->onPush();

    m_stack.push(m_cBlock);

    if (m_window)
        m_window->refresh();
}

void GameManager::popState()
{
    if (m_stack.size() > 1)
    {
        m_orphanedStates.push_back(m_stack.top());
        m_cBlock->onPop();

        m_stack.pop();

        m_cBlock = m_stack.top();

        if (m_cBlock)
            m_cBlock->onPush();

        if (m_window)
            m_window->refresh();
    }
}

void GameManager::sortScore()
{
    for (SKint64 k = 0; k < 9; ++k)
    {
        SKint64 s = k;
        for (SKint64 j = k + 1; j < 10; ++j)
        {
            if (m_settings.topTen[j] > m_settings.topTen[s])
                s = j;
        }
        if (k != s)
            skSwap(m_settings.topTen[k], m_settings.topTen[s]);
    }
}

void GameManager::mergeScore(SKint32 score)
{
    bool hasScore = false;

    for (int i = 0; i < 10 && !hasScore; ++i)
        hasScore = m_settings.topTen[i] == score;

    if (!hasScore)
    {
        for (int i = 0; i < 10; ++i)
        {
            SKint64& last = m_settings.topTen[i];
            if (score > last)
            {
                m_settings.topTen[9] = score;
                break;
            }
        }
    }

    sortScore();
}

void GameManager::destroyOrphanedStates()
{
    if (m_window)
        m_window->refresh();

    StateArray::Iterator it = m_orphanedStates.iterator();
    while (it.hasMoreElements())
        delete it.getNext();

    m_orphanedStates.resizeFast(0);
}

void GameManager::handle(const skEventType& evt)
{
    if (!m_window)
        return;

    if (m_cBlock)
    {
        if (evt == SK_WIN_DESTROY)
        {
            m_cBlock->finalize();
            detachFromWindow();
        }
        else
        {
            if (evt == SK_KEY_PRESSED)
            {
                switch (m_window->getKeyboardRef().key)
                {
                case KC_BACKSPACE:
                case KC_ESC:
                    popState();
                    break;
                default:
                    m_cBlock->handle(SK_KEY_PRESSED);
                }
            }
            else
                m_cBlock->handle(evt);
        }
    }
}

void GameManager::detachFromWindow()
{
    m_window = nullptr;
}

void GameManager::finalize()
{
    try
    {
        destroyOrphanedStates();

        NavigationStack::Iterator it = m_stack.iterator();
        while (it.hasMoreElements())
            delete it.getNext();

        if (m_context)
            skDeleteContext(m_context);
    }
    catch (...)
    {
        skLogd(LD_ASSERT, "finalization threw an exception\n");
    }
}

void GameManager::initialize()
{
    try
    {
        m_context = skNewContext();

        Resources::getSingleton().load();

        m_cBlock = new Splash(this);

        pushState(m_cBlock);

        if (m_window)
            m_window->refresh();
    }
    catch (...)
    {
        skLogd(LD_ASSERT, "initialization threw an exception\n");
    }
}

void GameManager::update() const
{
    Resources& res = Resources::getSingleton();
    res.clearState();

    if (m_cBlock)
    {
        if (!m_cBlock->overrideDefaultState())
        {
            RU::clear();
            m_cBlock->preUpdate();
            RU::displayDropShadow(res, 20, 20, Resources::Title);
        }
        m_cBlock->update();
    }
}
