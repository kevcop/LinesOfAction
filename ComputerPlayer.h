/************************************************************
 * Name:  Kevin Chicas                                      *
 * Project:  Lines of Action - P1                           *
 * Class:  CMPS 369 - OPL                                   *
 * Date:  03/13/2024                                        *
 ************************************************************/

#pragma once
#include "Player.h"
#include "Board.h" // Ensure correct casing if your file name is "Board.h" and not "board.h"
#include "Rules.h"
#include "Round.h"
#include <vector>
#include <string>

// Assuming Move is defined as std::pair<std::pair<int, int>, std::pair<int, int>>;
struct MoveDetails {
    std::pair<int, int> start; // Starting position of the move
    std::pair<int, int> end; // Ending position of the move
    std::vector<std::pair<int, int>> captures; // Positions of captured pieces
};

class ComputerPlayer : public Player {
public:
    ComputerPlayer() = default;
    explicit ComputerPlayer(const std::string& name);

    void askPlayer() override;
    void selectPiece(char row, int col) override;
    void setDestination(char row, int col) override;
    std::pair<char, int> getSelectedPiece() const override;
    std::pair<char, int> getDestination() const override;
    std::string properNotation(std::pair<int, int> position) const override;

    void generateAllPossibleMoves( Board& board);
    void displayPossibleMoves() const;
    //vector<Move> possibleMoves;
    void processHorizontalMoves(Board& board, int fromRow, int fromCol, int horizontalMovesRequired);
    std::string revisedProperNotation(std::pair<int, int> position) const;

    //void selectAndExecuteMove(Board& board, char playerPieceType);
    std::pair<std::string, std::string> selectAndExecuteMove(Board& board, char playerPieceType);
    void addMoveIfValid( Board& board, int startRow, int startCol, int endRow, int endCol);


    // Existing method for generating moves - we'll adjust its logic to fit the new strategy

    // New method to generate valid moves, including the count-based logic and validation

    // Method to randomly select one of the valid moves
    bool attemptToAddMove(Board& board, int fromRow, int fromCol, int toRow, int toCol);
        void displayFinalPossibleMoves() const;

private:
    //vector<Move> possibleMoves;
    vector<MoveDetails> possibleMoves;
    Rules rules; // Used for validating moves
    int moveCounter = 0;
    //Round test;
};
