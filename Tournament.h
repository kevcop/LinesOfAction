#pragma once
#include "Round.h"
#include <vector>

class Tournament {
private:
    int currentRoundNumber;
    std::vector<int> scores; // Assuming two players, index 0 for player1 and index 1 for player2
    Player* player1;
    Player* player2;

public:
    Tournament(Player* p1, Player* p2);
    void playNextRound();
    void displayScores() const;
    int getCurrentRoundNumber() const;
    void declareWinner() const;
    bool askToContinue() const; // Ask the user if they want to continue to the next round
};
