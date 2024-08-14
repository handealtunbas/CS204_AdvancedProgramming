//
// Created by Hande Altunbas on 14.05.2024.
//
#pragma once
#include <iostream>
using namespace std;



class Board {

    private:
        char** matrix;
        int size;
        int N;

    public:
        Board( int boardSize, int N);
        ~Board();
        void print_board();
        bool put_piece(char symbol, int col);
        void turn_board_clockwise();
        char get_game_status();
};

