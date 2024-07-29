/************************************************************
 * Name:  Kevin Chicas                                      *
 * Project:  Lines of Action - P1                           *
 * Class:  CMPS 369 - OPL                                   *
 * Date:  03/12/2024                                        *
 ************************************************************/

#pragma once
#include "Player.h"
#include "Board.h" // Ensure correct casing if your file name is "Board.h" and not "board.h"
#include "Rules.h"
#include "Round.h"
#include <vector>
#include <string>

 /**
  * Struct Name: MoveDetails
  * Purpose: Holds the starting and ending positions of a move, along with positions of any captured pieces.
  * Parameters: None
  * Return Value: None
  * Reference: None
  */
struct MoveDetails {
    //starting position of the move
    pair<int, int> start; 
    //end position of the move
    pair<int, int> end; // Ending position of the move
    //position of the captured pieces
    vector<pair<int, int>> captures;
};

/**
 * Class Name: ComputerPlayer
 * Purpose: Represents a computer-controlled player in the game, capable of generating and selecting moves automatically.
 * Parameters: Inherits from Player class.
 * Return Value: None
 * Reference: None
 */
class ComputerPlayer : public Player {
public:
    ComputerPlayer() = default;
    explicit ComputerPlayer(const string& name);

    void askPlayer() override;
    void selectPiece(char row, int col) override;
    void setDestination(char row, int col) override;
    pair<char, int> getSelectedPiece() const override;
    pair<char, int> getDestination() const override;
    string properNotation(pair<int, int> position) const override;

    void generateAllPossibleMoves( Board& board);
    void displayPossibleMoves() const;
    //vector<Move> possibleMoves;
    void processHorizontalMoves(Board& board, int fromRow, int fromCol, int horizontalMovesRequired);
    string revisedProperNotation(pair<int, int> position) const;

    //void selectAndExecuteMove(Board& board, char playerPieceType);
    pair<string, string> selectAndExecuteMove(Board& board, char playerPieceType);
    void addMoveIfValid( Board& board, int startRow, int startCol, int endRow, int endCol);


    // Existing method for generating moves - we'll adjust its logic to fit the new strategy

    // New method to generate valid moves, including the count-based logic and validation

    // Method to randomly select one of the valid moves
    bool attemptToAddMove(Board& board, int fromRow, int fromCol, int toRow, int toCol);
        void displayFinalPossibleMoves() const;

private:
    //vector<Move> possibleMoves;
    //list of possible moves generated
    vector<MoveDetails> possibleMoves;
    //instance used to validate moves
    Rules rules;
    //counter for moves
    int moveCounter = 0;
    
};
