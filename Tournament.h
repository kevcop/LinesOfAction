/************************************************************
 * Name:  Kevin Chicas                                      *
 * Project:  Lines of Action - P1                           *
 * Class:  CMPS 369 - OPL                                   *
 * Date:  03/13/2024                                        *
 ************************************************************/
#pragma once

#include <memory> // For std::unique_ptr
#include <vector>
#include "Player.h"
#include "Round.h" // Ensure this is correctly included

 /**
  * @class Tournament
  * @brief Manages the progression of rounds in the game tournament.
  *
  * This class handles the orchestration of multiple rounds in the tournament, keeping track of
  * the overall scores, current round number, and which player starts the next round.
  */
class Tournament {
private:
    int currentRoundNumber; ///< Tracks the current round number in the tournament.
    std::vector<int> scores; ///< Scores for the players, assuming two players.
    std::shared_ptr<Player> player1; ///< Shared pointer to the first player.
    std::shared_ptr<Player> player2; ///< Shared pointer to the second player.
    std::shared_ptr<Player> startingPlayer; ///< The player who starts the next round.

public:
    /**
     * @brief Constructs a Tournament object with two players.
     * @param p1 A shared pointer to the first player.
     * @param p2 A shared pointer to the second player.
     */
    Tournament(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2);

    /**
     * @brief Initiates the gameplay for the next round in the tournament.
     */
    void playNextRound();

    /**
     * @brief Displays the current scores of both players.
     */
    void displayScores() const;

    /**
     * @brief Retrieves the current round number in the tournament.
     * @return The current round number as an integer.
     */
    int getCurrentRoundNumber() const;

    /**
     * @brief Declares the overall winner of the tournament based on scores or rounds won.
     */
    void declareWinner() const;

    /**
     * @brief Asks the player if they want to continue to the next round.
     * @return True if the player chooses to continue, false otherwise.
     */
    bool askToContinue() const;

    /**
     * @brief Resumes the tournament from a previously saved state.
     * @param loadedRound A unique pointer to the loaded round.
     */
    void resumeTournament(std::unique_ptr<Round> loadedRound);
};
