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
#include "GameManager.h"
#include "Graphics/skGraphics.h"
#include "Json/skJsonParser.h"
#include "Json/skJsonVisitor.h"
#include "Utils/CommandLine/skCommandLineParser.h"
#include "Utils/skDisableWarnings.h"
#include "Utils/skLogger.h"
#include "Utils/skRandom.h"
#include "Window/skKeyboard.h"
#include "Window/skWindow.h"
#include "Window/skWindowHandler.h"

using namespace skCommandLine;

enum SwitchIds
{
    TETRIS_WIN_SIZE = 0,
    TETRIS_MAX
};

const Switch Switches[TETRIS_MAX] = {
    {
        TETRIS_WIN_SIZE,
        'w',
        "window",
        "Specify the window width and height.\n"
        "  - Arguments: [width, height]\n"
        "    - Width  [200 - 7680]\n"
        "    - Height [100 - 4320]\n",
        true,
        2,
    },
};

class AppPrivate : public skJsonVisitor
{
private:
    Application* m_parent;

public:
    AppPrivate(Application* parent) :
        m_parent(parent)
    {
    }
    ~AppPrivate() override = default;

    void keyValueParsed(const skString&        key,
                        const skJsonTokenType& valueType,
                        const skString&        value) override
    {
        if (key.equals("width"))
            m_parent->m_settings.width = value.toInt32();
        else if (key.equals("height"))
            m_parent->m_settings.height = value.toInt32();
        else if (key.equals("type"))
            m_parent->m_settings.gridType = value.toInt32();
    }
};

Application::Application() :
    m_key(nullptr),
    m_mouse(nullptr),
    m_manager(nullptr),
    m_settings({800, 600, 0})
{
    m_private = new AppPrivate(this);
}

Application::~Application()
{
    delete m_private;
    skDeleteContext(skGetCurrentContext());
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
    case SK_WIN_SIZE:
        skSetContext2i(SK_CONTEXT_SIZE, caller->getWidth(), caller->getHeight());
        caller->refresh();
        break;
    case SK_WIN_PAINT:
        m_manager->update();
        caller->flush();
        break;
    case SK_KEY_PRESSED:
    case SK_MOUSE_RELEASED:
    case SK_MOUSE_MOVED:
    case SK_WIN_EVT_UNKNOWN:
    case SK_WIN_DESTROY:
    case SK_KEY_RELEASED:
    case SK_MOUSE_PRESSED:
    case SK_MOUSE_WHEEL:
    case SK_WIN_SHOWN:
    case SK_WIN_HIDDEN:
        m_manager->handle(evt);
        break;
    }
}

int Application::parseCommandLine(int argc, char** argv)
{
    Parser p;
    if (p.parse(argc, argv, Switches, TETRIS_MAX) < 0)
        return 1;

    if (p.isPresent(TETRIS_WIN_SIZE))
    {
        m_settings.width  = (SKuint16)p.getValueInt(TETRIS_WIN_SIZE, 0, 800);
        m_settings.height = (SKuint16)p.getValueInt(TETRIS_WIN_SIZE, 1, 600);
    }

    m_programDir = p.getProgramDirectory();
    loadSettings();
    return 0;
}

void Application::loadSettings()
{
    skJsonParser parser(m_private);
    parser.parse(m_programDir + "settings.json");

    m_settings.width    = skClamp<SKint32>(m_settings.width, 200, 7680);
    m_settings.height   = skClamp<SKint32>(m_settings.height, 100, 4320);
    m_settings.gridType = skClamp<SKint32>(m_settings.gridType, 0, 5);
}

void Application::saveSettings()
{
    // create a skJsonPrinter;
}




int Application::run()
{
    Resources* resource = new Resources();
    skRandInit();

    skWindowManager mgr(WM_CTX_SDL, this);

    skWindow* win = mgr.create("Tetris",
                               m_settings.width,
                               m_settings.height,
                               WM_WF_SHOW_CENT_DIA);

    m_manager = new GameManager(win);
    m_manager->setSettings(m_settings);

    // Broadcast a size message so that handlers
    // can update rectangles appropriately.
    mgr.dispatchInitialEvents();

    while (mgr.processInteractive(true))
    {
        if (m_manager->hasOrphanedStates())
            m_manager->destroyOrphanedStates();
    }


    saveSettings();

    delete resource;

    delete m_manager;
    return 0;
}

int main(int argc, char** argv)
{
    skLogger log;
    log.setFlags(LF_STDOUT | LF_FILE | LF_TIMESTAMP | LF_DETAIL);
    log.open("Tetris.log");

    try
    {
        Application app;
        if (app.parseCommandLine(argc, argv) != 0)
            return 1;

        return app.run();
    }
    catch (...)
    {
        skLogd(LD_ERROR, "An unknown exception occurred\n");
    }

    return 1;
}
