#include "Catan.hpp"

ariel::Catan::Catan(ariel::Player &p1, ariel::Player &p2, ariel::Player &p3) : players{p1, p2, p3},
                                                                               board(ariel::Board::get_instance()) {}

