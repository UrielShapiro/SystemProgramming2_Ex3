/**
 * Demo file for Ex3.
 *
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

    catan.print_players_stats();
    std::cout << "------------------------------------------" << std::endl;
    catan.rollDice();
    try
    {
        catan.get_players()[1].placeRoad(*board, *(board->get_edges().at(14))); // p1 builds a road.
    }
    catch (const std::exception &e)
    {
        std::cerr << "\033[0;31m" << e.what() << "\033[0m" << '\n';
    }
    for (int i = 0; i < NUM_OF_TURNS + 1; i++) // Simulate the game for NUM_OF_TURNS turns to make the players get resources.
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

    // // Starting of the game. Every player places two settlements and two roads.
    // catan.ChooseStartingPlayer();   // should print the name of the starting player, assume it is Amit.
    // Board* board = catan.getBoard(); // get the board of the game.
    // vector<string> places = {"Forest", "Hills"};
    // vector<int> placesNum = {5, 6};
    // p1.placeSettelemnt(places, placesNum, board);
    // p1.placeRoad(places, placesNum, board);
    // vector<string> places = {"Agricultural Land", "Desert"};
    // vector<int> placesNum = {3, 4};
    // p1.placeSettelemnt(places, placesNum, board);
    // p1.placeRoad(places, placesNum, board); // p1 chooses Forest, hills, Agricultural Land, Desert with numbers 5, 6, 3, 4.

    // vector<string> places = {"Mountains", "Pasture Land"};
    // vector<int> placesNum = {4, 9};
    // p2.placeSettelemnt(places, placesNum, board);
    // p2.placeRoad(places, placesNum, board);
    // try
    // {
    //     p3.placeSettelemnt(places, placesNum, board); // p3 tries to place a settlement in the same location as p2.
    // }
    // catch (const std::exception &e)
    // {
    //     cout << e.what() << endl;
    // }
    // vector<string> places = {"Forest", "Pasture Land"};
    // vector<int> placesNum = {5, 9};
    // p2.placeSettelemnt(places, placesNum, board);
    // p2.placeRoad(places, placesNum, board); // p2 chooses Mountains, Pasture Land, and Forest with numbers 4, 9, 5.

    // vector<string> places = {"Mountains", "Pasture Land"};
    // vector<int> placesNum = {3, 8};
    // p3.placeSettelemnt(places, placesNum, board);
    // p3.placeRoad(places, placesNum, board);
    // vector<string> places = {"Agricultural Land", "Pasture Land"};
    // vector<int> placesNum = {3, 9};
    // p3.placeSettelemnt(places, placesNum, board);
    // p3.placeRoad(places, placesNum, board); // p3 chooses Mountains, Pasture Land, Agricultural Land, Pasture Land with numbers 3, 8, 3, 9.

    // // p1 has wood,bricks, and wheat, p2 has wood, ore, and wool, p3 has ore, wool, wheat.
    // p1.rollDice();                                    // Lets say it's print 4. Then, p2 gets ore from the mountations.
    // p1.placeRoad({"Forest", "Hills"}, {5, 6}, board); // p1 continues to build a road.
    // p1.endTurn();                                     // p1 ends his turn.

    // p2.rollDice(); // Lets say it's print 9. Then, p3 gets wool from the Pasture Land, p2 gets wool from the Pasture Land.
    // p2.endTurn();  // p2 ends his turn.

    // p3.rollDice(); // Lets say it's print 3. Then, p3 gets wheat from the Agricultural Land and Ore from the Mountains, p1 gets wheat from the Agricultural Land.
    // p3.endTurn();  // p3 ends his turn.

    // try
    // {
    //     p2.rollDice(); // p2 tries to roll the dice again, but it's not his turn.
    // }
    // catch (const std::exception &e)
    // {
    //     cout << e.what() << endl;
    // }

    // p1.rollDice();                       // Lets say it's print 6. Then, p1 gets bricks from the hills.
    // p1.trade(p2, "wood", "brick", 1, 1); // p1 trades 1 wood for 1 brick with p2.
    // p1.endTurn();                        // p1 ends his turn.

    // p2.rollDice();           // Lets say it's print 9. Then, p3 gets wool from the Pasture Land, p2 gets wool from the Pasture Land.
    // p2.buyDevelopmentCard(); // p2 buys a development card. Lets say it is a bonus points card.
    // p2.endTurn();            // p2 ends his turn.

    // p1.printPoints(); // p1 has 2 points because it has two settelments.
    // p2.printPoints(); // p2 has 3 points because it has two settelments and a bonus points card.
    // p3.printPoints(); // p3 has 2 points because it has two settelments.

    // catan.printWinner(); // Should print None because no player reached 10 points.
    return 0;
}