#pragma once

namespace Engine {
    enum CellType {
        NONE        = 0b000,
        BLACK_PAWN  = 0b010,
        BLACK_QUEEN = 0b011,
        WHITE_PAWN  = 0b100,
        WHITE_QUEEN = 0b101,
    };
}