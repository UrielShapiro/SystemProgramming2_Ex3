#include "Edge.hpp"

ariel::Edge::Edge(): is_taken(false), road_owner(NULL) {}

void ariel::Edge::set_road(const Player &p)
{
    this->road_owner = p;
    this->is_taken = true;
}