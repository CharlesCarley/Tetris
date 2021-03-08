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
#ifndef _Board_h_
#define _Board_h_

#include "Math/skRectangle.h"
#include "Piece.h"
#include "State.h"

struct RandomState
{
    SKint8 color;
    SKint8 type;
    SKint8 rotation;
    SKint8 unused;
};

class Board
{
private:
    SKbyte*     m_game;
    SKbyte*     m_board;
    SKint32     m_boardRows;
    SKint32     m_boardColumns;
    SKint32     m_boardSize;
    Piece       m_cPiece;
    Piece       m_nPiece;
    bool        m_init;
    int         m_mergeCount;
    RandomState m_cBlock;
    RandomState m_nBlock;

    static void selectRandom(RandomState& block);

    void updateRandomState();

    bool isInsideBoard(const SKint32& x, const SKint32& y) const;

    void initialize(SKint32 type);

    void finalize();

    SKint32 GetIDX(SKint32 r, SKint32 c) const;

public:
    explicit Board(SKint32 type);
    ~Board();

    SKint32 getBoardWidth() const
    {
        return m_boardColumns;
    }

    SKint32 getBoardHeight() const
    {
        return m_boardRows;
    }

    void clear() const;

    void drop();

    void rotate();

    void reset() const;

    bool isGameOver() const;

    void getPieceBoundingBox(SKint32& l, SKint32& t, SKint32& r, SKint32& b, SKint32& w, SKint32& h)
    {
        l = (SKint32)m_cPiece.bb[0];
        t = (SKint32)m_cPiece.bb[1];
        r = (SKint32)m_cPiece.bb[2];
        b = (SKint32)m_cPiece.bb[3];
        w = m_boardColumns;
        h = m_boardRows;
    }

    void movePiece(SKint32 x, SKint32 y);

    void mergePiece(SKint32 x, SKint32 y) const;

    void mergeAndShift();

    int getLastMergeCount() const
    {
        return m_mergeCount;
    }

    bool hasCollisions(SKint32 x, SKint32 y);

    void fill(const skRectangle& rect, const skScalar& blockSize) const;

    void showNext(const skRectangle& rect, const skScalar& blockSize) const;
};

#endif  //_Board_h_
