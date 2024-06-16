/**
 * @ID: 9745
 * @name: Uriel Shapiro
 * @email: uriel1999@gmail.com
 */

#include <iostream>
#include <stdexcept>
#include <vector>
#include "Catan.hpp"
#include "Player.hpp"
#include "Board.hpp"
using namespace std;
using namespace ariel;

#define NUM_OF_TURNS MAX_NUM_OF_PLAYERS * 5

int main()
{
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3);

    Board *board = catan.getBoard(); // get the board of the game.

    std::vector<size_t> e_placement = {26, 18, 13, 55, 58, 52};
    std::vector<size_t> v_placement = {1, 0, 1, 1, 0, 1};

    catan.StartingGame(e_placement, v_placement); // Will place the initial buildings and roads for the players.

    catan.rollDice();
    try
    {
        std::vector<GameConsts::ResourceCard> resources_vec = {GameConsts::ResourceCard::Wool, GameConsts::ResourceCard::Wool};
        catan.get_players()[0].trade(catan.get_players()[2], resources_vec);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    catan.GameCheck();  // Would change the turn to the next player.

    try
    {
        catan.get_players()[1].placeRoad(*board, *(board->get_edges().at(14))); // p1 builds a road.
    }
    catch (const std::exception &e)
    {
        std::cerr << "\033[0;31m" << e.what() << "\033[0m" << '\n';
    }

    for (int i = 0; i < NUM_OF_TURNS; i++) // Simulate the game for NUM_OF_TURNS turns to make the players get resources.
    {
        catan.rollDice();
    }
    
    try
    {
        catan.buyDevelopmentCard(catan.get_players()[2]);                                                          // p3 buys a development card.
        catan.use_development_card(catan.get_players()[2], catan.get_players()[2].get_development_cards().back()); // p3 uses the development card.
    }
    catch (const std::exception &e)
    {
        std::cerr << "\033[0;31m" << e.what() << "\033[0m" << '\n';
    }
    catan.rollDice();

    try
    {
        catan.get_players()[0].placeSettelemnt(*board, *(board->get_vertices().at(4)), "City"); // p1 builds a city on vertex 4.
    }
    catch (const std::exception &e)
    {
        std::cerr << "\033[0;31m" << e.what() << "\033[0m" << '\n';
    }

    catan.print_players_stats();
    std::cout << "------------------------------------------" << std::endl;
    
    return 0;
}