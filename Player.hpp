#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Buildable.hpp"
#include "Board.hpp"
#include "Vertex.hpp"

using namespace GameConsts;

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
        ~Player();
        void change_victory_points(const short amount);
        void add_resource(const MapValues resource, const size_t amount);
        const short get_victory_points() const;
        const int rollDice() const;
        void placeSettelemnt(ariel::Board &b, ariel::Vertex &v, const std::string building);
        void placeRoad(ariel::Board &b, ariel::Edge &e);

        /*
         *   @param: edge_placement - the id of the edge
         *   @param: vertex_placement - 0 for for one side of the vertex and 1 for the other
        */
        void game_start_placement(ariel::Board &b, size_t edge_placement, unsigned short vertex_placement);
        const std::string get_name() const;
        const short get_id() const;
    };
}