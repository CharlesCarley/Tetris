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
#include "Piece.h"
#include "Utils/skMemoryStream.h"
#include "Utils/skPlatformHeaders.h"

static const Pieces::GridPiece NullPiece = {
    {0, 0, 0, 0},
    {
        {0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0},
    },
};

static const Pieces::GridPiece SquareN = {
    {-1, -1, 0, 0},
    {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 1, 2, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
    },
};

static const Pieces::GridPiece LineN = {
    {0, -2, 0, +1},
    {
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 2, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
    },
};

static const Pieces::GridPiece LineE = {
    {-1, 0, +2, 0},
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 2, 1, 1},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
    },
};

static const Pieces::GridPiece LineS = {
    {0, -1, 0, +2},
    {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 2, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
    },
};

static const Pieces::GridPiece LineW = {
    {-2, 0, +1, 0},
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {1, 1, 2, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
    },
};

static const Pieces::GridPiece TShapeN = {
    {-1, -1, +1, 0},
    {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 2, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
    },
};

static const Pieces::GridPiece TShapeE = {
    {0, -1, +1, +1},
    {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 2, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
    },
};

static const Pieces::GridPiece TShapeS = {
    {-1, 0, +1, +1},
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 2, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
    },
};

static const Pieces::GridPiece TShapeW = {
    {-1, -1, 0, +1},
    {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 2, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
    },
};

static const Pieces::GridPiece LShapeN = {
    {0, -1, +1, +1},
    {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 2, 0, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 0, 0, 0},
    },
};

static const Pieces::GridPiece LShapeE = {
    {-1, 0, +1, +1},
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 2, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0},
    },
};

static const Pieces::GridPiece LShapeS = {
    {-1, -1, 0, +1},
    {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 2, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
    },
};

static const Pieces::GridPiece LShapeW = {
    {-1, -1, +1, 0},
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 2, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
    },
};

static const Pieces::GridPiece LMShapeN = {
    {-1, -1, 0, +1},
    {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 2, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0},
    },
};

static const Pieces::GridPiece LMShapeE = {
    {-1, -1, +1, 0},
    {
        {0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 2, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
    },
};

static const Pieces::GridPiece LMShapeS = {
    {0, -1, +1, +1},
    {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 2, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
    },
};

static const Pieces::GridPiece LMShapeW = {
    {-1, 0, +1, +1},
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 2, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0},
    },
};

static const Pieces::GridPiece NShapeN = {
    {0, -1, +1, +1},
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 2, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
    },
};

static const Pieces::GridPiece NShapeE = {
    {-1, 0, +1, +1},
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 2, 0, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 0, 0, 0},
    },
};

static const Pieces::GridPiece NShapeS = {
    {-1, -1, 0, +1},
    {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 2, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0},
    },
};

static const Pieces::GridPiece NShapeW = {
    {-1, -1, +1, 0},
    {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 2, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
    },
};

static const Pieces::GridPiece NMShapeN = {
    {-1, -1, 0, +1},
    {
        {0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 2, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
    },
};

static const Pieces::GridPiece NMShapeE = {
    {-1, 0, +1, +1},
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 2, 1, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0},
    },
};

static const Pieces::GridPiece NMShapeS = {
    {0, -1, +1, +1},
    {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 2, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0},
    },
};

static const Pieces::GridPiece NMShapeW = {
    {-1, -1, +1, 0},
    {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 1, 0},
        {0, 1, 2, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
    },
};

void Pieces::getGridPiece(GridPiece& dest, int piece, int rotation)
{
    if (piece < GamePieceMax && rotation < PieceRotationMax)
    {
        if (piece >= 0 && rotation >= 0)
        {
            skMemcpy(&dest, &Objects[piece][rotation], sizeof(Pieces::GridPiece));
            return;
        }
    }
    skMemcpy(&dest, &NullPiece, sizeof(Pieces::GridPiece));
}

Pieces::GridPiece Pieces::Objects[7][4] = {
    // SquareShape
    {
        SquareN,
        SquareN,
        SquareN,
        SquareN,
    },

    // Line Shape
    {
        LineN,
        LineE,
        LineS,
        LineW,
    },

    // T Shape
    {
        TShapeN,
        TShapeE,
        TShapeS,
        TShapeW,
    },

    // L Shape
    {
        LShapeN,
        LShapeE,
        LShapeS,
        LShapeW,
    },

    // L Mirror Shape
    {
        LMShapeN,
        LMShapeE,
        LMShapeS,
        LMShapeW,
    },

    // N Shape
    {
        NShapeN,
        NShapeE,
        NShapeS,
        NShapeW,
    },

    // N Mirror Shape
    {
        NMShapeN,
        NMShapeE,
        NMShapeS,
        NMShapeW,
    },
};
