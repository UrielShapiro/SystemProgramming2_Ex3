#pragma once
#include "Player.hpp"

namespace ariel
{
    class Edge
    {
    private:
        Player road_owner;
        bool is_taken;
        const short ID;

    public:
        Edge(const short id);
        void set_road(const Player &p);
    };
}