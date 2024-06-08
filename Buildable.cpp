#include "Buildable.hpp"

ariel::Buildable::Buildable(const Player &p, const MapValues *resources_list) : owner(p), resources{*resources_list} {}

const MapValues *ariel::Buildable::get_resources() const
{
    return this->resources;
}

const ariel::Player &ariel::Buildable::get_owner() const
{
    return this->owner;
}

ariel::Village::Village(const Player &p, const MapValues *resources_list) : Buildable(p, resources_list) {}

const void ariel::Village::get_resources(size_t amount)
{
    for (MapValues &resource : this->resources)
    {
        this->owner.add_resource(resource, amount);
    }
}

ariel::City::City(const Player &p, const MapValues *resources_list) : Buildable(p, resources_list) {}

const void ariel::City::get_resources(size_t amount)
{
    for (MapValues &resource : this->resources)
    {
        this->owner.add_resource(resource, amount);
    }
}