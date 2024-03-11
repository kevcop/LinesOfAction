/************************************************************
 * Name:  Kevin Chicas                                      *
 * Project:  Lines of Action - P1                           *
 * Class:  CMPS 369 - OPL                                   *
 * Date:  03/13/2024                                        *
 ************************************************************/
#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <utility>
using namespace std;

/**
 * @class Player
 * @brief Represents a player in the game.
 *
 * This abstract class defines the common interface and data for all players in the game,
 * including both human and computer players.
 */
class Player {
protected:
    // used for storing name of player
    string playerName;
    //used as initial piece selected for making a move
    std::pair<char, int> piece;
    //used for storing desired destination for move 
    std::pair<char, int> destination; 
    //used for keeping track of type of piece 
    char pieceType;
    ///< Indicates whether the player won the last round.
    bool wonLastRound = false; 
    // Total number of rounds won by the player.
    int roundsWon = 0; 
    //keeps track of score
    int score = 0;

public:
    /**
     * @brief Default constructor for creating a Player object.
     */
    Player() = default;

    /**
     * @brief Constructs a Player with a given name.
     * @param name The name of the player.
     */
    explicit Player(const std::string& name) : playerName(name) {}

    /**
     * @brief Virtual destructor for the Player class.
     */
    virtual ~Player() {}

    /**
     * @brief Pure virtual function to prompt the player for input.
     */
    virtual void askPlayer() = 0;

    /**
     * @brief Pure virtual function for selecting a piece on the board.
     * @param row The row character of the piece to select.
     * @param col The column integer of the piece to select.
     */
    virtual void selectPiece(char row, int col) = 0;

    /**
     * @brief Pure virtual function to set the desired destination for a move.
     * @param row The row character of the destination.
     * @param col The column integer of the destination.
     */
    virtual void setDestination(char row, int col) = 0;

    /**
     * @brief Pure virtual function to retrieve the selected piece.
     * @return The selected piece's position as a pair of row (char) and column (int).
     */
    virtual pair<char, int> getSelectedPiece() const = 0;

    /**
     * @brief Pure virtual function to retrieve the chosen destination for a move.
     * @return The chosen destination's position as a pair of row (char) and column (int).
     */
    virtual pair<char, int> getDestination() const = 0;

    /**
     * @brief Pure virtual function to convert positions to a chess-like notation.
     * @param position The board position to convert.
     * @return A string representing the position in chess notation (e.g., A6).
     */
    virtual string properNotation(std::pair<int, int> position) const = 0;

    /**
     * @brief Retrieves the player's name.
     * @return The name of the player as a string.
     */
    string getName() const { return playerName; }

    /**
     * @brief Sets the piece type for the player.
     * @param type The piece type ('B' or 'W').
     */
    void setPieceType(char type) { pieceType = type; }

    /**
     * @brief Retrieves the player's piece type.
     * @return The piece type ('B' or 'W').
     */
    char getPieceType() const { return pieceType; }

    /**
     * @brief Sets whether the player won the last round.
     * @param won True if the player won the last round, false otherwise.
     */
    void setWonLastRound(bool won) { wonLastRound = won; }

    /**
     * @brief Retrieves whether the player won the last round.
     * @return True if the player won the last round, false otherwise.
     */
    bool getWonLastRound() { return wonLastRound; }

    /**
     * @brief Sets the total number of rounds won by the player.
     * @param newRoundsWon The new total of rounds won.
     */
    void setRoundsWon(int newRoundsWon) { roundsWon = newRoundsWon; }

    /**
     * @brief Sets the player's score.
     * @param newScore The new score for the player.
     */
    void setScore(int newScore) { score = newScore; }

    /**
     * @brief Retrieves the total number of rounds won by the player.
     * @return The total number of rounds won.
     */
    int getRoundsWon() const { return roundsWon; }

    /**
     * @brief Retrieves the player's current score.
     * @return The player's score.
     */
    int getScore() const { return score; }
};

#endif


