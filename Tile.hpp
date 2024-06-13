#pragma once
#include "Board.hpp"
#include "Edge.hpp"
#include "Vertex.hpp"
#include "GameConsts.hpp"

#define EDGES_PER_TILE 6
#define VERTICES_PER_TILE 6

namespace ariel
{
    class Vertex; // Forward declaration
    class Edge;   // Forward declaration

    class Tile
    {
    private:
        short ID;
        int number_token;
        GameConsts::MapValues value;
        std::vector<Edge *> edges;
        std::vector<Vertex *> corners;

    public:
        Tile(short id, short token, GameConsts::MapValues v, Edge *e[EDGES_PER_TILE], Vertex *c[VERTICES_PER_TILE]);
        short get_ID() const;
        short get_token() const;
        std::vector<ariel::Edge *> get_edges();
        std::vector<ariel::Vertex *> get_vertices();
        GameConsts::MapValues get_value() const;
        ~Tile() = default;
    };
}