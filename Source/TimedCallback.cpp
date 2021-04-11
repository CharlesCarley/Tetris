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
#include "TimedCallback.h"
#include "GameManager.h"

TimedCallback::TimedCallback(Listener*      listener,
                             const SKulong& interrupt,
                             GameManager*   mgr) :
    m_interrupt(interrupt),
    m_tick(0),
    m_listener(listener),
    m_running(false),
    m_owner(mgr)
{
}

TimedCallback ::~TimedCallback()
{
    end();
}

void TimedCallback::setInterval(const SKulong& interrupt)
{
    m_interrupt = skMax<SKint32>(interrupt, 1);
}

void TimedCallback::frameStarted()
{

    if (m_timer.getMicroseconds() - m_tick > m_interrupt)
    {
        m_tick = m_timer.getMicroseconds();
        m_listener->tickEnd();
        m_listener->tickStart();
    }
}

void TimedCallback::begin()
{
    if (m_owner)
    {
        skWindow* window = m_owner->getWindow();
        if (window)
        {
            skWindowManager* mgr = window->getCreator();
            if (mgr)
                mgr->addHandler(this);

            m_timer.reset();
            m_tick = m_timer.getMicroseconds();
            m_listener->tickStart();
        }
    }
}

void TimedCallback::end()
{
    if (m_owner)
    {
        skWindow* window = m_owner->getWindow();
        if (window)
        {
            m_listener->tickEnd();

            skWindowManager* mgr = window->getCreator();
            if (mgr)
                mgr->removeHandler(this);

        }
    }
}
