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
#ifndef _RenderUtils_h_
#define _RenderUtils_h_

#include "Resources.h"
#include "Math/skRectangle.h"
#include "Utils/skString.h"

class RenderUtils
{
public:
    static void getTextRect(const Resources& R, skRectangle& dest, const StaticString& text);

    static void displayString(const Resources& R, skScalar x, skScalar y, const StaticString& text);
    static void displayStringSm(const Resources& R, skScalar x, skScalar y, const StaticString& text);

    static void displayDropShadow(const Resources& R, skScalar x, skScalar y, const StaticString& text);

    static void displayDropShadow(const Resources& R, skScalar x, skScalar y, const skString& text);

    static void clear();

    static void setColorFromEnum(const SKuint8& col);

    static void displayBlock(const SKuint8& col, skScalar x, skScalar y, skScalar size, const skScalar shadowDist=3.33333f);

    static void displayGrayedBlock(const SKuint8& col, skScalar x, skScalar y, skScalar size, const skScalar shadowDist = 3.33333f);

    static void displayBlockArt(const BlockArt &block, bool grey=false, skScalar opacity=1.f);
};

using RU = RenderUtils;

#endif  //_RenderUtils_h_
