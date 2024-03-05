#include "Tournament.h"
#include <iostream>

Tournament::Tournament(Player* p1, Player* p2)
    : player1(p1), player2(p2), currentRoundNumber(0), scores(2, 0) {
}


void Tournament::playNextRound() {
    currentRoundNumber++;
    std::cout << "Starting round " << currentRoundNumber << std::endl;

    Round round(player1, player2);
    round.startGame(startingPlayer);

    // Determine the round's winner and calculate the score based on the new logic
    Player* roundWinner = round.getRoundWinner();
    int scoreDifference = round.calculateScore(); // Adjust this method to return the difference in pieces
    startingPlayer = roundWinner;
    if (roundWinner == player1) {
        scores[0] += scoreDifference; // Player 1 wins and scores are updated accordingly
        std::cout << player1->getName() << " wins the round with " << scoreDifference << " points!" << std::endl;
    }
    else if (roundWinner == player2) {
        scores[1] += scoreDifference; // Player 2 wins and scores are updated accordingly
        std::cout << player2->getName() << " wins the round with " << scoreDifference << " points!" << std::endl;
    }
    else {
        // Handle a draw or no winner scenario appropriately
        std::cout << "The round ends in a draw." << std::endl;
    }

    displayScores();

    if (askToContinue()) {
        playNextRound();
    }
    else {
        declareWinner();
    }
}


// Ensure the rest of your functions like `declareWinner`, `displayScores`, and any other relevant
// method in the Tournament class are correctly handling the scores and winner logic.



void Tournament::displayScores() const {
    std::cout << "Scores after round " << currentRoundNumber << ":" << std::endl;
    std::cout << player1->getName() << ": " << scores[0] << std::endl;
    std::cout << player2->getName() << ": " << scores[1] << std::endl;
}

int Tournament::getCurrentRoundNumber() const {
    return currentRoundNumber;
}

void Tournament::declareWinner() const {
    std::cout << "Tournament over!" << std::endl;
    // Logic to determine the overall winner
    if (scores[0] > scores[1]) {
        std::cout << player1->getName() << " wins the tournament!" << std::endl;
    }
    else if (scores[1] > scores[0]) {
        std::cout << player2->getName() << " wins the tournament!" << std::endl;
    }
    else {
        std::cout << "The tournament ends in a draw!" << std::endl;
    }
}

bool Tournament::askToContinue() const {
    std::cout << "Would you like to play another round? (Y/N): ";
    char response;
    std::cin >> response;
    return (response == 'Y' || response == 'y');
}
