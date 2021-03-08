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
#include "HighScores.h"
#include "GameManager.h"
#include "RenderUtils.h"
#include "Window/skKeyboard.h"

using R = Resources;

HighScores::HighScores(GameManager* owner) :
    State(owner)
{
}

void HighScores::handle(const skEventType& evt)
{
    if (evt == SK_KEY_PRESSED)
    {
        switch (getKey())
        {
        case KC_SPACE:
        case KC_RET:
            popState();
            break;
        default:
            break;
        }
    }
}

void HighScores::update()
{
    skClearColor1i(R::Background);
    skProjectContext(SK_STANDARD);
    skClearContext();
    RU::displayBlockArt(R::GameBackground, true);
    RU::displayDropShadow(R::getSingleton(), 20, 20, R::HighScores);
}
