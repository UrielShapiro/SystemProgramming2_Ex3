#pragma once
#include "Board.hpp"

#define MAX_NUM_OF_PLAYERS 3
#define POINTS_TO_WIN 10

namespace ariel
{
    class Catan
    {
    private:
        Player players[MAX_NUM_OF_PLAYERS];
        const Board *board;

    public:
        Catan(ariel::Player &p1, ariel::Player &p2, ariel::Player &p3);
        void const ChooseStartingPlayer();
    };
}