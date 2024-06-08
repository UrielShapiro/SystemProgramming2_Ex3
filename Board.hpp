#pragma once
#include "Player.hpp"
#include "Tile.hpp"

#define NUM_OF_TILES 19
#define NUM_OF_VERTICES 54
#define NUM_OF_EDGES 73
#define EDGES_PER_TILE 6
#define VERTICES_PER_TILE 6



namespace ariel
{
    class Board
    {
    private:
        std::vector<ariel::Tile> tiles;
        std::vector<ariel::Edge> edges;
        std::vector<ariel::Vertex> vertices;
        static Board *instance;
        Board();

    public:
        Board(Board &b) = delete;               // Singleton should not be cloneable.
        void operator=(const Board &) = delete; // Singleton should not be assignable.
        static Board *get_instance();
        ~Board();
    };
}