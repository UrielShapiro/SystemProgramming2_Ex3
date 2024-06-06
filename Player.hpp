#pragma once
#include <string>
#include <vector>
#include "Catan.hpp"

namespace ariel
{
    class Player
    {
    private:
        std::string name;
        size_t wood_amount;
        size_t brick_amount;
        size_t ore_amount;
        size_t grain_amount;
        size_t wool_amount;
        size_t total_cards;
        short victory_points;

    public:
        Player(std::string player_name);
        void add_victory_points(short amount);
        void add_resource(MapValues resource, size_t amount);
        int roll_dice();
    };
}