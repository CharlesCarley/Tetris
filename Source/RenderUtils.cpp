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
#include "RenderUtils.h"
#include "Piece.h"
#include "Resources.h"

void RenderUtils::getTextRect(const Resources& R, skRectangle& dest, const StaticString& text)
{
    SKint32 w = 0, h = 0;
    skGetFontTextExtent(R.Font, text.buf, text.len, &w, &h);
    dest.x      = 0;
    dest.y      = 0;
    dest.width  = (skScalar)w;
    dest.height = (skScalar)h;
}

void RenderUtils::displayString(const Resources& R, skScalar x, skScalar y, const StaticString& text)
{
    skDisplayString(R.Font, text.buf, text.len, x, y);
}

void RenderUtils::displayStringSm(const Resources& R, skScalar x, skScalar y, const StaticString& text)
{
    skDisplayString(R.FontSm, text.buf, text.len, x, y);
}

void RenderUtils::displayDropShadow(const Resources& R, skScalar x, skScalar y, const StaticString& text)
{
    skColor1ui(Resources::Shadow);
    skDisplayString(R.Font, text.buf, text.len, x + 5, y + 5);
    skColor1ui(Resources::Text);
    skDisplayString(R.Font, text.buf, text.len, x, y);
}

void RenderUtils::displayDropShadow(const Resources& R, skScalar x, skScalar y, const skString& text)
{
    const StaticString string = {text.c_str(), (SKint32)text.size()};
    displayDropShadow(R, x, y, string);
}

void RenderUtils::clear()
{
    skClearColor1i(Resources::Background);
    skProjectContext(SK_STANDARD);
    skClearContext();
}

void RenderUtils::setColorFromEnum(const SKuint8& col)
{
    using C = Pieces;
    using R = Resources;

    switch (col)
    {
    case C::SemiTransp:
        skColor1ui(0x00000080);
        break;
    case C::ColorRed:
        skColor1ui(R::Red);
        break;
    case C::ColorOrange:
        skColor1ui(R::Orange);
        break;
    case C::ColorYellow:
        skColor1ui(R::Yellow);
        break;
    case C::ColorGreen:
        skColor1ui(R::Green);
        break;
    case C::ColorBlueGreen:
        skColor1ui(R::BlueGreen);
        break;
    case C::ColorBlue:
        skColor1ui(R::Blue);
        break;
    case C::ColorViolet:
        skColor1ui(R::Violet);
        break;
    case C::ColorRedViolet:
        skColor1ui(R::RedViolet);
        break;
    case C::ColorText:
        skColor1ui(R::Text);
        break;
    case C::ColorTextFaded:
        skColor1ui(R::TextFaded);
        break;
    case C::ColorTextFadedMore:
        skColor1ui(R::TextFadedMore);
        break;
    case C::ColorShadow:
        skColor1ui(R::Shadow);
        break;
    default:
        skColor1ui(0);
        break;
    }
}

void RenderUtils::displayBlock(const SKuint8& col, skScalar x, skScalar y, skScalar size, const skScalar shadowDist)
{
    const skScalar shadowOffset = size / shadowDist;

    skRect(x + shadowOffset, y + shadowOffset, size, size);
    skColor1ui(Resources::Shadow);
    skFill();

    setColorFromEnum(col);
    skRect(x, y, size, size);
    skFill();
    skColor1ui(Resources::DarkBorder);
    skStroke();
}

void RenderUtils::displayGrayedBlock(const SKuint8& col, skScalar x, skScalar y, skScalar size, const skScalar shadowDist)
{
    skRect(x, y, size, size);
    if (col <= 1)
    {
        skColor1ui(Resources::TextFadedMore);
        skFill();
        skColor1ui(Resources::Shadow);
        skStroke();
    }
    else
    {
        skColor1ui(Resources::TextFadedMore);
        skStroke();
    }
}

void RenderUtils::displayBlockArt(const BlockArt& block, bool grey, skScalar opacity)
{
    skScalar wh[2] = {};
    skGetContext2f(SK_CONTEXT_SIZE, wh);

    skRectangle bb(0, 0, wh[0], wh[1]);

    skScalar blockSize = wh[1] / BlockArtHeight;
    bb.contract(blockSize, blockSize);

    blockSize = bb.height / BlockArtHeight;

    const skScalar gw = blockSize * BlockArtWidth;
    const skScalar gh = blockSize * BlockArtHeight;

    const skVector2 ip(bb.cx() - gw / 2.f, bb.cy() - gh / 2.f);

    skSetContext1f(SK_OPACITY, opacity);

    skScalar x = ip.x, y = ip.y;
    for (SKint32 i = 0; i < BlockArtHeight; ++i)
    {
        for (SKint32 j = 0; j < BlockArtWidth; ++j)
        {
            if (block.art[i][j] != 0)
            {
                if (grey)
                    displayGrayedBlock(block.art[i][j], x, y, blockSize, 7.f);
                else
                    displayBlock(block.art[i][j], x, y, blockSize, 7.f);
            }

            x += blockSize;
        }
        x = ip.x;
        y += blockSize;
    }

    skSetContext1f(SK_OPACITY, 1);
}
