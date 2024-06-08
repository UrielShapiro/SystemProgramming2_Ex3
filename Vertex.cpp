#include "Vertex.hpp"

ariel::Vertex::Vertex(const MapValues resource[3]) : is_taken(false),
                                                     resouces{resource[0], resource[1], resource[2]} {}

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