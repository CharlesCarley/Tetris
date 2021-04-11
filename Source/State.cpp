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
#include "State.h"
#include "GameManager.h"
#include "Window/skKeyboard.h"
#include "Window/skMouse.h"

State::State(GameManager* owner) :
    m_owner(owner)
{
    SK_ASSERT(m_owner);
}

State::~State()
{
    State::finalize();
}

skVector2 State::getMouseCo() const
{
    skWindow* win = m_owner->getWindow();
    if (win)
    {
        skMouse* mouse = win->getMouse();
        if (mouse)
        {
            return skVector2(skScalar(mouse->x.abs),
                             skScalar(mouse->y.abs));
        }
    }
    return skVector2::Zero;
}

SKint32 State::getMouseButton() const
{
    
    skWindow* win = m_owner->getWindow();
    if (win)
    {
        skMouse* mouse = win->getMouse();
        if (mouse)
        {
            return mouse->button;
        }
    }
    return MBT_None;
}

SKint32 State::getKey() const
{
    skWindow* win = m_owner->getWindow();
    if (win)
    {
        skKeyboard* keyboard = win->getKeyboard();
        if (keyboard)
        {
            return keyboard->key;
        }
    }
    return 0;
}

void State::refresh() const
{
    skWindow* win = m_owner->getWindow();
    if (win)
        win->refresh();
}

void State::close()
{
    skWindow* win = m_owner->getWindow();
    if (win)
    {
        finalize();
        win->close();
        m_owner->detachFromWindow();
    }
}


void State::pushState(State* newState) const
{
    SK_ASSERT(m_owner);
    if (newState != nullptr)
        m_owner->pushState(newState);
}

void State::popState() const
{
    SK_ASSERT(m_owner);
    m_owner->popState();
}

void State::popAndSaveState() const
{
    // TODO: save the state rather than
    //       orphaning it, so that it
    //       can be restored
    SK_ASSERT(m_owner);
    m_owner->popState();
}
