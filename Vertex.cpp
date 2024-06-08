#include "Vertex.hpp"

ariel::Vertex::Vertex(const MapValues resource1, const MapValues resource2,
                      const MapValues resource3, const short id) : is_taken(false), ID(id),
                                                                   resouces{resource1, resource2, resource3} {}

void ariel::Vertex::set_building(ariel::Buildable *b) // Village can be overwritten by city
{
    this->building = b;
    this->is_taken = true;
}

const ariel::Buildable *ariel::Vertex::get_building() const
{
    return this->building;
}

const bool ariel::Vertex::is_free() const
{
    return !this->is_taken;
}

const MapValues *ariel::Vertex::get_resources() const
{
    return this->resouces;
}
