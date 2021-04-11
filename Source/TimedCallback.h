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
#ifndef _TimedCallback_h_
#define _TimedCallback_h_

#include "Utils/skTimer.h"
#include "Window/skWindowHandler.h"

class GameManager;

class TimedCallback final : public skWindowHandler
{
public:
    class Listener
    {
    public:
        virtual ~Listener() = default;

        virtual void tickStart()
        {
        }

        virtual void tickEnd()
        {
        }
    };

private:
    SKulong      m_interrupt, m_tick;
    Listener*    m_listener;
    bool         m_running;
    skTimer      m_timer;
    GameManager* m_owner;

    void handle(const skEventType& event, skWindow* window) override
    {
    }

    void frameStarted() override;

public:
    TimedCallback(Listener* listener, const SKulong& interrupt, GameManager *mgr);

    ~TimedCallback() override;

    void setInterval(const SKulong& interrupt);
    void begin();
    void end();
};

#endif  //_TimedCallback_h_
