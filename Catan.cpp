/**
 * @ID: 9745
 * @name: Uriel Shapiro
 * @email: uriel1999@gmail.com
 */

#include "Catan.hpp"
#include <time.h>
#include <iostream>
#include <stdexcept>
#include <random>

// #define DEBUG

ariel::Catan::Catan(ariel::Player &p1, ariel::Player &p2, ariel::Player &p3) : largest_army(INITIATE_LARGEST_ARMY), turn(0),
                                                                               board(ariel::Board::get_instance()), players{p1, p2, p3}
{
    std::cout << "Catan game has started" << std::endl;
    std::cout << "Starting player is: " << players[turn].get_name() << std::endl;
}

ariel::Board *ariel::Catan::getBoard() { return this->board; }

void ariel::Catan::StartingGame(std::vector<size_t> &e_placement, std::vector<size_t> &v_placement)
{
    if (e_placement.size() != MAX_NUM_OF_PLAYERS * 2 || v_placement.size() != MAX_NUM_OF_PLAYERS * 2)
    {
        throw std::runtime_error("Error: The number of arguments passed to start the game should have 2 villages and to roads for each player");
    }
    size_t pointer1 = 0;
    size_t pointer2 = 0;
    for (size_t player_index = 0; player_index < MAX_NUM_OF_PLAYERS; player_index++)
    {
        std::vector<size_t> edge_placement = {e_placement[pointer1], e_placement[++pointer1]};
        std::vector<size_t> vertex_placement = {v_placement[pointer2], v_placement[++pointer2]};
        players[player_index].game_start_placement(*(this->board), edge_placement, vertex_placement);
        pointer1++;
        pointer2++;
    }
}

int ariel::Catan::rollDice()
{
    GameCheck(); // before rolling the dice, we need to check if the game has ended
    int dice_result = players[turn].rollDice();
    std::cout << players[turn].get_name() << " rolled the dice. The result is: " << dice_result << std::endl;
    if (dice_result == 7)
    {
        for (Player &p : players)
        {
            if (p.get_total_cards() > 7)
            {
                std::cout << p.get_name() << " has more than 7 cards, and will be discarded half of them" << std::endl;
                p.discard_half_cards();
            }
        }
        return dice_result;
    }
    for (ariel::Tile *t : board->get_tiles())
    {
        if (t->get_token() == dice_result)
        {
            for (ariel::Vertex *v : t->get_vertices())
            {
                if (!v->is_free())
                {
                    int amount = v->get_building()->get_type() == "Village" ? 1 : 2;
                    v->get_building()->get_owner().change_resource_amount(t->get_value(), amount);
                    GameConsts::ResourceCard card_name;
                    switch (t->get_value())
                    {
                    case GameConsts::MapValues::FOREST:
                        card_name = GameConsts::ResourceCard::Wood;
                        break;
                    case GameConsts::MapValues::HILL:
                        card_name = GameConsts::ResourceCard::Brick;
                        break;
                    case GameConsts::MapValues::MOUNTAIN:
                        card_name = GameConsts::ResourceCard::Ore;
                        break;
                    case GameConsts::MapValues::FIELD:
                        card_name = GameConsts::ResourceCard::Grain;
                        break;
                    case GameConsts::MapValues::PASTURES:
                        card_name = GameConsts::ResourceCard::Wool;
                        break;
                    case GameConsts::MapValues::DESERT:
                        break;
                    case GameConsts::MapValues::SEA:
                        break;
                    }

                    std::cout << v->get_building()->get_owner().get_name() << " was awarded " << amount << " "
                              << GameConsts::to_string(card_name) << " card" << std::endl;
                }
            }
        }
    }
    return dice_result; // For the tests
}

GameConsts::DevelopmentCard ariel::Catan::buyDevelopmentCard(ariel::Player &p)
{
    if (players[turn].get_id() != p.get_id())
    {
        throw std::runtime_error("Error: You cannot buy a development card because it is not your turn");
    }

    // Check if the player has enough resources to buy a development card
    if (!(p.check_valid_resources(GameConsts::ResourceCard::Ore, 1) && p.check_valid_resources(GameConsts::ResourceCard::Wool, 1) && p.check_valid_resources(GameConsts::ResourceCard::Grain, 1)))
    {
        throw std::runtime_error("Error: Not enough resources to buy a development card");
    }
    // Otherwise: remove the resources and add a random card to the player
    p.change_resource_amount(GameConsts::ResourceCard::Ore, -1);
    p.change_resource_amount(GameConsts::ResourceCard::Wool, -1);
    p.change_resource_amount(GameConsts::ResourceCard::Grain, -1);

    std::vector<GameConsts::DevelopmentCard> cards = {GameConsts::DevelopmentCard::BUILD_ROAD,
                                                      GameConsts::DevelopmentCard::KNIGHT,
                                                      GameConsts::DevelopmentCard::WINNING_POINTS,
                                                      GameConsts::DevelopmentCard::YEAR_OF_PLENTY};

    static std::random_device rd;                             // random number generator
    static std::mt19937 gen(rd());                            // seeder
    std::uniform_int_distribution<> dis(0, cards.size() - 1); // Uniform distribution for dice rolls (1 to 6)

    p.add_development_card(cards.at(dis(gen)));
    std::cout << p.get_name() << " has bought the following development card: " << to_string(p.get_development_cards().back()) << std::endl;
    return p.get_development_cards().back();
}

void ariel::Catan::use_development_card(ariel::Player &p, GameConsts::DevelopmentCard card)
{
    if (players[turn].get_id() != p.get_id())
    {
        throw std::runtime_error("Error: It is not your turn");
    }
    // First, remove the card from the users vector of development cards, unless its a knight.
    if (card != GameConsts::DevelopmentCard::KNIGHT)
    {
        bool found = false;

#ifdef DEBUG
        std::cout << "Development cards vector size: " << p.get_development_cards().size() << std::endl;
#endif
        for (size_t i = 0; i < p.get_development_cards().size() && !found; i++)
        {
#ifdef DEBUG
            std::cout << "Checking if " << to_string(p.get_development_cards().at(i)) << " is equal to " << to_string(card) << std::endl;
#endif
            if (to_string(p.get_development_cards().at(i)) == to_string(card))
            {
                p.get_development_cards().erase(p.get_development_cards().begin() + i);
                found = true;
#ifdef DEBUG
                std::cout << "Found the card" << std::endl;
#endif
            }
        }
        if (!found)
        {
            throw std::runtime_error("Error: requested card is not in the cards vector");
        }
    }

    if (card == GameConsts::DevelopmentCard::MONOPOLY)
    {
        std::string user_ans;
        GameConsts::ResourceCard resource_card;
        std::cout << "Which card do you want to take from the other players?" << std::endl;
        std::cin >> user_ans;

        if (!user_ans.compare("Ore") || !user_ans.compare("ore"))
        {
            resource_card = GameConsts::ResourceCard::Ore;
        }
        else if (!user_ans.compare("Wood") || !user_ans.compare("wood"))
        {
            resource_card = GameConsts::ResourceCard::Wood;
        }
        else if (!user_ans.compare("Wool") || !user_ans.compare("wool"))
        {
            resource_card = GameConsts::ResourceCard::Wool;
        }
        else if (!user_ans.compare("Brick") || !user_ans.compare("brick"))
        {
            resource_card = GameConsts::ResourceCard::Brick;
        }
        else if (!user_ans.compare("Grain") || !user_ans.compare("grain"))
        {
            resource_card = GameConsts::ResourceCard::Grain;
        }

        for (ariel::Player &player : this->players)
        {
            if (player.get_id() != p.get_id())
            {
                for (size_t i = 0; player.check_valid_resources(resource_card, 1); i++)
                {
                    player.change_resource_amount(resource_card, -1);
                    p.change_resource_amount(resource_card, 1);
                    std::cout << "Took a " << GameConsts::to_string(resource_card) << " card from " << player.get_name() << std::endl;
                }
            }
        }
    }

    if (card == GameConsts::DevelopmentCard::BUILD_ROAD)
    {
        std::string place1;
        std::string place2;

        std::cout << "Write the two positions in which you want to place a road in, seprerated by space: ";
        std::cin >> place1 >> place2;
        std::cout << std::endl;
        try
        {
            // We add the neccerry resources, so that placeRoad won't throw an exception for invalid amount of resources
            p.change_resource_amount(GameConsts::ResourceCard::Brick, 1);
            p.change_resource_amount(GameConsts::ResourceCard::Wood, 1);
            p.placeRoad(*(this->board), *(this->board->get_edges().at(std::stoi(place1))));
        }
        catch (const std::runtime_error &e)
        {
            std::cerr << "\033[0;31m" << "Error: " << e.what() << "\033[0m" << '\n';
        }
        try
        {
            // We add the neccerry resources, so that placeRoad won't throw an exception for invalid amount of resources
            p.change_resource_amount(GameConsts::ResourceCard::Brick, 1);
            p.change_resource_amount(GameConsts::ResourceCard::Wood, 1);
            p.placeRoad(*(this->board), *(this->board->get_edges().at(std::stoi(place2))));
        }
        catch (const std::runtime_error &e)
        {
            std::cerr << "\033[0;31m" << "Error: " << e.what() << "\033[0m" << '\n';
        }
    }

    if (card == GameConsts::DevelopmentCard::YEAR_OF_PLENTY)
    {
        std::string user_ans1;
        std::string user_ans2;
        std::cout << "Choose which resources do you want from the bank (2 resources seperated by space): ";
        std::cin >> user_ans1 >> user_ans2;
        std::cout << std::endl;

        GameConsts::ResourceCard resource_card1;
        GameConsts::ResourceCard resource_card2;

        // First resource
        if (!user_ans1.compare("Ore") || !user_ans1.compare("ore"))
        {
            resource_card1 = GameConsts::ResourceCard::Ore;
        }
        else if (!user_ans1.compare("Wood") || !user_ans1.compare("wood"))
        {
            resource_card1 = GameConsts::ResourceCard::Wood;
        }
        else if (!user_ans1.compare("Wool") || !user_ans1.compare("wool"))
        {
            resource_card1 = GameConsts::ResourceCard::Wool;
        }
        else if (!user_ans1.compare("Brick") || !user_ans1.compare("brick"))
        {
            resource_card1 = GameConsts::ResourceCard::Brick;
        }
        else if (!user_ans1.compare("Grain") || !user_ans1.compare("grain"))
        {
            resource_card1 = GameConsts::ResourceCard::Grain;
        }

        // Second resource
        if (!user_ans2.compare("Ore") || !user_ans2.compare("ore"))
        {
            resource_card2 = GameConsts::ResourceCard::Ore;
        }
        else if (!user_ans2.compare("Wood") || !user_ans2.compare("wood"))
        {
            resource_card2 = GameConsts::ResourceCard::Wood;
        }
        else if (!user_ans2.compare("Wool") || !user_ans2.compare("wool"))
        {
            resource_card2 = GameConsts::ResourceCard::Wool;
        }
        else if (!user_ans2.compare("Brick") || !user_ans2.compare("brick"))
        {
            resource_card2 = GameConsts::ResourceCard::Brick;
        }
        else if (!user_ans2.compare("Grain") || !user_ans2.compare("grain"))
        {
            resource_card2 = GameConsts::ResourceCard::Grain;
        }

        p.change_resource_amount(resource_card1, 1);
        p.change_resource_amount(resource_card2, 1);
        std::cout << "Added " << GameConsts::to_string(resource_card1) << " and " << GameConsts::to_string(resource_card2) << " to " << p.get_name() << std::endl;
    }
    if (card == GameConsts::DevelopmentCard::WINNING_POINTS)
    {
        p.change_victory_points(1);
        std::cout << p.get_name() << " was added a victory point" << std::endl;
    }

    if (card == GameConsts::DevelopmentCard::KNIGHT)
    {
        if (ariel::Catan::check_largest_army())
        {
            std::cout << players[turn].get_name() << " has the largest army" << std::endl;
            // Because check_largest_army() updates each dice roll, if it is updated now, it means that the player has the largest army
        }
    }
    GameCheck(); // To move the turn to the next player
}

bool ariel::Catan::check_winner()
{
    for (ariel::Player &p : players)
    {
#ifdef DEBUG
        std::cout << p.get_name() << " has " << p.get_victory_points() << " points" << std::endl;
#endif
        if (p.get_victory_points() >= 10)
        {
            std::cout << p.get_name() << " has reached " << p.get_victory_points() << " points and won the game!" << std::endl;
            return true;
        }
    }
    return false;
}

bool ariel::Catan::check_largest_army()
{
    bool updated = false;
    for (Player &p : players)
    {
        size_t knights_amount = 0;
        for (GameConsts::DevelopmentCard card : p.get_development_cards())
        {
            if (card == GameConsts::DevelopmentCard::KNIGHT)
            {
                knights_amount++;
            }
        }
        if (knights_amount >= largest_army) // If the amount of knights is atleast the amount required to get the largest army
        {
            p.set_largest_army(true);      // Victory points will be added in the player class
            largest_army = knights_amount; // update the amount of knights required for the largest army
            updated = true;
        }
        else
        {
            p.set_largest_army(false); // Victory points will be reduced in the player class if needed
        }
    }
    return updated;
}

ariel::Catan::~Catan()
{
    delete board;
    // Not deleting players because they are not dynamically allocated
}

/*
    This function will return true if the game has ended, if not, it will move to the next player and return false.
*/
bool ariel::Catan::GameCheck()
{
    if (ariel::Catan::check_winner())
        return true;

    check_largest_army();
    ++turn;
    turn = turn % MAX_NUM_OF_PLAYERS; // Move to the next player
    return false;
}

void ariel::Catan::print_players_stats()
{
    for (ariel::Player &p : players)
    {
        p.print_stats();
    }
}

ariel::Player *ariel::Catan::get_players()
{
    return this->players;
}

size_t ariel::Catan::get_turn() const
{
    return this->turn;
}