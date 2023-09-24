#pragma once

#include <bits/stdc++.h>
#include "CellType.hpp"

namespace Engine {

    int getBit(int i, int j);

    std::pair<int,int> getCoords(int b);

    int sign(int v);

    struct State {
        // [32; 63] bits - Quens
        // [ 0; 31] bits - Pawns
        unsigned long long black, white;
        
        // [0; 4] bits - Last moved figure
        // 5 bit - Current player step series
        // 6 bit - Current player step (1 - White player; 0 - Black player)
        unsigned long long flags;

        State();

        // Default State
        void reset();

        Engine::CellType get(int bit);

        Engine::CellType getByCoords(int i, int j);

        void set(int bit, Engine::CellType type);

        void setByCoords(int i, int j, Engine::CellType type);

        bool currentPlayer();

        void setPlayer(bool v);

        void togglePlayer();

        void setSeriesPosition(unsigned long long v);

        unsigned long long getSeriesPosition();

        bool isSeries();

        void setSeries(bool v);

        int lastStepBit();

        std::pair<int,int> lastStepCoords();

        void canBeat(int bit);

        bool isValid(int sbit, int fbit);

        void makeStep(int sbit, int fbit);
    };
}