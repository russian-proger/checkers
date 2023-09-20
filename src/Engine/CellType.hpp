#pragma once

namespace Engine {
    enum CellType {
        NONE,
        BLACK_PAWN = 0b10,
        WHITE_PAWN = 0b11,
        WHITE_QUEEN = 0b100,
        BLACK_QUEEN = 0b101,
    };
}