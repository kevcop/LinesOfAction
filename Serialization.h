/************************************************************
 * Name:  Kevin Chicas                                      *
 * Project:  Lines of Action - P1                           *
 * Class:  CMPS 369 - OPL                                   *
 * Date:  03/13/2024                                        *
 ************************************************************/
#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <fstream>
#include <memory>
#include <string>
#include "Board.h"
#include "Player.h"
#include "HumanPlayer.h"
 // Forward declarations to avoid circular dependencies.
class Round;
class ComputerPlayer;

/**
 * @class Serialization
 * @brief Handles saving and loading of game state.
 *
 * Provides static methods to serialize (save) and deserialize (load)
 * the current state of the game to and from a file.
 */
class Serialization {
public:
    /**
     * @brief Saves the current state of the game.
     * @param round The current round of the game to be saved.
     */
    static void saveGameState(const Round& round);

    /**
     * @brief Extracts an integer value from a given line of text.
     * @param line The string line containing the value.
     * @return The extracted integer value.
     */
    static int extractValue(const string& line);

    /**
     * @brief Processes player data from an input file stream.
     * @param inFile The input file stream to read from.
     * @param player The player object to load data into.
     */
    static void processPlayerData(ifstream& inFile, shared_ptr<Player> player);

    /**
     * @brief Loads the game state from a file.
     * @param filename The name of the file to load the game state from.
     * @return A unique pointer to the loaded Round object, or nullptr if loading fails.
     */
    static unique_ptr<Round> loadGameState(const string& filename);
};

#endif // SERIALIZATION_H
