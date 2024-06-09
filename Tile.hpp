#pragma once
#include "Board.hpp"
#include "Edge.hpp"
#include "Vertex.hpp"

namespace ariel
{
    class Tile
    {
    private:
        short ID;
        short number_token;
        GameConsts::MapValues value;
        Edge edges[EDGES_PER_TILE];
        Vertex corners[VERTICES_PER_TILE];

    public:
        Tile(short id, short token, GameConsts::MapValues v, Edge e[EDGES_PER_TILE], Vertex c[VERTICES_PER_TILE]);
        const short get_ID() const;
        const short get_token() const;
        const GameConsts::MapValues get_value() const;
    };
}