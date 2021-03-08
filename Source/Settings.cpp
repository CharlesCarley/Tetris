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
#include "Settings.h"
#include "GameManager.h"
#include "MainMenu.h"
#include "Piece.h"
#include "RenderUtils.h"
#include "Window/skKeyboard.h"

Settings::Settings(GameManager* owner) :
    State(owner)
{
    m_selection = owner->getSettings().gridType;
}

void Settings::handle(const skEventType& evt)
{
    if (evt == SK_KEY_PRESSED)
    {
        switch (getKey())
        {
        case KC_SPACE:
        case KC_RET:
            popState();
            break;

        case KC_LEFT:
            m_selection -= 1;
            if (m_selection < 0)
                m_selection = 2;
            refresh();
            break;
        case KC_RIGHT:
            m_selection += 1;
            if (m_selection > 2)
                m_selection = 0;
            refresh();
            break;
        default:
            break;
        }
    }
}

void Settings::onPop()
{
    if (m_owner)
        m_owner->getSettings().gridType = m_selection;
    
}

void Settings::update()
{
    const Resources& R = Resources::getSingleton();

    skClearColor1i(Resources::Background);
    skProjectContext(SK_STANDARD);
    skClearContext();
    RU::displayBlockArt(Resources::GameBackground, true);
    RU::displayDropShadow(R, 20, 20, Resources::Settings);

    skVector2 sz;
    skGetContext2f(SK_CONTEXT_SIZE, sz.ptr());

    const skScalar mts3  = skScalar(Resources::menuTextSize) * 3.f;
    const skScalar mtsO2 = skScalar(Resources::menuTextSize) * 0.5f;

    skRectangle rct;

    rct.width  = sz.x / 1.5f;
    rct.height = mts3;

    rct.x = sz.x * 0.5f - rct.width * 0.5f;
    rct.y = 20 + mts3;

    skColor1ui(Resources::TextFaded);
    skRect(rct.x, rct.y, rct.width, rct.height);
    skStroke();

    skSetFont1f(R.Font, SK_FONT_SIZE, mtsO2);

    RU::displayDropShadow(Resources::getSingleton(),
                          rct.x + 20,
                          rct.y - mtsO2,
                          Resources::GridSize);

    const skScalar unit = rct.width / 3.f;

    skRectangle r1, r2, r3;

    r1.y = r2.y = r3.y = rct.y;
    r1.height = r2.height = r3.height = rct.height;
    r1.width = r2.width = r3.width = unit;

    r1.x = rct.x;
    r2.x = rct.x + unit;
    r3.x = rct.x + unit * 2;

    r1.contract(mtsO2, mtsO2);
    r2.contract(mtsO2, mtsO2);
    r3.contract(mtsO2, mtsO2);

    const skScalar size  = 30;
    const skScalar sizeH = size / 2.f;

    r1 = skRectangle(r1.cx() - sizeH, r1.cy() - sizeH, size, size);
    r2 = skRectangle(r2.cx() - sizeH, r2.cy() - sizeH, size, size);
    r3 = skRectangle(r3.cx() - sizeH, r3.cy() - sizeH, size, size);

    skColor1ui(Resources::Text);
    RU::displayStringSm(R, r1.x, r1.getBottom() + mtsO2, Resources::GS_10x20);

    if (m_selection == 0)
    {
        skColor1ui(Resources::TextFaded);
        skRect(r1.x, r1.y, r1.width, r1.height);
        skStroke();
        RU::displayBlock((SKuint8)Pieces::ColorBlue, r1.x + 2, r1.y + 2, r1.width - 4, 20);
    }
    else
    {
        skColor1ui(Resources::TextFaded);
        skRect(r1.x, r1.y, r1.width, r1.height);
        skStroke();
    }

    skColor1ui(Resources::Text);
    RU::displayStringSm(R, r2.x, r2.getBottom() + mtsO2, Resources::GS_15x30);
    if (m_selection == 1)
    {
        skColor1ui(Resources::TextFaded);
        skRect(r2.x, r2.y, r2.width, r2.height);
        skStroke();
        RU::displayBlock((SKuint8)Pieces::ColorRedViolet, r2.x + 2, r2.y + 2, r2.width - 4, 20);
    }
    else
    {
        skColor1ui(Resources::TextFaded);
        skRect(r2.x, r2.y, r2.width, r2.height);
        skStroke();
    }
    skColor1ui(Resources::Text);
    RU::displayStringSm(R, r3.x, r3.getBottom() + mtsO2, Resources::GS_20x40);
    if (m_selection == 2)
    {
        skColor1ui(Resources::TextFaded);
        skRect(r3.x, r3.y, r3.width, r3.height);
        skStroke();
        RU::displayBlock((SKuint8)Pieces::ColorGreen, r3.x + 2, r3.y + 2, r3.width - 4, 20);
    }
    else
    {
        skColor1ui(Resources::TextFaded);
        skRect(r3.x, r3.y, r3.width, r3.height);
        skStroke();
    }
}
