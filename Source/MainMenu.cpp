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
#include "MainMenu.h"
#include "Game.h"
#include "GameManager.h"
#include "HighScores.h"
#include "RenderUtils.h"
#include "Settings.h"
#include "Window/skKeyboard.h"

using R = Resources;

MainMenu::MainMenu(GameManager* owner) :
    State(owner),
    m_selection(0)
{
    MainMenu::initialize();
}

void MainMenu::initialize()
{
    const Resources& res = Resources::getSingleton();

    m_selection = 0;
    //skSetFont1i(res.Font, SK_FONT_SIZE, R::menuTextSize);

    RU::getTextRect(res, m_ngRect, R::NewGame);
    RU::getTextRect(res, m_hsRect, R::HighScores);
    RU::getTextRect(res, m_stRect, R::Settings);
    RU::getTextRect(res, m_exRect, R::Exit);
}

int MainMenu::testOption() const
{
    const skVector2 mco = getMouseCo();
    if (m_ngRect.contains(mco) || m_selection == 0)
        return 0;
    if (m_hsRect.contains(mco) || m_selection == 1)
        return 1;
    if (m_stRect.contains(mco) || m_selection == 2)
        return 2;
    if (m_exRect.contains(mco) || m_selection == 3)
        return 3;
    return -1;
}

void MainMenu::pushOption(int opt)
{
    switch (opt)
    {
    case 0:
        pushState(new Game(m_owner));
        break;
    case 1:
        pushState(new HighScores(m_owner));
        break;
    case 2:
        pushState(new Settings(m_owner));
        break;
    case 3:
        close();
        break;
    default:
        break;
    }
}

bool MainMenu::handleKey()
{
    switch (getKey())
    {
    case KC_UP:
        m_selection--;
        if (m_selection < 0)
            m_selection = 3;
        return true;
    case KC_DOWN:
        m_selection++;
        if (m_selection > 3)
            m_selection = 0;
        return true;
    case KC_RET:
        int opt;
        if ((opt = testOption()) != -1)
            pushOption(opt);
        break;
    default:
        break;
    }
    return false;
}

void MainMenu::onPush()
{
    const Resources& res = Resources::getSingleton();
    skVector2        sz;
    skGetContext2f(SK_CONTEXT_SIZE, sz.ptr());
    sz *= skScalar(0.5);


    const skScalar ms = sz.minValue();
    skSetFont1f(res.Font, SK_FONT_SIZE, ms / 18);

    const SKscalar offs = SKscalar(ms / 18 + 50);
    sz.y -= offs * 2;

    // Compute the text rectangle's starting position
    m_ngRect.x = sz.x - m_ngRect.width * .5f;
    m_ngRect.y = sz.y;

    m_hsRect.x = sz.x - m_hsRect.width * .5f;
    m_hsRect.y = sz.y + offs;

    m_stRect.x = sz.x - m_stRect.width * .5f;
    m_stRect.y = sz.y + offs * 2;

    m_exRect.x = sz.x - m_exRect.width * .5f;
    m_exRect.y = sz.y + offs * 3;
}

void MainMenu::handle(const skEventType& evt)
{
    if (evt == SK_KEY_PRESSED)
    {
        if (handleKey())
            refresh();
    }
    else if (evt == SK_MOUSE_MOVED)
    {
        m_selection = -1;
        refresh();
    }
    else if (evt == SK_MOUSE_RELEASED)
    {
        int opt;
        if (m_exRect.contains(getMouseCo()))
            close();
        else if ((opt = testOption()) != -1)
            pushOption(opt);
    }
}

void MainMenu::preUpdate()
{
    RU::displayBlockArt(Resources::GameBackground, true);
}

void MainMenu::update()
{
    const Resources& res = Resources::getSingleton();

    const skVector2 mco = getMouseCo();

    if (m_ngRect.contains(mco) || m_selection == 0)
        RU::displayDropShadow(res, m_ngRect.x, m_ngRect.y, R::NewGame);
    else
    {
        skColor1ui(R::TextFaded);
        skDisplayString(res.Font, R::NewGame.buf, R::NewGame.len, m_ngRect.x, m_ngRect.y);
    }

    if (m_hsRect.contains(mco) || m_selection == 1)
        RU::displayDropShadow(res, m_hsRect.x, m_hsRect.y, R::HighScores);
    else
    {
        skColor1ui(R::TextFaded);
        skDisplayString(res.Font, R::HighScores.buf, R::HighScores.len, m_hsRect.x, m_hsRect.y);
    }

    if (m_stRect.contains(mco) || m_selection == 2)
        RU::displayDropShadow(res, m_stRect.x, m_stRect.y, R::Settings);
    else
    {
        skColor1ui(R::TextFaded);
        skDisplayString(res.Font, R::Settings.buf, R::Settings.len, m_stRect.x, m_stRect.y);
    }

    if (m_exRect.contains(mco) || m_selection == 3)
        RU::displayDropShadow(res, m_exRect.x, m_exRect.y, R::Exit);
    else
    {
        skColor1ui(R::TextFaded);
        skDisplayString(res.Font, R::Exit.buf, R::Exit.len, m_exRect.x, m_exRect.y);
    }
}
