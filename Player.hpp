#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "Vertex.hpp"
#include "GameConsts.hpp"
#define MAX_RESOURCES_PER_BUILDABLE 3
namespace ariel
{
    class Board;     // Forward declaration
    class Edge;      // Forward declaration
    class Buildable; // Forward declaration
    class Vertex;    // Forward declaration

    class Player
    {
    private:
        static short ID; // Will top at 3
        short my_id;
        std::string name;
        int wood_amount;
        int brick_amount;
        int ore_amount;
        int grain_amount;
        int wool_amount;
        size_t total_cards;
        short victory_points;
        std::vector<ariel::Buildable *> buildings;
        std::vector<GameConsts::DevelopmentCard> development_cards;
        bool largest_army;

    public:
        Player(const std::string player_name);
        ~Player();
        void change_victory_points(const short amount);
        void change_resource_amount(const GameConsts::MapValues resource, const size_t amount);
        void change_resource_amount(const GameConsts::MapValues* resources_vec, const size_t amount);
        void change_resource_amount(const GameConsts::ResourceCard resource, const size_t amount);
        short get_victory_points() const;
        int rollDice() const;
        void placeSettelemnt(ariel::Board &b, ariel::Vertex &v, const std::string building);
        void placeRoad(ariel::Board &b, ariel::Edge &e);
        bool check_valid_resources(GameConsts::ResourceCard card, int amount) const;
        std::vector<GameConsts::DevelopmentCard> &get_development_cards(); // Is not const because it will be used to add cards to the vector
        void set_largest_army(bool is_the_largest);

        /*
         *   @param: edge_placement - the id of the edge
         *   @param: vertex_placement - 0 for for one side of the vertex and 1 for the other
         */
        void game_start_placement(ariel::Board &b, std::vector<size_t> &edge_placement, std::vector<size_t> &vertex_placement);
        const std::string get_name() const;
        short get_id() const;

        template <typename CardsType>
        bool trade(ariel::Player &p, std::vector<CardsType> &vec); // Used template to create function for Development cards and for resource cards

        void add_development_card(const GameConsts::DevelopmentCard card);
        size_t get_total_cards() const;
        void discard_half_cards();
        void print_stats() const;
    };
};