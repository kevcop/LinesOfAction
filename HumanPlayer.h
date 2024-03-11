/************************************************************
 * Name:  Kevin Chicas                                      *
 * Project:  Lines of Action - P1                           *
 * Class:  CMPS 369 - OPL                                   *
 * Date:  03/13/2024                                        *
 ************************************************************/
#pragma once
#include "Player.h"
#include <string>

 /**
  * @class HumanPlayer
  * @brief Represents a human player in the game.
  *
  * This class is derived from the Player class and represents a human-controlled player.
  * It overrides the virtual functions defined in the Player class to implement human-specific interactions.
  */
class HumanPlayer : public Player {
public:
    /**
     * @brief Default constructor for creating a HumanPlayer object.
     */
    HumanPlayer() = default;

    /**
     * @brief Constructs a HumanPlayer with a given name.
     * @param name The name of the human player.
     */
    explicit HumanPlayer(const string& name);

    /**
     * @brief Prompts the human player for input.
     */
    void askPlayer() override;

    /**
     * @brief Allows the human player to select a piece on the board.
     * @param row The row character of the piece to select.
     * @param col The column integer of the piece to select.
     */
    void selectPiece(char row, int col) override;

    /**
     * @brief Sets the desired destination for a move by the human player.
     * @param row The row character of the destination.
     * @param col The column integer of the destination.
     */
    void setDestination(char row, int col) override;

    /**
     * @brief Retrieves the selected piece by the human player.
     * @return The selected piece's position as a pair of row (char) and column (int).
     */
    std::pair<char, int> getSelectedPiece() const override;

    /**
     * @brief Retrieves the chosen destination for a move by the human player.
     * @return The chosen destination's position as a pair of row (char) and column (int).
     */
    std::pair<char, int> getDestination() const override;

    /**
     * @brief Converts positions to a chess-like notation for the human player.
     * @param position The board position to convert.
     * @return A string representing the position in chess notation (e.g., A6).
     */
    std::string properNotation(std::pair<int, int> position) const override;
};
