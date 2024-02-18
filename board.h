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
    static int getCols() { return COLS; } //return num of cols
    void showBoard() const;//display board
    void resetBoard();//initialize board
    bool placePiece(int row, int col, char pieceType); //place piece
    bool movePiece(int startRow, int startCol, int endRow, int endCol, char player); //actual movement
    char getPieceAt(int row, int col) const; //retrieve a particular piece
    bool isPositionValid(int row, int col) const; //determine if location is within bounds
    void removePiece(int row, int col);
    pair<int, int> countPiecesByColor() const;
};
#endif