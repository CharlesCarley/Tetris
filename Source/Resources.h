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
#ifndef _Resources_h_
#define _Resources_h_

#include "Graphics/skGraphics.h"
#include "Utils/skSingleton.h"

class GameManager;
class State;

struct StaticString
{
    const char*   buf;
    const SKint32 len;
};

#define BlockArtWidth 26
#define BlockArtHeight 20

struct BlockArt
{
    const SKbyte art[BlockArtHeight][BlockArtWidth];
};


struct UserSettings
{
    SKint32 width;
    SKint32 height;
    SKint32 gridType;
    SKint64 topTen[10];
};



class Resources : public skSingleton<Resources>
{
public:
    SK_DECLARE_SINGLETON(Resources)

    SKfont Font;
    SKfont FontSm;

    static const SKint32 LevelSpeedMax = 1000000;
    static const SKint32 LevelSpeedMin = 100;
    static const SKint32 LevelStep     = 10000;

    static const SKuint32 Red;
    static const SKuint32 Orange;
    static const SKuint32 Yellow;
    static const SKuint32 Green;
    static const SKuint32 BlueGreen;
    static const SKuint32 Blue;
    static const SKuint32 Violet;
    static const SKuint32 RedViolet;

    static const SKuint32 Background;
    static const SKuint32 DarkBorder;
    static const SKuint32 Shadow;
    static const SKuint32 DarkerShadow;
    static const SKuint32 Text;
    static const SKuint32 TextFaded;
    static const SKuint32 TextFadedMore;

    static const StaticString Title;
    static const StaticString NewGame;
    static const StaticString HighScores;
    static const StaticString Settings;
    static const StaticString Exit;
    static const StaticString GameOver;

    static const StaticString GridSize;
    static const StaticString GS_10x20;
    static const StaticString GS_15x30;
    static const StaticString GS_20x40;

    static const SKuint32 background;
    static const SKint32  menuTextSize;
    static const SKuint32 menuTextColor;
    static const SKuint32 menuTextHighlight;

    static const BlockArt Splash;
    static const BlockArt GameBackground;

public:
    Resources();
    ~Resources() override;

    void load();

    void clearState() const;
};

#endif  //_Resources_h_
