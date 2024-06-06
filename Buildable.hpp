#pragma once
#include "Player.hpp"
#include "Board.hpp"

#define MAX_RESOURCES_PER_BUILDABLE 3

namespace ariel
{
    class Buildable
    {
    private:
    protected:
        Player owner;
        MapValues resources[MAX_RESOURCES_PER_BUILDABLE];
        Buildable(const Player &p);

    public:
        ~Buildable();
        virtual const void get_resources(size_t amount);
    };

    class Village : public Buildable
    {
    private:
        MapValues resources[3];

    public:
        Village(Player &p);
    };
} // namespace ariel
