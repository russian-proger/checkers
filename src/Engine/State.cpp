#include "State.hpp"

namespace Engine {

    void State::reset() {
        black = 0x0000000000000fffull;
        white = 0x00000000fff00000ull;
        flags = 0x40ull;
    }

    State::State() {
        reset();
    }

    CellType State::get(int idx) const {
        Bit needle = 1ull << idx;
        if (black & (needle <<  0)) return CellType::BLACK_PAWN;
        if (black & (needle << 32)) return CellType::BLACK_QUEEN;
        if (white & (needle <<  0)) return CellType::WHITE_PAWN;
        if (white & (needle << 32)) return CellType::WHITE_QUEEN;
        return CellType::NONE;
    }

    void State::set(int bit, CellType type) {
        Bit mask = ~0ull;
        Bit needle = (1ull << bit);

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

    PlayerColor State::getPlayer() const {
        return (PlayerColor)(flags >> 6 & 1ull);
    }

    void State::setPlayer(bool v) {
        flags = flags & (1ull<<6) | ((Bit)(v)<<6);
    }

    void State::togglePlayer() {
        flags ^= (1ull<<6);
    }

    void State::setPivot(Bit v) {
        flags = ~(~flags | 0x1full) | (v & 0x1full);
    }

    Bit State::getPivot() const {
        return flags & 0x1full;
    }

    bool State::isCompound() const {
        return (flags >> 5) & 1ull;
    }

    void State::setCompound(bool v) {
        flags = ~(~flags | 0x20ull) | ((Bit)(v)<<5);
    }

    bool State::isFinished() const {
        return white == 0 || black == 0;
    }
}