#pragma once
#include "Board.hpp"
#include "GameConsts.hpp"

#define MAX_NUM_OF_PLAYERS 3
#define POINTS_TO_WIN 10
#define INITIATE_LARGEST_ARMY 3

namespace ariel
{
    class Catan
    {
    private:
        size_t largest_army;
        size_t turn;
        Board *board;
        Player players[MAX_NUM_OF_PLAYERS];

    public:
        Catan(ariel::Player &p1, ariel::Player &p2, ariel::Player &p3);
        Board *getBoard();
        void StartingGame(std::vector<size_t> &e_placement, std::vector<size_t> &v_placement);
        void rollDice();
        bool check_winner();
        bool check_largest_army();
        GameConsts::DevelopmentCard buyDevelopmentCard(Player &p);
        void use_development_card(ariel::Player &p, GameConsts::DevelopmentCard card);
        void GameCheck();
    };
}