#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include "Board.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
// Include other necessary headers

class Serialization {
public:
    static void saveGameState(const Board& board, const Player& player1, const Player& player2, bool isPlayer1Turn, int player1Score, int player2Score);
    static bool loadGameState(Board& board, HumanPlayer& humanPlayer, ComputerPlayer& computerPlayer, bool& isPlayer1Turn);
    static int extractValue(const std::string& line);

    //static bool loadGameState(Board& board, Player& player1, Player& player2, bool& isPlayer1Turn);

#endif // SERIALIZATION_H
};