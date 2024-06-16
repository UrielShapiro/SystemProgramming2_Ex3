/**
 * @ID: 9745
 * @name: Uriel Shapiro
 * @email: uriel1999@gmail.com
 */

#include "Edge.hpp"

ariel::Edge::Edge(const short id) : road_owner(NULL), is_taken(false), ID(id) {}

void ariel::Edge::set_road(Player &p)
{
    this->road_owner = &p;
    this->is_taken = true;
}

bool ariel::Edge::isTaken() const
{
    return this->is_taken;
}

short ariel::Edge::get_id() const
{
    return this->ID;
}

const ariel::Player *ariel::Edge::get_owner() const
{
    if (!this->is_taken)
    {
        return nullptr;
    }
    return this->road_owner;
}
