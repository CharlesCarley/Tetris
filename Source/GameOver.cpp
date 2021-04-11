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
#include "GameOver.h"
#include "GameManager.h"
#include "MainMenu.h"
#include "RenderUtils.h"
#include "Utils/skRandom.h"
#include "Window/skKeyboard.h"

using R = Resources;

GameOver::GameOver(GameManager* owner) :
    State(owner),
    m_clicked(false)
{
}

void GameOver::handle(const skEventType& evt)
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
    else if (evt == SK_MOUSE_PRESSED)
    {
        if (!m_clicked && getMouseButton() == MBT_L)
            m_clicked = true;
    }
    else if (evt == SK_MOUSE_RELEASED)
    {
        if (m_clicked && getMouseButton() == MBT_L)
            popState();
    }
}

void GameOver::update()
{
    const R& res = R::getSingleton();

    skVector2 sz;
    skGetContext2f(SK_CONTEXT_SIZE, sz.ptr());

    skVector2 pos;
    skClearColor1i(R::Background);
    skProjectContext(SK_STANDARD);
    skClearContext();

    RU::displayBlockArt(R::Splash, true);

    SKint32 w, h;
    skGetFontTextExtent(res.Font,
                        R::GameOver.buf,
                        R::GameOver.len,
                        &w,
                        &h);

    pos.x = sz.x * 0.5f - (skScalar)w * 0.5f;
    pos.y = sz.y * 0.5f - (skScalar)h * 0.5f;
    pos.y -= skScalar(R::menuTextSize >> 1);

    RU::displayDropShadow(res, pos.x, pos.y, R::GameOver);
}
