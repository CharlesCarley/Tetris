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
#ifndef _GameManager_h_
#define _GameManager_h_

#include "Resources.h"
#include "Utils/skArray.h"
#include "Utils/skStack.h"
#include "Window/skWindow.h"

class GameManager
{
public:
    typedef skArray<State*> StateArray;
    typedef skStack<State*> NavigationStack;

private:
    SKcontext       m_context;
    State*          m_cBlock;
    skWindow*       m_window;
    StateArray      m_orphanedStates;
    NavigationStack m_stack;
    UserSettings    m_settings;

    void initialize();

    void finalize();

public:
    explicit GameManager(skWindow* window);
    ~GameManager();

    void detachFromWindow();

    void update() const;

    void pushState(State* state);

    void popState();

    void handle(const skEventType& evt);

    void destroyOrphanedStates();

    bool hasOrphanedStates() const
    {
        return !m_orphanedStates.empty();
    }

    skWindow* getWindow() const
    {
        return m_window;
    }

    void setSettings(const UserSettings& settings)
    {
        m_settings = settings;
    }

    UserSettings& getSettings()
    {
        return m_settings;
    }
};

#endif  //_GameManager_h_
