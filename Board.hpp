#pragma once
#include "Player.hpp"
#include "Tile.hpp"
#include "GameConsts.hpp"

#define NUM_OF_TILES 19
#define NUM_OF_VERTICES 54
#define NUM_OF_EDGES 73
#define EDGES_PER_TILE 6
#define VERTICES_PER_TILE 6

namespace ariel
{
    class Player;   // Forward declaration
    class Tile;     // Forward declaration
    class Board
    {
    private:
        std::vector<ariel::Tile*> tiles;
        std::vector<ariel::Edge*> edges;
        std::vector<ariel::Vertex*> vertices;
        static Board *instance;
        Board();

    public:
        Board(Board &b) = delete;               // Singleton should not be cloneable.
        void operator=(const Board &) = delete; // Singleton should not be assignable.
        static Board *get_instance();
        bool valid_settlement_placement(Vertex &v, Player &p);
        bool valid_road_placement(Edge &e, Player &p);
        std::vector<ariel::Tile*> get_tiles();
        std::vector<ariel::Edge*> get_edges();
        ~Board();
    };
}