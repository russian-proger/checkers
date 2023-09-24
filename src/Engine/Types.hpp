#pragma once

#include <utility>

namespace Engine {
    typedef unsigned long long Bit;
    typedef std::pair<int,int> Position;

    enum CellType {
        NONE        = 0b000,
        BLACK_PAWN  = 0b010,
        BLACK_QUEEN = 0b011,
        WHITE_PAWN  = 0b100,
        WHITE_QUEEN = 0b101,
    };

    enum PlayerColor {
        BLACK       = 0,
        WHITE       = 1,
    };
}