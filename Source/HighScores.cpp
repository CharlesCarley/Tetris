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
#include "Utils/skPlatformHeaders.h"

using R = Resources;

HighScores::HighScores(GameManager* owner) :
    State(owner),
    m_topTen(),
    m_clicked(false)
{
    owner->sortScore();
    skMemcpy(m_topTen, owner->getSettings().topTen, sizeof(SKint64) * 10);
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

void HighScores::update()
{
    const Resources& res = R::getSingleton();

    skClearColor1i(R::Background);
    skProjectContext(SK_STANDARD);
    skClearContext();
    RU::displayBlockArt(R::GameBackground, true);
    RU::displayDropShadow(res, 20, 20, R::HighScores);

    skVector2 sz;
    skGetContext2f(SK_CONTEXT_SIZE, sz.ptr());

    const skScalar mts   = skScalar(Resources::menuTextSize);
    const skScalar mts3  = mts * 3.f;
    const skScalar mtsO2 = mts * 0.85f;

    skRectangle rct;

    rct.width  = sz.x / 1.5f;
    rct.height = mts;

    rct.x = sz.x * 0.5f - rct.width * 0.5f;
    rct.y = 20 + mts3;

    skSetFont1f(res.Font, SK_FONT_SIZE, mtsO2);

    for (SKuint32 i = 0; i < 10; ++i)
    {
        skString idx, str;
        skChar::toString(idx, 10 - i);

        skSetContext1f(SK_OPACITY, 0.2f);
        skRect(rct.x, rct.y + mts * (skScalar)i, rct.width, rct.height);
        if (i % 2)
            skColor1ui(R::DarkerShadow);
        else
            skColor1ui(R::Shadow);
        skFill();
        skSetContext1f(SK_OPACITY, 1);

        skColor1ui(R::TextFaded);
        RU::displayString(R::getSingleton(),
                          rct.x + 5,
                          rct.y + mts * (skScalar)i,
                          {
                              idx.c_str(),
                              (SKint32)idx.size(),
                          });

        skChar::toString(str, m_topTen[i]);
        SKint32 w;
        skGetFontTextExtent(R::getSingleton().Font, str.c_str(), (SKint32)str.size(), &w, nullptr);

        skColor1ui(R::TextFaded);
        RU::displayString(R::getSingleton(),
                          rct.x + rct.width - skScalar(w + 5),
                          rct.y + mts * (skScalar)i,
                          {str.c_str(), (SKint32)str.size()});
    }
}
