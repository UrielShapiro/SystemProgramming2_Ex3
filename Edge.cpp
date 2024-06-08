#include "Edge.hpp"

ariel::Edge::Edge(const short id): is_taken(false), road_owner(NULL), ID(id) {}

void ariel::Edge::set_road(const Player &p)
{
    this->road_owner = p;
    this->is_taken = true;
}