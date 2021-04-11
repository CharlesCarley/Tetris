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
#ifndef _MainMenu_h_
#define _MainMenu_h_

#include "Math/skRectangle.h"
#include "State.h"

class MainMenu : public State
{
private:
    skRectangle m_ngRect;
    skRectangle m_stRect;
    skRectangle m_hsRect;
    skRectangle m_exRect;
    SKint32     m_selection;
    bool        m_clicked;

    void handle(const skEventType& evt) override;

    bool handleKey();

    int testOption() const;

    void pushOption(int opt);

    void preUpdate() override;

    void onPush() override;

public:
    MainMenu(GameManager* owner);

    void initialize() override;

    void update() override;
};

#endif  //_MainMenu_h_
