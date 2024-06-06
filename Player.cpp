#include "Player.hpp"
#include <stdexcept>
#include "Catan.hpp"
#include "Board.hpp"

ariel::Player::Player(std::string player_name) : name(player_name), wood_amount(0), grain_amount(0),
                                                 brick_amount(0), ore_amount(0), total_cards(0),victory_points(0) {}

void ariel::Player::add_victory_points(short amount)
{
    if(amount > 2)
    {
        throw std::invalid_argument("There's no way you got more then 2 victory points at once");
    }
    this->victory_points += amount;
}

void ariel::Player::add_resource(MapValues resource, size_t amount)
{
    switch (resource)
    {
    case MapValues::FOREST:
        this->wood_amount += amount;
        break;
    case MapValues::HILL:
        this->brick_amount += amount;
        break;
    case MapValues::MOUNTAIN:
        this->ore_amount += amount;
        break;
    case MapValues::FIELD:
        this->grain_amount += amount;
        break;
    case MapValues::PASTURES:
        this->wool_amount += amount;
        break;
    default:
        throw std::invalid_argument("Invalid resource type");
    }
    this->total_cards += amount;
}