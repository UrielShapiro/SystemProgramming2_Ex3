/**
 * @ID: 9745
 * @name: Uriel Shapiro
 * @email: uriel1999@gmail.com
 */

#include "Vertex.hpp"

ariel::Vertex::Vertex(const GameConsts::MapValues resource1, const GameConsts::MapValues resource2,
                      const GameConsts::MapValues resource3, const short id) : building(nullptr), ID(id), is_taken(false),
                                                                               resouces{resource1, resource2, resource3} {}

void ariel::Vertex::set_building(ariel::Buildable *b) // Village can be overwritten by city
{
    this->building = b;
    this->is_taken = true;
}

ariel::Buildable *ariel::Vertex::get_building()
{
    return this->building;
}

bool ariel::Vertex::is_free() const
{
    return !this->is_taken;
}

const GameConsts::MapValues *ariel::Vertex::get_resources() const
{
    return this->resouces;
}

short ariel::Vertex::get_id() const
{
    return this->ID;
}
