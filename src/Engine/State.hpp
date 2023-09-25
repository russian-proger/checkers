#pragma once

#include <bits/stdc++.h>
#include "Types.hpp"

namespace Engine {

    struct State {
        // [32; 63] bits - Quens
        // [ 0; 31] bits - Pawns
        Bit black, white;
        
        // [0; 4] bits - Pivot of compound step
        // 5 bit - Is compound step
        // 6 bit - Current player step (1 - White player; 0 - Black player)
        Bit flags;

        State();

        // Default State
        void reset();

        // Return figure type at the given position
        CellType get(int idx) const;

        // Set the given figure type at the given position
        void set(int bit, CellType type);

        // Return current player (who making next step)
        PlayerColor getPlayer() const;

        // Set the current player
        void setPlayer(bool v);

        // Toggle player (white -> black, black -> white)
        void togglePlayer();

        // Return  last step position
        Bit getPivot() const;

        // Set last step position
        void setPivot(Bit v);

        // Is the step compound
        bool isCompound() const;

        // Set step compound status
        void setCompound(bool v);

        bool isEmpty() const;
    };
}