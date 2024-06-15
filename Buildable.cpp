#include "Buildable.hpp"
#include "Catan.hpp"

ariel::Buildable::Buildable(Player &p, const GameConsts::MapValues resources_list[MAX_RESOURCES_PER_BUILDABLE]) : owner(p)
{
    for (size_t i = 0; i < MAX_RESOURCES_PER_BUILDABLE; i++)
    {
        resources[i] = resources_list[i];
    }
}
ariel::Buildable::Buildable(const Buildable &other) : owner(other.owner)
{
    for (size_t i = 0; i < MAX_RESOURCES_PER_BUILDABLE; i++)
    {
        resources[i] = other.resources[i];
    }
}

const GameConsts::MapValues *ariel::Buildable::get_resources() const
{
    return resources;
}

ariel::Player &ariel::Buildable::get_owner()
{
    return owner;
}

ariel::Village::Village(Player &p, const GameConsts::MapValues resources_list[MAX_RESOURCES_PER_BUILDABLE]) : Buildable(p, resources_list) {}



std::string ariel::Village::get_type() const { return "Village"; }

ariel::City::City(Player &p, const GameConsts::MapValues resources_list[MAX_RESOURCES_PER_BUILDABLE]) : Buildable(p, resources_list) {}


std::string ariel::City::get_type() const { return "City"; }