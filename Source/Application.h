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
#ifndef _Application_h_
#define _Application_h_


#include "Window/skWindow.h"
#include "Window/skWindowHandler.h"


class Application : public skWindowHandler
{
private:
    skKeyboard*      m_key;
    skMouse*         m_mouse;
    skWindow*        m_window;

    void handleKey(skWindow* window) const;

    void initialize(skWindow* win);

    void handle(const skEventType& evt, skWindow* caller) override;

    void redraw();

public:
    Application();

    ~Application() override;

    int parseCommandLine(int argc, char** argv);

    int run();
};

#endif  //_Application_h_
