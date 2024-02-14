#pragma once
#ifndef RULES_H
#define RULES_H

#include "board.h"
#include "Player.h"
#include <utility>

class Rules {
public:
    //determine if move is valid
    static bool isValidMove(const Board& board, const Player& player, int startRow, int startCol, int endRow, int endCol);
    //determine amount of space moves
    static int countPiecesInLine(const Board& board, int row, int col, char direction);
    //not yet implemented but capturing logic
    static bool handleCapture(Board& board, int endRow, int endCol);
    //check for won round
    static bool checkWinCondition(const Board& board, const Player& player);
    //check if path is valid
    static bool isPathClear(const Board& board, int startRow, int startCol, int endRow, int endCol, char playerPieceType);
    //determine if ending spot is valid 
    static bool isValidEndingPosition(const Board& board, int endRow, int endCol, char pieceType);
    //method to handle diagonal moves
    static int countDiagonalPieces(const Board& board, int row, int col);
private:
    static std::pair<int, int> directionOffsets(char direction); //diagonal logic

#endif
};