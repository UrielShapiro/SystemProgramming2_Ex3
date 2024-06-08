#pragma once
#include <string>
#include <vector>
#include "Catan.hpp"
#include "Buildable.hpp"

namespace ariel
{
    class Player
    {
    private:
        static short ID;    // Will top at 3
        short my_id;
        std::string name;
        size_t wood_amount;
        size_t brick_amount;
        size_t ore_amount;
        size_t grain_amount;
        size_t wool_amount;
        size_t total_cards;
        short victory_points;
        std::vector<ariel::Buildable> buildings;

    public:
        Player(const std::string player_name);
        void change_victory_points(const short amount);
        void add_resource(const MapValues resource, const size_t amount);
        const short get_victory_points() const;
        const int rollDice() const;
        void placeSettelemnt(Vertex &v, const std::string building);
        const std::string get_name() const;
        const short get_id() const;
    };
}