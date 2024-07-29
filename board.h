/************************************************************
 * Name:  Kevin Chicas                                      *
 * Project:  Lines of Action - P1                           *
 * Class:  CMPS 366 - OPL                                   *
 * Date:  03/13/2024                                        *
 ************************************************************/

#pragma once
#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <utility> // 

using namespace std;

/**
 * @class Board
 * @brief Represents the game board for the Lines of Action game.
 *
 * This class manages the state of the game board, including piece positions,
 * validating moves, and tracking the number of pieces.
 */
class Board {
private:
    //number of rows on the board
    static const int ROWS = 8; 
    //number of columns on the board
    static const int COLS = 8; 
    //create a char array to represent the board, char was chosen due to piece representation, eg: 'B', 'W'
    char board[ROWS][COLS]; 

public:
    /**
     * Function Name: Board
     * Purpose: Constructs a new Board instance and initializes the game board.
     * Parameters: None
     * Return Value: None
     * Reference: None
     */
    Board();

    /**
     * Function Name: getCols
     * Purpose: REturns the number of columns on the board.
     * Parameters: None
     * Return Value: An integer represent num of columns
     * Reference: None
     */
    static int getCols() { return COLS; }

    /**
     * Function Name: showBoard
     * Purpose: Displays the current state of the game board.
     * Parameters: None
     * Return Value: None
     * Reference: None
     */
    void showBoard() const;

    /**
     * Function Name: resetBoard
     * Purpose: Initializes the game board to its starting state.
     * Parameters: None
     * Return Value: None
     * Reference: None
     */
    void resetBoard();

    /**
     * Function Name: placePiece
     * Purpose: Places a game piece on the board.
     * Parameters:
     *     row, an integer. The row position to place the piece.
     *     col, an integer. The column position to place the piece.
     *     pieceType, a char. The type of the piece ('B' or 'W').
     * Return Value: True if the piece was placed successfully, false otherwise.
     * Reference: None
     */
    bool placePiece(int row, int col, char pieceType);

    /**
     * Function Name: movePiece
     * Purpose: Moves a game piece on the board.
     * Parameters:
     *     startRow, startCol, endRow, endCol, integers. Specify the starting and ending positions of the move.
     *     player, a char. The player's piece type making the move.
     * Return Value: True if the move was successful, false otherwise.
     */
    bool movePiece(int startRow, int startCol, int endRow, int endCol, char player);

    /**
     * Function Name: getPieceAt
     * Purpose: Retrieves the piece type at a given position.
     * Parameters:
     *     row, col, integers. The position to check.
     * Return Value: The piece type at the specified position, a char.
     * Reference: None
     */
    char getPieceAt(int row, int col) const;

    /**
     * Function Name: isPositionValid
     * Purpose: Checks if a given position is within the board bounds.
     * Parameters:
     *     row, col, integers. The position to check.
     * Return Value: True if the position is valid, false otherwise.
     * Reference: None
     */
    bool isPositionValid(int row, int col) const;


    /**
     * Function Name: removePiece
     * Purpose: Removes a piece from the board at the specified position.
     * Parameters:
     *     row, an integer. The row position of the piece to remove.
     *     col, an integer. The column position of the piece to remove.
     * Return Value: None
     */
    void removePiece(int row, int col);

    /**
     * Function Name: countPiecesByColor
     * Purpose: Counts the total number of black and white pieces on the board.
     * Parameters: None
     * Return Value: A pair of integers representing the count of black pieces first and white pieces second.
     * Reference: None
     */
    pair<int, int> countPiecesByColor() const;

    /**
     * Function Name: setPieceAt
     * Purpose: Sets a piece of a specified type at the given position on the board.
     * Parameters:
     *     row, an integer. The row position to set the piece.
     *     col, an integer. The column position to set the piece.
     *     pieceType, a char. The type of the piece to place ('B', 'W', or '.').
     * Return Value: None
     * Reference: None
     */
    void setPieceAt(int row, int col, char pieceType);

    /**
     * Function Name: isOpponentPiece
     * Purpose: Determines if the piece at the given position belongs to the opponent.
     * Parameters:
     *     row, an integer. The row position to check.
     *     col, an integer. The column position to check.
     *     playerPieceType, a char. The piece type of the current player ('B' or 'W').
     * Return Value: True if the position contains an opponent's piece, false otherwise.
     * Reference: None
     */
    bool isOpponentPiece(int row, int col, char playerPieceType) const;

    /**
     * Function Name: clearBoard
     * Purpose: Clears the board, setting all positions to empty ('.').
     * Parameters: None
     * Return Value: None
     * Reference: None
     */
    void clearBoard();
};

#endif // BOARD_H
