#include "Buildable.hpp"

ariel::Buildable::Buildable(const Player &p) : owner(p) {}

ariel::Village::Village(Player &p) : Buildable(p)
{
}

const void ariel::Buildable::get_resources(size_t amount)
{
    for (MapValues &resource : this->resources)
    {
        this->owner.add_resource(resource, amount);
    }
}