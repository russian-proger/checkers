#pragma once

#include <limits>
#include "./CellType.hpp"

inline int getBit(int i, int j) {
    return (i << 2) + (j >> 1);
}

namespace Engine {
    struct State {
        // First 32 bit - Quens
        // Last  32 bit - Pawns
        unsigned long long black, white;
        
        // 0 - black
        // 1 - white
        // Default: white
        bool step;

        State() {
            // Default State
            black = 0x00000000fff00000;
            white = 0x0000000000000fff;
            step  = 1;
        }

        Engine::CellType get(int i, int j) {
            unsigned needle = (1 << getBit(i, j));

            if (black & (needle <<  0)) return Engine::CellType::BLACK_PAWN;
            if (black & (needle << 32)) return Engine::CellType::BLACK_QUEEN;
            if (white & (needle <<  0)) return Engine::CellType::BLACK_PAWN;
            if (white & (needle << 32)) return Engine::CellType::BLACK_QUEEN;
            return Engine::CellType::NONE;
        }

        void set(int i, int j, Engine::CellType type) {
            unsigned long long mask = std::numeric_limits<unsigned long long>::max();
            unsigned needle = (1 << getBit(i, j));
            mask ^= needle | (needle << 32);

            black &= mask;
            white &= mask;

            switch (type) {
                case BLACK_PAWN: {
                    black |= needle;
                    break;
                }
                case WHITE_PAWN: {
                    white |= needle;
                    break;
                }
                case BLACK_QUEEN: {
                    black |= (needle << 32);
                    break;
                }
                case WHITE_QUEEN: {
                    white |= (needle << 32);
                    break;
                }
            }
        }
    };
}