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
#ifndef _Piece_h_
#define _Piece_h_

#include "Math/skRectangle.h"
#include "State.h"

class Pieces
{
public:
    enum PieceRotation
    {
        North,
        East,
        South,
        West,
        PieceRotationMax
    };

    enum PieceColor
    {
        Transparent,
        ColorRed,
        ColorOrange,
        ColorYellow,
        ColorGreen,
        ColorBlueGreen,
        ColorBlue,
        ColorViolet,
        ColorRedViolet,
        PieceColorMax,
        //
        ColorText,
        ColorTextFaded,
        ColorTextFadedMore,
        ColorShadow,

        //
        SemiTransp,
    };

    enum GamePiece
    {
        SquareShape,
        LineShape,
        TShape,
        LShape,
        LMirrorShape,
        NShape,
        NMirrorShape,
        GamePieceMax
    };

    struct GridPiece
    {
        /// <summary>
        /// Bounding box offsets from the center pivot
        /// in the order of: l,t,r,b
        /// </summary>
        SKbyte bb[4];
        SKbyte block[5][5];
    };

private:
    static GridPiece Objects[GamePieceMax][PieceRotationMax];

public:
    static void getGridPiece(GridPiece& dest, int piece, int rotation);
};

using Piece = Pieces::GridPiece;

#endif  //Piece
