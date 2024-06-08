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
        MapValues value;
        Edge edges[6];
        Vertex corners[6];

    public:
        Tile(short id, short token, MapValues v, Edge e[6], Vertex c[6]);
        const short get_ID() const;
        const short get_token() const;
        const MapValues get_value() const;
    };
}