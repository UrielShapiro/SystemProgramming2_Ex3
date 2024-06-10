#include "Tile.hpp"

ariel::Tile::Tile(short id, short token, GameConsts::MapValues v,
                  Edge (&e)[EDGES_PER_TILE], Vertex (&c)[VERTICES_PER_TILE]) : ID(id), number_token(token), value(v),
                                                                               edges{&e[0], &e[1], &e[2], &e[3], &e[4], &e[5]},
                                                                               corners{&c[0], &c[1], &c[2], &c[3], &c[4], &c[5]} {}

const short ariel::Tile::get_ID() const
{
    return this->ID;
}

const short ariel::Tile::get_token() const
{
    return this->number_token;
}

const GameConsts::MapValues ariel::Tile::get_value() const
{
    return this->value;
}

std::vector<ariel::Edge*> ariel::Tile::get_edges()
{
    return this->edges;
}

std::vector<ariel::Vertex*> ariel::Tile::get_vertices()
{
    return this->corners;
}