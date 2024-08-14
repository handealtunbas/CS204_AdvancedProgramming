//
// Created by Hande Altunbas on 14.05.2024.
//
#include <iostream>
#include "Player.h"
#include "Board.h"
using namespace std;
Player::Player(Board& board, char piece) : board(board), piece(piece) {}

// Place a piece on the board
bool Player::put(int col)
{
    return board.put_piece(piece, col);
}

// Turn the board clockwise
void Player::turn_board()
{
    board.turn_board_clockwise();
}

// Check if the player has won
bool Player::is_winner() const
{
    return board.get_game_status() == piece;
}

// Get the player's game piece
char Player::get_symbol() const
{
    return piece;
}