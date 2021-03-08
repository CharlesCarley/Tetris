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
#include "Application.h"
#include "Graphics/skGraphics.h"
#include "Utils/skDisableWarnings.h"
#include "Window/skKeyboard.h"
#include "Window/skWindow.h"
#include "Window/skWindowHandler.h"


Application::Application()
{
    m_window = nullptr;
    m_key    = nullptr;
    m_mouse  = nullptr;
}

Application::~Application()
{
    skDeleteContext(skGetCurrentContext());
}

void Application::handleKey(skWindow* window) const
{
    bool handled = false;

    if (handled)
        window->refresh();
}

void Application::initialize(skWindow* win)
{
    m_key   = win->getKeyboard();
    m_mouse = win->getMouse();
}

void Application::handle(const skEventType& evt, skWindow* caller)
{
    switch (evt)
    {
    case SK_KEY_PRESSED:
        handleKey(caller);
        break;
    case SK_MOUSE_RELEASED:
        break;
    case SK_WIN_PAINT:
        redraw();
        caller->flush();
        break;
    case SK_WIN_SIZE:
        caller->refresh();
        break;
    case SK_MOUSE_MOVED:
    case SK_WIN_EVT_UNKNOWN:
    case SK_WIN_DESTROY:
    case SK_KEY_RELEASED:
    case SK_MOUSE_PRESSED:
    case SK_MOUSE_WHEEL:
    case SK_WIN_SHOWN:
    case SK_WIN_HIDDEN:
        break;
    }
}


void Application::redraw()
{
    skClearContext();
}

int Application::parseCommandLine(int argc, char** argv)
{
    return 0;
}


int Application::run()
{
    skWindowManager mgr(WM_CTX_SDL);
    mgr.addHandler(this);

    skWindow* win = mgr.create("GraphicsTemplate", 800, 600, WM_WF_SHOW_CENT_DIA);
    skNewContext();
    skProjectContext(SK_STANDARD);
    initialize(win);
    mgr.broadcastEvent(SK_WIN_SIZE);
    mgr.process();
    return 0;
}
