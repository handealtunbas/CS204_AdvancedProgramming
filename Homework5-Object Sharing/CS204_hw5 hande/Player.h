//
// Created by Hande Altunbas on 14.05.2024.
//
#pragma once
#include <iostream>
#include "Board.h"
using namespace std;


class Player {

    private:
        Board& board;
        char piece;

    public:
        Player(Board& board, char piece);
        bool put(int col);
        void turn_board();
        bool is_winner() const;
        char get_symbol() const;


};

