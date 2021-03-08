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
#include "Board.h"
#include "Piece.h"
#include "RenderUtils.h"
#include "Utils/skPlatformHeaders.h"
#include "Utils/skRandom.h"

using R = Resources;



Board::Board(SKint32 type) :
    m_game(nullptr),
    m_board(nullptr),
    m_boardRows(0),
    m_boardColumns(0),
    m_boardSize(0),
    m_cPiece(),
    m_nPiece(),
    m_init(false),
    m_mergeCount(0),
    m_cBlock({}),
    m_nBlock({})
{
    initialize(skClamp<SKint32>(type, 0, 2));
}

Board::~Board()
{
    finalize();
}

void Board::initialize(SKint32 type)
{
    switch (type)
    {
    case 0:
        m_boardRows    = 20;
        m_boardColumns = 10;
        break;
    case 1:
        m_boardRows    = 30;
        m_boardColumns = 15;
        break;
    case 2:
        m_boardRows    = 40;
        m_boardColumns = 20;
        break;
    default:
        m_boardRows    = 30;
        m_boardColumns = 15;
        break;
    }

    m_boardSize = m_boardRows * m_boardColumns;

    m_board = new SKbyte[m_boardSize * sizeof(SKbyte)];
    m_game  = new SKbyte[m_boardSize * sizeof(SKbyte)];

    reset();
    selectRandom(m_cBlock);
    selectRandom(m_nBlock);
}

inline SKint32 Board::GetIDX(SKint32 r, SKint32 c) const
{
    return r * m_boardColumns + c;
}

void Board::finalize()
{
    delete[] m_board;
    delete[] m_game;

    m_board = nullptr;
    m_game  = nullptr;
}

void Board::clear() const
{
    for (SKint32 i = 0; i < m_boardSize; ++i)
        m_game[i] = 0;
}

void Board::reset() const
{
    for (SKint32 i = 0; i < m_boardSize; ++i)
    {
        m_game[i]  = 0;
        m_board[i] = 0;
    }
}

void Board::selectRandom(RandomState& block)
{
    block.color    = (SKuint8)skRandRange(Pieces::ColorRed, Pieces::PieceColorMax);
    block.rotation = (SKuint8)skRandRange(0, Pieces::PieceRotationMax);
    block.type     = (SKuint8)skRandRange(0, Pieces::GamePieceMax);
}

void Board::updateRandomState()
{
    if (!m_init)
    {
        m_cBlock.color    = (SKuint8)skRandRange(Pieces::ColorRed, Pieces::PieceColorMax);
        m_cBlock.rotation = (SKuint8)skRandRange(0, Pieces::PieceRotationMax);
        m_cBlock.type     = (SKuint8)skRandRange(0, Pieces::GamePieceMax);
    }

    m_nBlock.color    = (SKuint8)skRandRange(Pieces::ColorRed, Pieces::PieceColorMax);
    m_nBlock.rotation = (SKuint8)skRandRange(0, Pieces::PieceRotationMax);
    m_nBlock.type     = (SKuint8)skRandRange(0, Pieces::GamePieceMax);
}

void Board::drop()
{
    if (!m_init)
    {
        m_init = true;
        Pieces::getGridPiece(m_cPiece, m_cBlock.type, m_cBlock.rotation);
        Pieces::getGridPiece(m_nPiece, m_nBlock.type, m_nBlock.rotation);
    }
    else
    {
        m_cBlock = m_nBlock;
        m_cPiece = m_nPiece;

        selectRandom(m_nBlock);
        Pieces::getGridPiece(m_nPiece, m_nBlock.type, m_nBlock.rotation);
    }
}

void Board::rotate()
{
    m_cBlock.rotation += 1;
    if (m_cBlock.rotation >= 4)
        m_cBlock.rotation = 0;
    Pieces::getGridPiece(m_cPiece, m_cBlock.type, m_cBlock.rotation);
}

bool Board::isInsideBoard(const SKint32& x, const SKint32& y) const
{
    return x >= 0 && x < m_boardColumns && y >= 0 && y < m_boardRows;
}

void Board::movePiece(SKint32 x, SKint32 y)
{
    const SKint32 cx = x - 2;
    const SKint32 cy = y - 2;

    for (SKint32 r = 0; r < 5; ++r)
    {
        for (SKint32 c = 0; c < 5; ++c)
        {
            const SKuint8& pCell = m_cPiece.block[r][c];

            SKint32 ic = cx + c;
            SKint32 ir = cy + r;

            if (isInsideBoard(ic, ir))
            {
                const SKint32 idx = GetIDX(ir, ic);
                if (idx < m_boardSize)
                {
                    if (pCell == 0)
                        m_game[idx] = Pieces::Transparent;
                    else
                        m_game[idx] = m_cBlock.color;
                }
            }
        }
    }
}

void Board::mergePiece(SKint32 x, SKint32 y) const
{
    const SKint32 cx = x - 2;
    const SKint32 cy = y - 2;

    for (SKint32 r = 0; r < 5; ++r)
    {
        for (SKint32 c = 0; c < 5; ++c)
        {
            const SKbyte& pCell = m_cPiece.block[r][c];

            SKint32 ic = cx + c;
            SKint32 ir = cy + r;

            if (isInsideBoard(ic, ir))
            {
                const SKint32 idx = GetIDX(ir, ic);
                if (idx < m_boardSize)
                {
                    if (pCell != 0)
                    {
                        m_board[idx] = m_cBlock.color;
                        m_game[idx]  = 0;
                    }
                }
            }
        }
    }
}

bool Board::hasCollisions(SKint32 x, SKint32 y)
{
    const SKint32 cx = x - 2;
    const SKint32 cy = y - 2;

    if (cy + 1 + m_cPiece.bb[3] >= m_boardRows - 2)
        return true;

    for (SKint32 r = 0; r < 5; ++r)
    {
        for (SKint32 c = 0; c < 5; ++c)
        {
            const SKbyte& pCell = m_cPiece.block[r][c];

            SKint32 ic = cx + c;
            SKint32 ir = cy + r + 1;

            if (isInsideBoard(ic, ir))
            {
                const SKint32 idx = GetIDX(ir, ic);
                if (idx < m_boardSize)
                {
                    const SKbyte& bCell = m_board[idx];
                    if (bCell != 0 && pCell != 0)
                        return true;
                }
            }
        }
    }
    return false;
}

bool Board::isGameOver() const
{
    for (SKint32 c = 0; c < m_boardColumns; ++c)
    {
        if (m_board[c] != 0)
            return true;
    }
    return false;
}

void Board::mergeAndShift()
{
    m_mergeCount = 0;

    SKint32 c;
    for (SKint32 r = m_boardRows - 1; r >= 0 && m_mergeCount < m_boardRows; --r)
    {
        bool full = true;
        for (c = 0; c < m_boardColumns && full; ++c)
        {
            const SKint32 idx = GetIDX(r, c);
            if (idx > m_boardSize)
                return;

            if (m_board[idx] == 0)
                full = false;
        }

        if (full)
        {
            m_mergeCount++;
            for (SKint32 rm1 = r - 1; rm1 >= 1; --rm1, --r)
            {
                for (c = 0; c < m_boardColumns; ++c)
                {
                    const SKint32 idx1 = GetIDX(r, c);
                    const SKint32 idx2 = GetIDX(rm1, c);
                    if (idx1 < m_boardSize && idx2 < m_boardSize)
                        m_board[idx1] = m_board[idx2];
                }
            }

            r = m_boardRows;
        }
    }
}

void Board::fill(const skRectangle& rect, const skScalar& blockSize) const
{
    skScalar x = rect.x;
    skScalar y = rect.y;

    for (SKint32 r = 0; r < m_boardRows; ++r)
    {
        for (SKint32 c = 0; c < m_boardColumns; ++c)
        {
            const SKint32 idx = GetIDX(r, c);
            if (idx < m_boardSize)
            {
                const SKbyte& gState = m_game[idx];
                if (gState != 0)
                    RU::displayBlock(m_cBlock.color, x, y, blockSize);

                const SKbyte& bState = m_board[idx];
                if (bState != 0)
                    RU::displayBlock(bState, x, y, blockSize);
            }

            x += blockSize;
        }
        x = rect.x;
        y += blockSize;
    }
}

void Board::showNext(const skRectangle& rect, const skScalar& blockSize) const
{
    skRectangle borderRect = rect;
    borderRect.expand(2, 2);

    skScalar x = borderRect.x;
    skScalar y = borderRect.y;

    for (SKint32 r = 0; r < 5; ++r)
    {
        for (SKint32 c = 0; c < 5; ++c)
        {
            const SKbyte& pCell = m_nPiece.block[r][c];

            if (pCell != 0)
                RU::displayBlock(m_nBlock.color, x, y, blockSize);
            x += blockSize;
        }
        x = borderRect.x;
        y += blockSize;
    }
}
