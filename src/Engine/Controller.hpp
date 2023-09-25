#pragma once

#include <utility>

#include "State.hpp"
#include "Types.hpp"
#include "Utils.hpp"

namespace Engine {
    class Controller {
    
    protected:
        State state;

    public:
        Controller();

        // Reset game state
        void reset();

        // Return type of cell by position
        CellType get(const Position& pos) const;
        CellType operator[](const Position& pos) const;

        // Set type of cell by pos
        void set(const Position& pos, CellType type);

        // Return true if step consists of several moves
        bool isCompound() const;

        // Return current player color
        PlayerColor getPlayer() const;

        // Return true if given cell belonds to current player
        bool isFinished() const;

        // Return true if given cell belonds to current player
        bool isPickable(const Position& pos) const;

        // Return true if given cell belonds to opponent
        bool isOpposite(const Position& pos) const;

        // Return true if current player can attack
        bool canAttack() const;

        // Return true if current player can attack from given position
        bool canAttack(const Position& pos) const;

        // Return true if it is possible to move the figure to the given place
        bool isPossibleMove(const Position& from, const Position& to) const;

        // Make move by given positions
        void move(const Position& from, const Position& to);
    };

}