#pragma once
#ifndef RULES_H
#define RULES_H

#include "board.h"
#include "Player.h"
#include <utility>
#include <vector>

class Rules {
public:
    // Determines if a move is valid
    static bool isValidMove(Board& board, const Player& player, int startRow, int startCol, int endRow, int endCol);

    // Determines if the path between the start and end positions is clear
    static bool isPathClear(const Board& board, int startRow, int startCol, int endRow, int endCol, char playerPieceType, std::vector<std::pair<int, int>>& capturePositions);

    // Checks if the ending position of a move is valid
    static bool isValidEndingPosition(const Board& board, int endRow, int endCol, char pieceType);

    // Counts the number of pieces in a straight line from a given position
    static int countPiecesInLine(const Board& board, int startRow, int startCol, char direction);

    // Counts the pieces on a diagonal line from a given position
    static int countDiagonalPieces(const Board& board, int startRow, int startCol, int endRow, int endCol);

    // Determines the direction of a diagonal move
    static char determineDiagonalDirection(int startRow, int startCol, int endRow, int endCol);

    // Processes the captures of opponent pieces on the board
    static void processCaptures(Board& board, const std::vector<std::pair<int, int>>& captures);

    // Checks if the win condition has been met
    static bool checkWinCondition(const Board& board, const Player& player);

private:
    static std::pair<int, int> directionOffsets(char direction); // Method to calculate direction offsets for diagonal logic
};

#endif
