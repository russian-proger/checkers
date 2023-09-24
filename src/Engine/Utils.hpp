#pragma once

#include <utility>

#include "Types.hpp"

namespace Engine {

    inline bool between(int a, int b, int c) {
        return a <= b && b <= c;
    }

    // Coords -> BitPosition
    inline int convertToIdx(const int i, const int j) {
        return (i << 2) + (j >> 1);
    }

    inline int convertToIdx(const std::pair<int,int>& c) {
        return (c.first << 2) + (c.second >> 1);
    }

    // BitPosition -> Coords
    inline std::pair<int,int> convertToPosition(const int b) {
        int i = b >> 2;
        int j = ((b & 3) << 1) | ((i & 1) ^ 1);
        return {i, j};
    }

    // Return true if black board cell
    inline bool isValidCoords(std::pair<int,int> coords) {
        return ((coords.first ^ coords.second) & 1 != 0) &&
            between(0, coords.first,  7) &&
            between(0, coords.second, 7);
    }

    // Get Sign of Number
    inline int sign(const int v) {
        if (v < 0) return -1;
        if (v > 0) return  1;
        return 0;
    }

    // Return true if checker's color matches player
    inline bool sameColor(PlayerColor p, CellType c) {
        return c & (1ull<<p+1);
    }

    inline bool sameColor(CellType c, PlayerColor p) {
        return sameColor(p, c);
    }

    inline bool isPawn(CellType c) {
        return c & 1 ^ 1;
    }

    inline bool isQueen(CellType c) {
        return c & 1;
    }
}