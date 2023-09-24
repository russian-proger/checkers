#include "./State.hpp"

typedef unsigned long long ull;

namespace Engine {
    int getBit(int i, int j) {
        return (i << 2) + (j >> 1);    
    }

    std::pair<int,int> getCoords(int b) {
        int i = b >> 2;
        int j = ((b & 3) << 1) | ((i & 1) ^ 1);
        return {i, j};
    }

    int sign(int v) {
        if (v < 0) return -1;
        if (v > 0) return  1;
        return 0;
    }

    void State::reset() {
        black = 0x0000000000000fffull;
        white = 0x00000000fff00000ull;
        flags = 0b1000000;
    }

    State::State() {
        reset();
    }

    Engine::CellType State::get(int bit) {
        ull needle = 1ull << bit;
        if (black & (needle <<  0)) return Engine::CellType::BLACK_PAWN;
        if (black & (needle << 32)) return Engine::CellType::BLACK_QUEEN;
        if (white & (needle <<  0)) return Engine::CellType::WHITE_PAWN;
        if (white & (needle << 32)) return Engine::CellType::WHITE_QUEEN;
        return Engine::CellType::NONE;
    }

    Engine::CellType State::getByCoords(int i, int j) {
        return this->get(Engine::getBit(i, j));
    }

    void State::set(int bit, Engine::CellType type) {
        ull mask = std::numeric_limits<ull>::max();
        ull needle = (1ull << bit);

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

    void State::setByCoords(int i, int j, Engine::CellType type) {
        this->set(Engine::getBit(i, j), type);
    }

    bool State::currentPlayer() {
        return flags & (1ull << 6);
    }

    void State::setPlayer(bool v) {
        flags = flags & (1ull<<6) | ((ull)(v)<<6);
    }

    void State::togglePlayer() {
        flags ^= (1ull<<6);
    }

    void State::setSeriesPosition(ull v) {
        flags = ~(~flags | 0x1full) | (v & 0x1full);
    }

    ull State::getSeriesPosition() {
        return flags & 0x1full;
    }

    bool State::isSeries() {
        return (flags >> 5) & 1ull;
    }

    void State::setSeries(bool v) {
        flags = (~flags | 0x20full) | ((ull)(v)<<5);
    }

    int State::lastStepBit() {
        if (flags & 0x20ull) return flags&0x1full;
        return -1;
    }

    std::pair<int,int> State::lastStepCoords() {
        return getCoords(lastStepBit());
    }

    void State::canBeat(int bit) {
        
    }

    bool State::isValid(int sbit, int fbit) {
        CellType stype = get(sbit);
        CellType ftype = get(fbit);
        
        if (stype == CellType::NONE || ftype != CellType::NONE || !(stype & (1ull << 1 + currentPlayer()))) return false;
        
        auto [i1, j1] = getCoords(sbit);
        auto [i2, j2] = getCoords(fbit);
        if (abs(i1 - i2) != abs(j1 - j2)) return false;

        int di = i2 - i1;
        int dj = j2 - j1;
        int si = sign(di);
        int sj = sign(dj);

        if (stype & 1 ^ 1) {
            // Pawn
            if (di * si == 1) return si == 1 - (currentPlayer()<<1);
            if (di * si == 2) {
                CellType mtype = getByCoords((i1 + i2) >> 1, (j1 + j2) >> 1);
                return (mtype ^ stype) & 6 && mtype;
            }
            return false;
        }

        int cnt = 0;
        for (int i = 1; i < di*si; i++) {
            int ii = i1 + si*i;
            int jj = j1 + sj*i;
            int tt = getByCoords(ii, jj);
            if (tt & stype & 0b110) return false;
            if (tt) cnt++;
        }

        if (cnt <= 0) return false;
        return true;
    }

    void State::makeStep(int sbit, int fbit) {
        auto [i1, j1] = getCoords(sbit);
        auto [i2, j2] = getCoords(fbit);

        int di = i2 - i1;
        int dj = j2 - j1;
        int si = sign(di);
        int sj = sign(dj);

        CellType stype = get(sbit);
        set(fbit, stype);
        for (int i = 0; i < di*si; i++) {
            int ii = i1 + si*i;
            int jj = j1 + sj*i;
            setByCoords(ii, jj, NONE);
        }

        if (stype & 1) {
            // Queen
        } else {
            // Pawn
            if (di * si == 1) {
                flags &= 0b1000000;
                flags ^= 0b1000000;
            } else {
                auto check = [&](int ddi, int ddj, int i, int j) -> bool {
                    int fi = i + ddi * 2;
                    int fj = j + ddj * 2;
                    if (fi < 0 || 8 <= fi || fj < 0 || 8 <= fj) return false;
                    CellType stype = getByCoords(i, j);
                    CellType ftype = getByCoords(fi, fj);
                    CellType mtype = getByCoords(i + ddi, j + ddj);
                    return ftype == CellType::NONE && mtype && ((stype ^ mtype) & 6);
                };

                if (check(-1, -1, i2, j2) || check(-1, 1, i2, j2) || check(1, -1, i2, j2) || check(1, 1, i2, j2)) {
                    flags &= 0b1000000;
                    flags |= 0b100000 | fbit;
                } else {;
                    flags &= 0b1000000;
                    flags ^= 0b1000000;
                }
            }
        }
    }
}