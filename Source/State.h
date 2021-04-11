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
#ifndef _State_h_
#define _State_h_

#include "Math/skVector2.h"
#include "Resources.h"
#include "Utils/skDisableWarnings.h"
#include "Window/skWindowHandler.h"

class State
{
protected:
    GameManager* m_owner;

public:
    State(GameManager* owner);

    virtual ~State();

    skVector2 getMouseCo() const;

    SKint32 getMouseButton() const;

    SKint32 getMouseButtonState(const SKuint32& button) const;

    SKint32 getKey() const;

    void refresh() const;

    void close();

    void pushState(State* newState) const;

    void popState() const;

    void popAndSaveState() const;

    virtual void initialize()
    {
    }

    virtual void finalize()
    {
    }

    virtual void preUpdate()
    {
    }

    virtual void update()
    {
    }

    virtual void postUpdate()
    {
    }

    virtual void onPush()
    {
    }

    virtual void onPop()
    {
    }

    virtual void handle(const skEventType& evt)
    {
    }

    virtual bool overrideDefaultState()
    {
        return false;
    }
};

#endif  //_State_h_
