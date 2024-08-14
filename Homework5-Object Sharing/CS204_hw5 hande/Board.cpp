//
// Created by Hande Altunbas on 14.05.2024.
//
#include <iostream>
#include "Board.h"
using namespace std;

Board::Board(int boardSize, int N) : size(boardSize), N(N)
{
    matrix = new char*[size]; //create size many rows
    for(int i=0; i < size; i++)
    {
        matrix[i] = new char[size]; //create size many columns
        for (int j = 0; j < size; ++j)
        {
            matrix[i][j] = '-'; //assign empty cells to all
        }
    }

}

Board::~Board() //destructor
{
    for (int i = 0; i < size; ++i)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void Board::print_board() //printing the matrix game
{
    cout << endl; //empty line according to hw file
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << matrix[i][j] ;
        }
        cout << endl; //end line after each row
    }
    cout << endl; //empty line again according to the hw file
}

bool Board::put_piece(char symbol, int col) //assign piece to the matrix
{
    bool isPut = false; //assign a boolean value isPut to false
    for(int i=size-1 ; i > -1; i--) //start from the bottom of the column (ie size-1 since index starts from 0)
    {
        if(matrix[i][col] == '-') //if the most bottom is empty assign the symbol to the cell
        {
            matrix[i][col] = symbol; //assign the symbol
            isPut = true; //isPut is true since it is assigned
            i = -1; //assign i to -1 to exit the loop since it has put
        }
    }
    return isPut;
}

void Board::turn_board_clockwise()
{
    // Create a new matrix for the rotated board
    char** new_matrix = new char*[size];
    for (int i = 0; i < size; ++i)
    {
        new_matrix[i] = new char[size];
    }

    // Rotate the board 90 degrees clockwise
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            new_matrix[j][size - 1 - i] = matrix[i][j];
        }
    }

    // Apply gravity: make the pieces fall to the bottom of their respective columns
    for (int col = 0; col < size; ++col)
    {
        int empty_row = size - 1;
        for (int row = size - 1; row >= 0; --row)
        {
            if (new_matrix[row][col] != '-')
            {
                new_matrix[empty_row][col] = new_matrix[row][col];
                if (empty_row != row)
                {
                    new_matrix[row][col] = '-';
                }
                empty_row--;
            }
        }
    }

    // Delete the old matrix
    for (int i = 0; i < size; ++i)
    {
        delete[] matrix[i];
    }
    delete[] matrix;

    // Point matrix to the new rotated matrix
    matrix = new_matrix;
}

char Board::get_game_status()
{
    bool x_wins = false;
    bool o_wins = false;
    bool is_full = true;

    // Check for vertical wins
    for (int j = 0; j < size; ++j)
    {
        int x_count = 0, o_count = 0;
        for (int i = 0; i < size; ++i)
        {
            if (matrix[i][j] == 'X')
            {
                x_count++;
                o_count = 0;
            }
            else if (matrix[i][j] == 'O')
            {
                o_count++;
                x_count = 0;
            }
            else
            {
                x_count = 0;
                o_count = 0;
                is_full = false; // Found an empty cell
            }

            if (x_count > N-1) x_wins = true;
            if (o_count > N-1) o_wins = true;
        }
    }

    // Check for horizontal wins
    for (int i = 0; i < size; ++i)
    {
        int x_count = 0, o_count = 0;
        for (int j = 0; j < size; ++j)
        {
            if (matrix[i][j] == 'X')
            {
                x_count++;
                o_count = 0;
            }
            else if (matrix[i][j] == 'O')
            {
                o_count++;
                x_count = 0;
            }
            else
            {
                x_count = 0;
                o_count = 0;
                is_full = false; // Found an empty cell
            }

            if (x_count > N-1) x_wins = true;
            if (o_count > N-1) o_wins = true;
        }
    }

    // Check for diagonal wins (top-left to bottom-right)
    for (int start = 0; start <= size - N; ++start)
    {
        int x_count = 0, o_count = 0;
        for (int i = 0; i < size - start; ++i)
        {
            if (matrix[start + i][i] == 'X')
            {
                x_count++;
                o_count = 0;
            }
            else if (matrix[start + i][i] == 'O')
            {
                o_count++;
                x_count = 0;
            }
            else
            {
                x_count = 0;
                o_count = 0;
                is_full = false; // Found an empty cell
            }

            if (x_count > N-1) x_wins = true;
            if (o_count > N-1) o_wins = true;
        }
    }

    for (int start = 1; start <= size - N; ++start)
    {
        int x_count = 0, o_count = 0;
        for (int i = 0; i < size - start; ++i)
        {
            if (matrix[i][start + i] == 'X')
            {
                x_count++;
                o_count = 0;
            }
            else if (matrix[i][start + i] == 'O')
            {
                o_count++;
                x_count = 0;
            }
            else
            {
                x_count = 0;
                o_count = 0;
                is_full = false; // Found an empty cell
            }

            if (x_count > N-1) x_wins = true;
            if (o_count > N-1) o_wins = true;
        }
    }

    // Check for diagonal wins (bottom-left to top-right)
    for (int start = 0; start <= size - N; ++start)
    {
        int x_count = 0, o_count = 0;
        for (int i = 0; i < size - start; ++i)
        {
            if (matrix[size - 1 - (start + i)][i] == 'X')
            {
                x_count++;
                o_count = 0;
            }
            else if (matrix[size - 1 - (start + i)][i] == 'O')
            {
                o_count++;
                x_count = 0;
            }
            else
            {
                x_count = 0;
                o_count = 0;
                is_full = false; // Found an empty cell
            }

            if (x_count > N-1) x_wins = true;
            if (o_count > N-1) o_wins = true;
        }
    }

    for (int start = 1; start <= size - N; ++start)
    {
        int x_count = 0, o_count = 0;
        for (int i = 0; i < size - start; ++i)
        {
            if (matrix[size - 1 - i][start + i] == 'X')
            {
                x_count++;
                o_count = 0;
            }
            else if (matrix[size - 1 - i][start + i] == 'O')
            {
                o_count++;
                x_count = 0;
            }
            else
            {
                x_count = 0;
                o_count = 0;
                is_full = false; // Found an empty cell
            }

            if (x_count > N-1) x_wins = true;
            if (o_count > N-1) o_wins = true;
        }
    }

    if (x_wins && o_wins)
    {
        return 'D'; // Both players won, which is an invalid game state but treat it as a draw
    }
    else if (x_wins)
    {
        return 'X';
    }
    else if (o_wins)
    {
        return 'O';
    }
    else if (is_full)
    {
        return 'D'; // Board is full and no winner
    }
    else
    {
        return '-'; // Game is still ongoing
    }
}


