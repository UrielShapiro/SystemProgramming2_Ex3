#pragma once
#include "Player.hpp"
#include "Tile.hpp"

#define NUM_OF_TILES 19

enum MapValues
{
    FOREST,
	HILL,
	MOUNTAIN,
	FIELD,
	PASTURES,
	DESERT
};

namespace ariel
{
    class Board
    {
        private:
            Tile tiles[NUM_OF_TILES];

        public:
        Board();
        void initialize_board();
    };
}