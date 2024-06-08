#include "Player.hpp"
#include <stdexcept>
#include "Catan.hpp"
#include "Board.hpp"
#include "Buildable.hpp"
#include "Vertex.hpp"
#include <ctime>

short ariel::Player::ID = 0;

ariel::Player::Player(const std::string player_name) : name(player_name), wood_amount(0), grain_amount(0),
                                                       brick_amount(0), ore_amount(0), total_cards(0),
                                                       victory_points(0), buildings{}, my_id(ID++) {}

void ariel::Player::change_victory_points(const short amount)
{
    if (amount > 2)
    {
        throw std::invalid_argument("There's no way you got more then 2 victory points at once");
    }
    this->victory_points += amount;
}

const short ariel::Player::get_victory_points() const
{
    return this->victory_points;
}

void ariel::Player::add_resource(const MapValues resource, const size_t amount)
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

const int ariel::Player::rollDice() const
{
    srand(time(NULL));
    int dice1 = ((rand() % 6) + 1);
    srand(time(NULL));
    int dice2 = ((rand() % 6) + 1);
    return dice1 + dice2;
}

const std::string ariel::Player::get_name() const
{
    return this->name;
}

const short ariel::Player::get_id() const
{
    return this->my_id;
}

void ariel::Player::placeSettelemnt(ariel::Vertex &v, const std::string building)
{
    if (!v.is_free() && v.get_building()->get_owner().get_id() != this->get_id())
    {
        throw std::invalid_argument("This vertex is already taken");
    }

    if (building.compare("Village") == 0)
    {
        if (v.is_free())
            this->change_victory_points(1);

        ariel::Village village = ariel::Village(*this, v.get_resources());
        v.set_building(village);
        this->buildings.push_back(village);
    }
    else if (building.compare("City") == 0)
    {
        this->buildings.push_back(City(*this, v.get_resources()));
        this->change_victory_points(2);
    }
    else
    {
        throw std::invalid_argument("Invalid building type");
    }
}