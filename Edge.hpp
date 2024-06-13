#pragma once
#include "Player.hpp"

namespace ariel
{
    class Player; // Forward declaration
    class Edge
    {
    private:
        Player *road_owner;
        bool is_taken;
        const short ID;

    public:
        Edge(const short id);
        void set_road(Player &p);
        bool isTaken() const;
        short get_id() const;
        const Player *get_owner() const;
        ~Edge() = default;
    };
}