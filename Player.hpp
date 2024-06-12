#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Board.hpp"
#include "Vertex.hpp"

using namespace GameConsts;

namespace ariel
{
    class Player
    {
    private:
        static short ID; // Will top at 3
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
        std::vector<GameConsts::DevelopmentCard> development_cards;
        bool largest_army;

    public:
        Player(const std::string player_name);
        ~Player();
        void change_victory_points(const short amount);
        void change_resource_amount(const GameConsts::MapValues resource, const size_t amount);
        void ariel::Player::change_resource_amount(const GameConsts::ResourceCard resource, const size_t amount);
        const short get_victory_points() const;
        const int rollDice() const;
        void placeSettelemnt(ariel::Board &b, ariel::Vertex &v, const std::string building);
        void placeRoad(ariel::Board &b, ariel::Edge &e);
        const bool check_valid_resources(GameConsts::ResourceCard card, size_t amount) const;
        std::vector<GameConsts::DevelopmentCard> &get_development_cards(); // Is not const because it will be used to add cards to the vector
        void set_largest_army(bool is_the_largest);

        /*
         *   @param: edge_placement - the id of the edge
         *   @param: vertex_placement - 0 for for one side of the vertex and 1 for the other
         */
        void game_start_placement(ariel::Board &b, size_t edge_placement, size_t vertex_placement);
        const std::string get_name() const;
        const short get_id() const;

        template <typename CardsType>
        bool trade(ariel::Player &p, std::vector<CardsType> &vec); // Used template to create function for Development cards and for resource cards
    };
}