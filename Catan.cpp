#include "Catan.hpp"
#include <time.h>

ariel::Catan::Catan(ariel::Player &p1, ariel::Player &p2, ariel::Player &p3) : largest_army(INITIATE_LARGEST_ARMY), turn(0),
                                                                               board(ariel::Board::get_instance()), players{p1, p2, p3} {}

ariel::Board *ariel::Catan::getBoard() { return this->board; }

void ariel::Catan::StartingGame(std::vector<size_t> &e_placement, std::vector<size_t> &v_placement)
{
    if (e_placement.size() != MAX_NUM_OF_PLAYERS || v_placement.size() != MAX_NUM_OF_PLAYERS)
    {
        throw std::runtime_error("Error: The number of arguments passed to start the game is not equal to the amount of players");
    }
    for (size_t player_index = 0; player_index < MAX_NUM_OF_PLAYERS; player_index++)
    {
        players[player_index].game_start_placement(*(this->board), e_placement[player_index], v_placement[player_index]);
    }
}

void ariel::Catan::rollDice()
{
    int dice_result = players[turn++ % MAX_NUM_OF_PLAYERS].rollDice();
    for (ariel::Tile *t : board->get_tiles())
    {
        if (t->get_token() == dice_result)
        {
            for (ariel::Vertex *v : t->get_vertices())
            {
                if (!v->is_free())
                {
                    v->get_building()->get_resources(1);

                    size_t amount = v->get_building()->get_type() == "Village" ? 1 : 2;
                    // v->get_building()->get_owner().change_resource_amount(t->get_value(), amount);
                    std::cout << "Awarded " << amount << " of " << GameConsts::to_string(t->get_value()) << " cards to "
                              << v->get_building()->get_owner().get_name() << std::endl;
                }
            }
        }
    }
}

GameConsts::DevelopmentCard ariel::Catan::buyDevelopmentCard(ariel::Player &p)
{
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
    srand(time(NULL));
    p.get_development_cards().push_back(cards.at(rand() % cards.size()));
    return cards.at(rand() % cards.size());
}

void ariel::Catan::use_development_card(ariel::Player &p, GameConsts::DevelopmentCard card)
{
    // First, remove the card from the users vector of development cards, unless its a knight.
    if (card != GameConsts::DevelopmentCard::KNIGHT)
    {
        bool found = false;
        for (size_t i = 0 ; i < p.get_development_cards().size() && !found; i++)
        {
            if(to_string(p.get_development_cards().at(i)) == to_string(card))
            {
                p.get_development_cards().erase(p.get_development_cards().begin() + i);
                found = true;
            }
        }
        if(!found)
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
            std::cerr << "Error: " << e.what() << '\n';
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
            std::cerr << "Error: " << e.what() << '\n';
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
        p.change_resource_amount(resource_card2, 2);
    }

    if (card == GameConsts::DevelopmentCard::KNIGHT)
    {
        ariel::Catan::check_largest_army();
    }
}

bool ariel::Catan::check_winner()
{
    for (ariel::Player &p : players)
    {
        if (p.get_victory_points() >= 10)
        {
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
            p.set_largest_army(true);
            largest_army = knights_amount; // update the amount of knights required for the largest army
            updated = true;
        }
        else
        {
            p.set_largest_army(false);
        }
    }
    return updated;
}

void ariel::Catan::GameCheck()
{
    if (ariel::Catan::check_winner())
    {
        for (ariel::Player &p : players)
        {
            if (p.get_victory_points() >= 10)
            {
                std::cout << p.get_name() << " has reached " << p.get_victory_points() << " points and won the game!" << std::endl;
                return;
            }
        }
    }
    check_largest_army();
}