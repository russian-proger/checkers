#include "Controller.hpp"

Engine::Position directions[4] = {
    {-1, -1},
    {-1,  1},
    { 1, -1},
    { 1,  1},
};

namespace Engine {
    Controller::Controller() {
        reset();
    }

    void Controller::reset() {
        state.reset();
    }
    
    CellType Controller::get(const Position& pos) const {
        return state.get(convertToIdx(pos));
    }
    
    CellType Controller::operator[](const Position& pos) const {
        return state.get(convertToIdx(pos));
    }

    void Controller::set(const Position& pos, CellType type) {
        return state.set(convertToIdx(pos), type);
    }

    bool Controller::isCompound() const {
        return state.isCompound();
    }

    PlayerColor Controller::getPlayer() const {
        return state.getPlayer();
    }

    bool Controller::isPickable(const Position& pos) const {
        return sameColor(get(pos), getPlayer());
    }

    bool Controller::isOpposite(const Position& pos) const {
        return sameColor(get(pos), (PlayerColor)(!getPlayer()));
    }

    bool Controller::canAttack(const Position& pos) const {
        if (!isPickable(pos)) return false;

        for (int d_idx = 0; d_idx < 4; d_idx++) {
            const Position& d_pos = directions[d_idx];

            if (isPawn(get(pos))) {
                if (
                    isValidCoords({pos.first + (d_pos.first << 1), pos.second + (d_pos.second << 1)}) &&
                    get({pos.first + (d_pos.first << 1), pos.second + (d_pos.second << 1)}) == CellType::NONE &&
                    isOpposite({pos.first + d_pos.first, pos.second + d_pos.second})
                ) return true;
            }
            else {
                bool opposite_found = false;
                Position i_pos = {pos.first + d_pos.first, pos.second + d_pos.second};
                while (isValidCoords(i_pos)) {

                    if (isOpposite(i_pos)) {
                        if (opposite_found) break;
                        opposite_found = true;
                    }
                    else if (isPickable(i_pos)) break;
                    else if (opposite_found) return true;

                    i_pos.first += d_pos.first;
                    i_pos.second += d_pos.second;
                }
            }
        }

        return false;
    }

    bool Controller::canAttack() const {
        for (int c_idx = 0; c_idx < 32; c_idx++) {
            Position pos = convertToPosition(c_idx);
            if (canAttack(pos)) return true;
        }

        return false;
    }

    bool Controller::isFinished() const {
        if (state.isEmpty()) return false;
        for (int i = 0; i < 32; i++) {
            for (int j = 0; j < 32; j++) {
                if (isPossibleMove(convertToPosition(i), convertToPosition(j))) {
                    return false;
                }
            }
        }
        return true;
    }

    bool Controller::isPossibleMove(const Position& from, const Position& to) const {
        CellType ct_from = get(from);
        CellType ct_to   = get(to);

        if (!isPickable(from) || ct_to != CellType::NONE) return false;
        if (isCompound() && convertToPosition(state.getPivot()) != from) return false;
        
        int di = to.first  - from.first;
        int dj = to.second - from.second;

        int si = sign(di);
        int sj = sign(dj);

        // If not diagonal
        if (di*si != dj*sj || di == 0) return false;

        if (isPawn(ct_from)) {
            if (di*si == 1) return si == 1 - getPlayer() * 2 && !canAttack() && !isCompound();
            if (di*si  > 2) return false;
            return isOpposite({from.first + si, from.second + sj});
        } else {
            int oppo_count = 0;
            int self_count = 0;
            Position pos = from;
            while (pos != to) {
                pos.first += si;
                pos.second += sj;
                oppo_count += isOpposite(pos);
                self_count += isPickable(pos);
            }
            return (oppo_count == 0 && !isCompound() && !canAttack() || oppo_count == 1) && self_count == 0;
        }

        return true;
    }

    void Controller::move(const Position& from, const Position& to) {
        
        int di = to.first  - from.first;
        int dj = to.second - from.second;

        int si = sign(di);
        int sj = sign(dj);

        set(to, get(from));

        bool is_attack = false;

        Position i_pos = from;
        while (i_pos != to) {
            if (isOpposite(i_pos)) is_attack = true;
            set(i_pos, CellType::NONE);
            i_pos.first  += si;
            i_pos.second += sj;
        }

        if (to.first == 0 && getPlayer() == PlayerColor::WHITE || to.first == 7 && getPlayer() == PlayerColor::BLACK) {
            state.set(convertToIdx(to), (CellType)(get(to)|1));
        }

        if (is_attack && canAttack(to)) {
            state.setPivot(convertToIdx(i_pos));
            state.setCompound(true);
        }
        else {
            state.setCompound(false);
            state.togglePlayer();
        }
    }
}