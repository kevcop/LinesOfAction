#pragma once
#ifndef BOARD_H
#define BOARD_H
#include <iostream>
using namespace std;

class Board {
private:
    const static int ROWS = 8; //row dimension
    const static int COLS = 8; //column dimension
    char board[ROWS][COLS]; //char type was used for improved board visibility, B - black, W - white, ' ' - space

public:
    Board();//construct
    void showBoard();//display board
    void createBoard();//initialize board
};
#endif