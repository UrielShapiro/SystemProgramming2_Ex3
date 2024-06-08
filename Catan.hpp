#pragma once
#include "Player.hpp"
#include "Board.hpp"

#define MAX_NUM_OF_PLAYERS 3
#define POINTS_TO_WIN 10

namespace GameConsts
{
    enum ResourceCard
    {
        Brick,
        Wood,
        Ore,
        Grain,
        Wool
    };
    enum MapValues
    {
        FOREST,
        HILL,
        MOUNTAIN,
        FIELD,
        PASTURES,
        SEA,
        DESERT
    };
}

namespace ariel
{
    class Catan
    {
    private:
        Player players[MAX_NUM_OF_PLAYERS];
        Board &board;

    public:
        Catan();
    }
}