#include "Player.hpp"
#include <stdexcept>
#include <ctime>
#include <iostream>
#include <random>

// #define DEBUG

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

void ariel::Player::change_resource_amount(const GameConsts::MapValues *resources_vec, const size_t amount)
{
    for (size_t i = 0; i < MAX_RESOURCES_PER_BUILDABLE; i++)
    {
        change_resource_amount(resources_vec[i], amount);
    }
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
    // Random number generator - https://en.cppreference.com/w/cpp/numeric/random
    // Using this instead of rand() + srand() because it's true random

    static std::random_device rd;              // random number generator
    static std::mt19937 gen(rd());             // seeder
    std::uniform_int_distribution<> dis(1, 6); // Uniform distribution for dice rolls (1 to 6)

    int dice1 = dis(gen);
    int dice2 = dis(gen);
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
        throw std::invalid_argument("You cannot place a settlement here!");
    }

    if (building.compare("Village") == 0)
    {
        if (!v.is_free())
        {
            return;
        }
        if (!check_valid_resources(GameConsts::ResourceCard::Brick, 1) ||
            !check_valid_resources(GameConsts::ResourceCard::Wood, 1) ||
            !check_valid_resources(GameConsts::ResourceCard::Wool, 1) ||
            !check_valid_resources(GameConsts::ResourceCard::Grain, 1)) // Check if the amount of resources is valid
        {
            throw std::runtime_error("Invalid amount of resources to build a village!");
        }

        std::vector<GameConsts::ResourceCard> cost = {GameConsts::ResourceCard::Brick,
                                                      GameConsts::ResourceCard::Wood,
                                                      GameConsts::ResourceCard::Wool,
                                                      GameConsts::ResourceCard::Grain};
        for (GameConsts::ResourceCard resource_card : cost)
        {
            this->change_resource_amount(resource_card, -1);
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
        if (!check_valid_resources(GameConsts::ResourceCard::Ore, 3) ||
            !check_valid_resources(GameConsts::ResourceCard::Grain, 2)) // Check if the amount of resources is valid
        {
            throw std::runtime_error("Invalid amount of resources to build a city!");
        }
        this->change_resource_amount(GameConsts::ResourceCard::Ore, -3);
        this->change_resource_amount(GameConsts::ResourceCard::Grain, -2);

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
        throw std::runtime_error("You cannot place a road here!");
    }
#ifdef DEBUG
    std::cout << "Checking if the player has enough resources to build a road" << std::endl;
    std::cout << "Wood: " << wood_amount << " Brick: " << brick_amount << std::endl;
#endif
    if (!check_valid_resources(GameConsts::ResourceCard::Wood, 1) ||
        !check_valid_resources(GameConsts::ResourceCard::Brick, 1))
    {
        throw std::runtime_error("Invalid amount of resources to build a road!");
    }
    change_resource_amount(GameConsts::ResourceCard::Brick, -1);
    change_resource_amount(GameConsts::ResourceCard::Wood, -1);
    e.set_road(*this);
    std::cout << this->name << " has set a road on edge: " << e.get_id() << std::endl;
}

void ariel::Player::game_start_placement(ariel::Board &b, std::vector<size_t> &edge_placement, std::vector<size_t> &vertex_placement)
{
    if (edge_placement.size() != 2 || vertex_placement.size() != 2)
    {
        throw std::invalid_argument("Error: you have entered the wrong amount of placements\n");
    }
    for (size_t e : edge_placement)
    {
        if (e > NUM_OF_EDGES)
        {
            throw std::domain_error("Error: you have entered a number above the limit\n");
        }
    }

    // First placement
    if (b.get_edges().at(edge_placement[0])->isTaken())
    {
        std::string error = "Error:" + std::to_string(b.get_edges().at(edge_placement[0])->get_id()) + " is already taken\n";
        throw std::runtime_error(error.c_str());
    }
    b.get_edges().at(edge_placement[0])->set_road(*this);
    std::cout << this->name << " has set a road on edge: " << edge_placement[0] << std::endl;

    bool found = false;
    for (ariel::Tile *tile : b.get_tiles())
    {
        for (size_t i = 0; i < EDGES_PER_TILE && !found; i++)
        {
            if (tile->get_edges().at(i)->get_id() == b.get_edges().at(edge_placement[0])->get_id())
            {
                size_t choice = vertex_placement[0] % 2; // To make it sort of boolean
                switch (choice)
                {
                case 0:
                { // Open perentheses to use v_resources again in the next case
                    const GameConsts::MapValues *v_resouces(tile->get_vertices().at(i)->get_resources());
                    this->buildings.push_back(new ariel::Village(*this, v_resouces));
                    tile->get_vertices().at(i)->set_building(this->buildings.back());
                    this->change_resource_amount(v_resouces, 1);
                    std::cout << this->name << " has set a village on vertex: " << tile->get_vertices().at(i)->get_id() << std::endl;
                }
                    found = true;
                    break;
                case 1:
                {
                    const GameConsts::MapValues *v_resouces(tile->get_vertices().at(Utils::good_mod(i + 1, VERTICES_PER_TILE))->get_resources());
                    this->buildings.push_back(new ariel::Village(*this, v_resouces));
                    tile->get_vertices().at(Utils::good_mod(i + 1, VERTICES_PER_TILE))->set_building(this->buildings.back());
                    this->change_resource_amount(v_resouces, 1);
                    std::cout << this->name << " has set a village on vertex: " << tile->get_vertices().at(Utils::good_mod(i + 1, VERTICES_PER_TILE))->get_id() << std::endl;
                }
                    found = true;
                    break;
                default:
                    throw std::runtime_error("An error occured while trying to set a building on a vertex");
                }
            }
        }
    }

    // Second placement
    if (b.get_edges().at(edge_placement[1])->isTaken())
    {
        std::string error = "Error:" + std::to_string(b.get_edges().at(edge_placement[1])->get_id()) + " is already taken\n";
        throw std::runtime_error(error.c_str());
    }
    b.get_edges().at(edge_placement[1])->set_road(*this);
    std::cout << this->name << " has set an edge on: " << edge_placement[1] << std::endl;
    bool found2 = false;
    for (ariel::Tile *tile : b.get_tiles())
    {
        for (size_t i = 0; i < EDGES_PER_TILE && !found2; i++)
        {
            if (tile->get_edges().at(i)->get_id() == b.get_edges().at(edge_placement[1])->get_id())
            {
                size_t choice = vertex_placement[1] % 2; // To make it sort of boolean
                switch (choice)
                {
                case 0:
                { // Open perentheses to use v_resources again in the next case
                    const GameConsts::MapValues *v_resouces(tile->get_vertices().at(i)->get_resources());
                    this->buildings.push_back(new ariel::Village(*this, v_resouces));
                    tile->get_vertices().at(i)->set_building(this->buildings.back());
                    this->change_resource_amount(v_resouces, 1);
                    std::cout << this->name << " has set a village on vertex: " << tile->get_vertices().at(i)->get_id() << std::endl;
                }
                    found2 = true;
                    break;
                case 1:
                {
                    const GameConsts::MapValues *v_resouces(tile->get_vertices().at(i + 1)->get_resources());
                    this->buildings.push_back(new ariel::Village(*this, v_resouces));
                    tile->get_vertices().at(Utils::good_mod(i + 1, VERTICES_PER_TILE))->set_building(this->buildings.back());
                    this->change_resource_amount(v_resouces, 1);
                    std::cout << this->name << " has set a village on vertex: " << tile->get_vertices().at(Utils::good_mod(i + 1, VERTICES_PER_TILE))->get_id() << std::endl;
                }
                    found2 = true;
                    break;
                default:
                    throw std::runtime_error("An error occured while trying to set a building on a vertex");
                }
            }
        }
    }
    this->change_victory_points(2); // Awarding a victory point for the first settlement
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
        std::cout << this->name << " no longer has the largest army" << std::endl;
    }
    this->largest_army = is_the_largest;
    if (this->largest_army) // If is the new largest army
    {
        this->change_victory_points(2);
        std::cout << this->name << " now has the largest army" << std::endl;
    }
}

template <typename T>
bool ariel::Player::trade(ariel::Player &p, std::vector<T> &vec)
{
    bool traded = false;
    for (T &item : vec)
    {
        if (std::is_same<decltype(item), GameConsts::ResourceCard>::value) // Check if the type of the item is resource card
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

void ariel::Player::add_development_card(const GameConsts::DevelopmentCard card)
{
    this->development_cards.push_back(card);
}

size_t ariel::Player::get_total_cards() const
{
    return this->total_cards;
}

void ariel::Player::discard_half_cards()
{
#ifdef DEBUG
    std::cout << this->name << " has too many cards, discarding half of them" << std::endl;
#endif
    if (this->total_cards <= 7) // If the player has less or equal to 7 cards, he doesn't need to discard
    {
        return;
    }
    size_t half = this->total_cards / 2;
#ifdef DEBUG
    std::cout << "Discarding " << half << " cards" << std::endl;
#endif
    if (half == 0)
    {
        return;
    }
    static std::random_device rd;  // random number generator
    static std::mt19937 gen(rd()); // seeder
    std::vector<GameConsts::ResourceCard> resources_vec = {GameConsts::ResourceCard::Brick, GameConsts::ResourceCard::Grain, GameConsts::ResourceCard::Ore, GameConsts::ResourceCard::Wool, GameConsts::ResourceCard::Wood};
    std::uniform_int_distribution<> dis(0, resources_vec.size() - 1); // Uniform distribution

    while (this->total_cards > half)
    {
        GameConsts::ResourceCard card = resources_vec.at(dis(gen));
#ifdef DEBUG
        std::cout << "Discarding card: " << to_string(card) << std::endl;
        std::cout << "Total cards: " << this->total_cards << std::endl;
#endif
        switch (card)
        {
        case GameConsts::ResourceCard::Brick:
            if (check_valid_resources(GameConsts::ResourceCard::Brick, 1))
                change_resource_amount(GameConsts::ResourceCard::Brick, -1);
            break;
        case GameConsts::ResourceCard::Grain:
            if (check_valid_resources(GameConsts::ResourceCard::Grain, 1))
                change_resource_amount(GameConsts::ResourceCard::Grain, -1);
            break;
        case GameConsts::ResourceCard::Ore:
            if (check_valid_resources(GameConsts::ResourceCard::Ore, 1))
                change_resource_amount(GameConsts::ResourceCard::Ore, -1);
            break;
        case GameConsts::ResourceCard::Wool:
            if (check_valid_resources(GameConsts::ResourceCard::Wool, 1))
                change_resource_amount(GameConsts::ResourceCard::Wool, -1);
            break;
        case GameConsts::ResourceCard::Wood:
            if (check_valid_resources(GameConsts::ResourceCard::Wood, 1))
                change_resource_amount(GameConsts::ResourceCard::Wood, -1);
            break;
        default:
            throw std::runtime_error("Error: invalid resource card");
        }
    }
}

void ariel::Player::print_stats() const
{
    std::cout << "------------------------------------------" << std::endl;
    std::cout << this->name << " has the following resources:" << std::endl;
    std::cout << "Wood:\t" << this->wood_amount << std::endl;
    std::cout << "Brick:\t" << this->brick_amount << std::endl;
    std::cout << "Ore:\t" << this->ore_amount << std::endl;
    std::cout << "Grain:\t" << this->grain_amount << std::endl;
    std::cout << "Wool:\t" << this->wool_amount << std::endl;
    std::cout << "Total cards:\t" << this->total_cards << std::endl;
    std::cout << "Victory points:\t" << this->victory_points << std::endl;
    std::string has_largest_army = this->largest_army ? "True" : "False";
    std::cout << "Largest army:\t" << has_largest_army << std::endl;
    if (development_cards.size() > 0)
    {
        std::cout << "Development cards: ";
        for (GameConsts::DevelopmentCard card : this->development_cards)
        {
            std::cout << to_string(card) << " ";
        }
        std::cout << std::endl;
    }
}