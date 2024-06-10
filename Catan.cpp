#include "Catan.hpp"

ariel::Catan::Catan(ariel::Player &p1, ariel::Player &p2, ariel::Player &p3) : players{p1, p2, p3},
                                                                               board(ariel::Board::get_instance()) {}

ariel::Board *ariel::Catan::getBoard() { return this->board; }

void ariel::Catan::StartingGame(std::vector<size_t> &e_placement, std::vector<size_t> &v_placement)
{
    if (e_placement.size() != 3 || v_placement.size() != 3)
    {
        throw std::runtime_error("Error: Not enough arguments passed to start the game");
    }
    for (size_t player_index = 0; player_index < MAX_NUM_OF_PLAYERS; player_index++)
    {
        players[player_index].game_start_placement(*(this->board), e_placement[player_index], v_placement[player_index]);
    }
}