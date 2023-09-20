#pragma once

#include <bit>
#include <bits/stdc++.h>
#include "./CellType.hpp"

inline int getBit(int i, int j) {
    return (i << 2) + (j >> 1);
}

namespace Engine {
    struct State {
        // [32; 63] bits - Quens
        // [ 0; 31] bits - Pawns
        unsigned long long black, white;
        
        // [0; 31] bits - Last moved figure
        // 32 bit - Current player step (0 - First player; 1 - Second player)
        unsigned long long flags;

        State() {
            // Default State
            black = 0x0000000000000fffull;
            white = 0x00000000fff00000ull;
            flags = 0;
        }

        Engine::CellType get(int i, int j) {
            unsigned long long needle = (1ull << getBit(i, j));

            if (black & (needle <<  0)) return Engine::CellType::BLACK_PAWN;
            if (black & (needle << 32)) return Engine::CellType::BLACK_QUEEN;
            if (white & (needle <<  0)) return Engine::CellType::WHITE_PAWN;
            if (white & (needle << 32)) return Engine::CellType::WHITE_QUEEN;
            return Engine::CellType::NONE;
        }

        void set(int i, int j, Engine::CellType type) {
            unsigned long long mask = std::numeric_limits<unsigned long long>::max();
            unsigned long long needle = (1ull << getBit(i, j));
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

        bool currentPlayer() {
            return flags & (1ull << 32);
        }

        unsigned long long lastStepMask() {
            return flags & 0xffffffffull;
        }

        std::pair<int, int> lastStep() {
            auto mask = lastStepMask();
            if (mask == 0) return {-1, -1};
            auto cnt = std::__countr_zero(mask);
            int i = (cnt >> 4);
            int j = ((cnt & 3) << 1) | ((i & 1) ^ 1);
            return {i, j};
        }
    };
}