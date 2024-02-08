#pragma once
#ifndef BOARD_H
#define BOARD_H
#include <iostream>
using namespace std;

class Board {
private:
    static const int ROWS = 8; //row dimension
    static const int COLS = 8; //column dimension
    char board[ROWS][COLS]; //char type was used for improved board visibility, B - black, W - white, ' ' - space

public:
    Board();//construct
    void showBoard() const;//display board
    void resetBoard();//initialize board
};
#endif