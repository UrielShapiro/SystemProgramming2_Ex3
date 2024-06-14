#include "Player.hpp"
#include <stdexcept>
#include <ctime>

short ariel::Player::ID = 0;

ariel::Player::Player(const std::string player_name) : my_id(ID++), name(player_name), wood_amount(0),
                                                       brick_amount(0), ore_amount(0), grain_amount(0), wool_amount(0), total_cards(0),
                                                       victory_points(0), buildings{}, development_cards{}, largest_army(false) {}

ariel::Player::~Player()
{
    for (ariel::Buildable *b : buildings)
    {
        delete b;
    }
}

void ariel::Player::change_victory_points(const short amount)
{
    if (amount > 2)
    {
        throw std::invalid_argument("There's no way you got more then 2 victory points at once");
    }
    this->victory_points += amount;
}

short ariel::Player::get_victory_points() const
{
    return this->victory_points;
}

void ariel::Player::change_resource_amount(const GameConsts::MapValues resource, const size_t amount)
{
    switch (resource)
    {
    case GameConsts::MapValues::FOREST:
        this->wood_amount += amount;
        break;
    case GameConsts::MapValues::HILL:
        this->brick_amount += amount;
        break;
    case GameConsts::MapValues::MOUNTAIN:
        this->ore_amount += amount;
        break;
    case GameConsts::MapValues::FIELD:
        this->grain_amount += amount;
        break;
    case GameConsts::MapValues::PASTURES:
        this->wool_amount += amount;
        break;
    case GameConsts::MapValues::SEA:
        break;
    case GameConsts::MapValues::DESERT:
        break;
    default:
        throw std::invalid_argument("Invalid resource type"); // Shouldn't be reached.
    }
    this->total_cards += amount;
}

void ariel::Player::change_resource_amount(const GameConsts::ResourceCard resource, const size_t amount)
{
    switch (resource)
    {
    case GameConsts::ResourceCard::Wood:
        this->wood_amount += amount;
        break;
    case GameConsts::ResourceCard::Brick:
        this->brick_amount += amount;
        break;
    case GameConsts::ResourceCard::Ore:
        this->ore_amount += amount;
        break;
    case GameConsts::ResourceCard::Grain:
        this->grain_amount += amount;
        break;
    case GameConsts::ResourceCard::Wool:
        this->wool_amount += amount;
        break;
    default:
        throw std::invalid_argument("Invalid resource type"); // Shouldn't be reached.
    }
    this->total_cards += amount;
}

int ariel::Player::rollDice() const
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

short ariel::Player::get_id() const
{
    return this->my_id;
}

void ariel::Player::placeSettelemnt(ariel::Board &b, ariel::Vertex &v, const std::string building)
{
    if (!b.valid_settlement_placement(v, *this))
    {
        throw std::invalid_argument("This vertex is already taken");
    }

    if (building.compare("Village") == 0)
    {
        if (!v.is_free())
        {
            return;
        }
        if (brick_amount - 1 < 0 || wood_amount - 1 < 0 || wool_amount - 1 < 0 || grain_amount - 1 < 0) // Check if the amount of resources is valid
        {
            throw std::runtime_error("Invalid amount of resources to build a village!");
        }

        this->change_victory_points(1);
        ariel::Village *village = new ariel::Village(*this, v.get_resources());
        v.set_building(village);
        this->buildings.push_back(village);
    }
    else if (building.compare("City") == 0)
    {
        if (v.is_free())
        {
            throw std::runtime_error("You cannot build a city from scratch");
        }
        if (ore_amount - 3 < 0 || grain_amount - 2 < 0) // Check if the amount of resources is valid
        {
            throw std::runtime_error("Invalid amount of resources to build a city!");
        }

        this->change_victory_points(1);
        ariel::City *city = new ariel::City(*this, v.get_resources());
        v.set_building(city);
        this->buildings.push_back(city);
    }
    else
    {
        throw std::invalid_argument("Invalid building type");
    }
}

void ariel::Player::placeRoad(ariel::Board &b, ariel::Edge &e)
{
    if (!b.valid_road_placement(e, *this))
    {
        throw std::runtime_error("This edge is already taken!");
    }
    if (wood_amount - 1 < 0 || brick_amount - 1 < 0)
    {
        throw std::runtime_error("Invalid amount of resources to build a road!");
    }
    e.set_road(*this);
}

void ariel::Player::game_start_placement(ariel::Board &b, size_t edge_placement, size_t vertex_placement)
{
    if (edge_placement > NUM_OF_EDGES)
    {
        throw std::domain_error("Error: you have entered a number above the limit\n");
    }
    if (b.get_edges().at(edge_placement)->isTaken())
    {
        std::string error = "Error:" + std::to_string(b.get_edges().at(edge_placement)->get_id()) + " is already taken\n";
        throw std::runtime_error(error.c_str());
    }
    b.get_edges().at(edge_placement)->set_road(*this);
    std::cout << this->name << " has set an edge on: " << edge_placement << std::endl;

    for (ariel::Tile *tile : b.get_tiles())
    {
        for (size_t i = 0; i < EDGES_PER_TILE; i++)
        {
            if (tile->get_edges().at(i)->get_id() == b.get_edges().at(edge_placement)->get_id())
            {
                size_t choice = vertex_placement % 2;   // To make it sort of boolean
                switch (choice)
                {
                case 0:
                { // Open perentheses to use v_resources again in the next case
                    const GameConsts::MapValues *v_resouces(tile->get_vertices().at(i)->get_resources());
                    this->buildings.push_back(new ariel::Village(*this, v_resouces));
                    tile->get_vertices().at(i)->set_building(this->buildings.back());
                    std::cout << this->name << " has set a village on vertex: " << tile->get_vertices().at(i)->get_id() << std::endl;
                }
                break;
                case 1:
                {
                    const GameConsts::MapValues *v_resouces(tile->get_vertices().at(i + 1)->get_resources());
                    this->buildings.push_back(new ariel::Village(*this, v_resouces));
                    tile->get_vertices().at(Utils::good_mod(i + 1, VERTICES_PER_TILE))->set_building(this->buildings.back());
                    std::cout << this->name << " has set a village on vertex: " << tile->get_vertices().at(Utils::good_mod(i + 1, VERTICES_PER_TILE))->get_id() << std::endl;
                }
                break;
                default:
                    throw std::runtime_error("An error occured while trying to set a building on a vertex");
                }
            }
        }
    }
    this->change_victory_points(1); // Awarding a victory point for the first settlement
}

bool ariel::Player::check_valid_resources(GameConsts::ResourceCard card, int amount) const
{
    if (amount < 0)
    {
        throw std::invalid_argument("Error: entered a negative amount, will always return true");
    }
    switch (card)
    {
    case GameConsts::ResourceCard::Ore:
        return ore_amount - amount >= 0;
        break;
    case GameConsts::ResourceCard::Brick:
        return brick_amount - amount >= 0;
        break;
    case GameConsts::ResourceCard::Grain:
        return grain_amount - amount >= 0;
        break;
    case GameConsts::ResourceCard::Wood:
        return wood_amount - amount >= 0;
    case GameConsts::ResourceCard::Wool:
        return wool_amount - amount >= 0;
    default:
        throw std::runtime_error("Error: resource card is not valid"); // Would never reach here
    }
}

std::vector<GameConsts::DevelopmentCard> &ariel::Player::get_development_cards()
{
    return this->development_cards;
}

void ariel::Player::set_largest_army(bool is_the_largest)
{
    if (this->largest_army && is_the_largest) // Was the largest and still is
    {
        return;
    }
    else if (this->largest_army && !is_the_largest) // Was the largest but isnt anymore
    {
        this->change_victory_points(-2);
    }
    this->largest_army = is_the_largest;
    if (this->largest_army) // If is the new largest army
    {
        this->change_victory_points(2);
    }
}

template <typename T>
bool ariel::Player::trade(ariel::Player &p, std::vector<T> &vec)
{
    bool traded = false;
    for (T &item : vec)
    {
        if (std::is_same<decltype(item), GameConsts::ResourceCard>::value)  // Check if the type of the item is resource card
        {
            if (!(this->check_valid_resources(item, 1)))
            {
                std::cout << this->get_name() << " does not have " << typeid(item).name() << std::endl;
                continue;
            }
            else
            {
                this->change_resource_amount(item, -1);
                p.change_resource_amount(item, 1);
                traded = true;
            }
        }
        else if (std::is_same<decltype(item), GameConsts::DevelopmentCard>::value)
        {
            if (this->development_cards.size() == 0)
            {
                std::cerr << "Error while trading cards: " << this->get_name() << " does not have any development cards" << std::endl;
                continue;
            }
            for (size_t i = 0; i < this->development_cards.size(); i++)
            {
                if (to_string(this->development_cards.at(i)) == to_string(item))
                {
                    this->development_cards.erase(this->development_cards.begin() + i);
                    p.get_development_cards().push_back(item);
                    traded = true;
                    break;
                }
            }
        }
        else
        {
            throw std::runtime_error("Error: invalid type of trade");
        }
    }
    return traded;
}
