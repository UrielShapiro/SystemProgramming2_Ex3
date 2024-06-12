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
        GameConsts::MapValues resources[MAX_RESOURCES_PER_BUILDABLE];
        Buildable(const Player &p, const GameConsts::MapValues *resources_list);

    public:
        virtual const void get_resources(const size_t amount) = 0;
        virtual const std::string get_type() = 0;
        const GameConsts::MapValues *get_resources() const;
        Player &get_owner();
    };

    class Village : public Buildable
    {
    public:
        Village(const Player &p, const GameConsts::MapValues *resources);
        const void get_resources(const size_t amount) override;
        const std::string get_type() override;
    };

    class City : public Buildable
    {
    public:
        City(const Player &p, const GameConsts::MapValues *resources);
        const void get_resources(const size_t amount) override;
        const std::string get_type() override;
    };

} // namespace ariel
