#pragma once
#include "Player.hpp"
#include "Board.hpp"

#define MAX_RESOURCES_PER_BUILDABLE 3

namespace ariel
{
    class Buildable
    {
    protected:
        Player owner;
        MapValues resources[MAX_RESOURCES_PER_BUILDABLE];
        Buildable(const Player &p, const MapValues *resources_list);

    public:
        virtual const void get_resources(const size_t amount) = 0;
        const MapValues* get_resources() const;
        const Player &get_owner() const;
    };

    class Village : public Buildable
    {
    public:
        Village(const Player &p, const MapValues *resources);
        const void get_resources(const size_t amount) override;
    };

    class City : public Buildable
    {
    public:
        City(const Player &p, const MapValues *resources);
        const void get_resources(const size_t amount) override;
    };

} // namespace ariel