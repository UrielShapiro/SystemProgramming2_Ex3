#pragma once
#include "Player.hpp"

namespace ariel
{
    class Edge
    {
    private:
        Player road_owner;
        bool is_taken;

    public:
        Edge();
        void set_road(Player &p);
    };
}