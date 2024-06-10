#include "Edge.hpp"

ariel::Edge::Edge(const short id) : is_taken(false), road_owner(NULL), ID(id) {}

void ariel::Edge::set_road(Player &p)
{
    this->road_owner = &p;
    this->is_taken = true;
}

bool const ariel::Edge::isTaken() const
{
    return this->is_taken;
}

const short ariel::Edge::get_id() const
{
    return this->ID;
}

const ariel::Player *ariel::Edge::get_owner() const
{
    if(!this->is_taken)
    {
        return nullptr;
    }
    return this->road_owner;
}
