/**
 * @ID: 9745
 * @name: Uriel Shapiro
 * @email: uriel1999@gmail.com
 */

#include "Catan.hpp"
#include <iostream>

int main()
{
    std::cout << "Catan Game is starting..." << std::endl;
    std::cout << "Please enter the names of the players (3 names divided by spaces): " << std::endl;
    std::string player1, player2, player3;
    std::cin >> player1 >> player2 >> player3;
    ariel::Player p1(player1);
    ariel::Player p2(player2);
    ariel::Player p3(player3);
    ariel::Catan catan(p1, p2, p3);

    ariel::Board *board = catan.getBoard();

    std::vector<size_t> e_placement;
    std::vector<size_t> v_placement;

    for (int i = 0; i < MAX_NUM_OF_PLAYERS; i++)
    {
        std::cout << "Please enter 2 edge placements for player " << catan.get_players()[i].get_name() << std::endl;
        size_t edge1, edge2;
        std::cin >> edge1 >> edge2;
        e_placement.push_back(edge1);
        e_placement.push_back(edge2);
        std::cout << "Please enter 2 vertex placements for player " << catan.get_players()[i].get_name() << std::endl;
        size_t vertex1, vertex2;
        std::cin >> vertex1 >> vertex2;
        v_placement.push_back(vertex1);
        v_placement.push_back(vertex2);
    }

    catan.StartingGame(e_placement, v_placement);

    while (!catan.GameCheck())
    {
        std::cout << "It's " << catan.get_players()[catan.get_turn()].get_name() << "'s turn!" << std::endl;
        catan.rollDice(); // Will print the result

        bool valid_ans = false;
        while (!valid_ans)
        {
            std::cout << "Please choose an action: " << std::endl;
            std::cout << "1. Buy Development Card" << std::endl;
            std::cout << "2. Use Development Card" << std::endl;
            std::cout << "3. Buy Settlement" << std::endl;
            std::cout << "4. Buy Road" << std::endl;
            std::cout << "5. Trade cards" << std::endl;
            std::cout << "6. Print resources" << std::endl;
            std::cout << "7. End turn" << std::endl;

            int ans;
            std::cin >> ans;
            switch (ans)
            {
            case 1:
                try
                {
                    catan.buyDevelopmentCard(catan.get_players()[catan.get_turn()]);
                    valid_ans = true;
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << '\n';
                }
                break;
            case 2:
                try
                {
                    bool valid_ans2 = false;
                    while (!valid_ans2)
                    {
                        std::cout << "Please enter the card you want to use: " << std::endl;
                        std::cout << "1. Knight" << std::endl;
                        std::cout << "2. Road Building" << std::endl;
                        std::cout << "3. Year of Plenty" << std::endl;
                        std::cout << "4. Monopoly" << std::endl;
                        int card;
                        std::cin >> card;
                        GameConsts::DevelopmentCard dev_card;
                        switch (card)
                        {
                        case 1:
                            dev_card = GameConsts::DevelopmentCard::KNIGHT;
                            valid_ans2 = true;
                            break;
                        case 2:
                            dev_card = GameConsts::DevelopmentCard::BUILD_ROAD;
                            valid_ans2 = true;
                            break;
                        case 3:
                            dev_card = GameConsts::DevelopmentCard::YEAR_OF_PLENTY;
                            valid_ans2 = true;
                            break;
                        case 4:
                            dev_card = GameConsts::DevelopmentCard::MONOPOLY;
                            valid_ans2 = true;
                            break;
                        default:
                            std::cerr << "Invalid input, please try again" << std::endl;
                            continue;
                        }
                        catan.use_development_card(catan.get_players()[catan.get_turn()], dev_card);
                    }
                    valid_ans = true;
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << '\n';
                }
                break;
            case 3:
                try
                {
                    std::cout << "Please enter the vertex you want to place the settlement on: " << std::endl;
                    size_t vertex;
                    std::cin >> vertex;

                    std::string building_str = "Village";
                    bool valid_input1 = false;
                    while (!valid_input1)
                    {
                        std::cout << "Please enter the building you want to place: " << std::endl;
                        std::cout << "1. Settlement" << std::endl;
                        std::cout << "2. City" << std::endl;
                        int building;
                        std::cin >> building;
                        if (building != 1 && building != 2)
                        {
                            std::cerr << "Invalid input, please try again" << std::endl;
                            continue;
                        }
                        building_str = building == 1 ? "Settlement" : "City";
                        valid_input1 = true;
                    }
                    catan.get_players()[catan.get_turn()].placeSettelemnt(*board, *(board->get_vertices()[vertex]), building_str);
                    valid_ans = true;
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << '\n';
                }
                break;
            case 4:
                try
                {
                    bool valid_input2 = false;
                    size_t edge;
                    while (!valid_input2)
                    {
                        std::cout << "Please enter the edge you want to place the road on: " << std::endl;
                        std::cin >> edge;
                        if (edge >= board->get_edges().size())
                        {
                            std::cerr << "Invalid input, please try again" << std::endl;
                            continue;
                        }
                        valid_input2 = true;
                    }
                    catan.get_players()[catan.get_turn()].placeRoad(*board, *(board->get_edges()[edge]));
                    valid_ans = true;
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << '\n';
                }
                break;
            case 5:
                try
                {
                    bool valid_input3 = false;
                    std::string player;
                    while (!valid_input3)
                    {
                        std::cout << "Please enter the player you want to trade with: " << std::endl;
                        std::cin >> player;
                        if (player != catan.get_players()[0].get_name() &&
                            player != catan.get_players()[1].get_name() &&
                            player != catan.get_players()[2].get_name())
                        {
                            std::cerr << "There is no player with that name, please try again" << std::endl;
                            continue;
                        }
                        valid_input3 = true;
                    }

                    bool trade_more = false;
                    while (!trade_more)
                    {
                        bool valid_input4 = false;
                        size_t resource;
                        GameConsts::ResourceCard resource_card;
                        while (!valid_input4)
                        {
                            std::cout << "Please enter the resources you want to trade (give): " << std::endl;
                            std::cout << "1. Wood" << std::endl;
                            std::cout << "2. Brick" << std::endl;
                            std::cout << "3. Grain" << std::endl;
                            std::cout << "4. Wool" << std::endl;
                            std::cout << "5. Ore" << std::endl;
                            std::cin >> resource;
                            if (resource < 1 || resource > 5)
                            {
                                std::cerr << "Invalid input, please try again" << std::endl;
                                continue;
                            }
                            valid_input4 = true;
                        }
                        switch (resource)
                        {
                        case 1:
                            resource_card = GameConsts::ResourceCard::Wood;
                            break;
                        case 2:
                            resource_card = GameConsts::ResourceCard::Brick;
                            break;
                        case 3:
                            resource_card = GameConsts::ResourceCard::Grain;
                            break;
                        case 4:
                            resource_card = GameConsts::ResourceCard::Wool;
                            break;
                        case 5:
                            resource_card = GameConsts::ResourceCard::Ore;
                            break;
                        default:
                            throw std::invalid_argument("Something went wrong");
                            break;
                        }
                        if (catan.get_players()[catan.get_turn()].check_valid_resources(resource_card, 1))
                        {
                            std::cerr << "You don't have any of that resource, please try again" << std::endl;
                            continue;
                        }
                        std::vector<GameConsts::ResourceCard> resources_vec1 = {resource_card};

                        for (size_t i = 0; i < MAX_NUM_OF_PLAYERS; i++)
                        {
                            if (catan.get_players()[i].get_name() == player)
                            {
                                catan.get_players()[i].trade(catan.get_players()[catan.get_turn()], resources_vec1);
                            }
                        }

                        GameConsts::ResourceCard resource_card2;
                        bool valid_input5 = false;
                        int resource2;

                        while (!valid_input5)
                        {
                            std::cout << "Please enter the resources you want to get: " << std::endl;
                            std::cout << "1. Wood" << std::endl;
                            std::cout << "2. Brick" << std::endl;
                            std::cout << "3. Wheat" << std::endl;
                            std::cout << "4. Sheep" << std::endl;
                            std::cout << "5. Ore" << std::endl;
                            std::cin >> resource2;
                            if (resource2 < 1 || resource2 > 5)
                            {
                                std::cerr << "Invalid input, please try again" << std::endl;
                                continue;
                            }
                            valid_input5 = true;
                        }
                        switch (resource2)
                        {
                        case 1:
                            resource_card2 = GameConsts::ResourceCard::Wood;
                            break;
                        case 2:
                            resource_card2 = GameConsts::ResourceCard::Brick;
                            break;
                        case 3:

                            resource_card2 = GameConsts::ResourceCard::Grain;
                            break;
                        case 4:
                            resource_card2 = GameConsts::ResourceCard::Wool;
                            break;
                        case 5:
                            resource_card2 = GameConsts::ResourceCard::Ore;
                            break;
                        default:
                            throw std::invalid_argument("Something went wrong");
                            break;
                        }
                        std::vector<GameConsts::ResourceCard> resources_vec2 = {resource_card2};
                        for (size_t i = 0; i < MAX_NUM_OF_PLAYERS; i++)
                        {
                            if (catan.get_players()[i].get_name() == player)
                            {
                                catan.get_players()[catan.get_turn()].trade(catan.get_players()[i], resources_vec2);
                            }
                        }

                        std::cout << "Do you want to trade more? (1 for yes, 0 for no)" << std::endl;
                        int trade;
                        std::cin >> trade;
                        if (trade == 1)
                        {
                            trade_more = true;
                        }
                        else
                        {
                            trade_more = false;
                        }
                    }
                    valid_ans = true;
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << '\n';
                }
                break;
            case 6:
                catan.print_players_stats();
                break;
            case 7:
                valid_ans = true;   // End turn
                break;
            default:
                std::cerr << "Invalid input, please try again" << std::endl;
                break;
            }
        }
    }
    return 0;
}