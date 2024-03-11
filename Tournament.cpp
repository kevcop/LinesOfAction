#include "Tournament.h"
#include <iostream>

//Tournament::Tournament(Player* p1, Player* p2)
//    : player1(p1), player2(p2), currentRoundNumber(0), scores(2, 0) {
//}

Tournament::Tournament(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2)
    : player1(p1), player2(p2), currentRoundNumber(0), scores(2, 0) {
}


//void Tournament::playNextRound() {
//    currentRoundNumber++;
//    std::cout << "Starting round " << currentRoundNumber << std::endl;
//
//    Round round(player1, player2);
//    round.startGame(startingPlayer);
//
//    // Determine the round's winner and calculate the score based on the new logic
//    shared_ptr<Player> roundWinner = round.getRoundWinner();
//    int scoreDifference = round.calculateScore(); // Adjust this method to return the difference in pieces
//    cout << "This is difference within playNextRound" << scoreDifference << endl;
//    startingPlayer = roundWinner;
//    if (roundWinner == player1) {
//        scores[0] += scoreDifference; // Player 1 wins and scores are updated accordingly
//        std::cout << player1->getName() << " wins the round with " << scoreDifference << " points!" << std::endl;
//    }
//    else if (roundWinner == player2) {
//        scores[1] += scoreDifference; // Player 2 wins and scores are updated accordingly
//        std::cout << player2->getName() << " wins the round with " << scoreDifference << " points!" << std::endl;
//    }
//    else {
//        // Handle a draw or no winner scenario appropriately
//        std::cout << "The round ends in a draw." << std::endl;
//    }
//
//    displayScores();
//
//    if (askToContinue()) {
//        playNextRound();
//    }
//    else {
//        declareWinner();
//    }
//}
//
//
//CALCS CORRECTLY
//void Tournament::playNextRound() {
//    currentRoundNumber++;
//    std::cout << "Starting round " << currentRoundNumber << std::endl;
//
//    Round round(player1, player2);
//    round.startGame(startingPlayer);
//
//    // The winner is already set inside the round class, and scores are updated there
//    //round.updateScores(); // This will now update the scores within the round
//
//    // Now we retrieve the winner from the round and display the outcome
//    shared_ptr<Player> roundWinner = round.getRoundWinner();
//    if (roundWinner == player1) {
//        std::cout << player1->getName() << " wins the round with "
//            << round.getPlayer1Score() << " points!" << std::endl;
//        scores[0] = round.getPlayer1Score(); // Make sure this sets the score, not just adds to it
//    }
//    else if (roundWinner == player2) {
//        std::cout << player2->getName() << " wins the round with "
//            << round.getPlayer2Score() << " points!" << std::endl;
//        scores[1] = round.getPlayer2Score(); // Make sure this sets the score, not just adds to it
//    }
//    else {
//        std::cout << "The round ends in a draw." << std::endl;
//    }
//
//    displayScores();
//
//    if (askToContinue()) {
//        playNextRound();
//    }
//    else {
//        declareWinner();
//    }
//}

void Tournament::playNextRound() {
    currentRoundNumber++;
    std::cout << "Starting round " << currentRoundNumber << std::endl;

    Round round(player1, player2);
    round.startGame(startingPlayer);

    // The winner is already set inside the round class, and scores are updated there
    //round.updateScores(); // This will now update the scores within the round

    // Retrieve the winner from the round and display the outcome
    shared_ptr<Player> roundWinner = round.getRoundWinner();

    // Update startingPlayer for the next round
    startingPlayer = roundWinner; // This is crucial to set the first player for the next round

    if (roundWinner == player1) {
        scores[0] = round.getPlayer1Score();
        std::cout << player1->getName() << " wins the round with "
            << scores[0] << " points!" << std::endl;
    }
    else if (roundWinner == player2) {
        scores[1] = round.getPlayer2Score();
        std::cout << player2->getName() << " wins the round with "
            << scores[1] << " points!" << std::endl;
    }
    else {
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

//void Tournament::declareWinner() const {
//    std::cout << "Tournament over!" << std::endl;
//    // Logic to determine the overall winner
//    if (scores[0] > scores[1]) {
//        std::cout << player1->getName() << " wins the tournament!" << std::endl;
//    }
//    else if (scores[1] > scores[0]) {
//        std::cout << player2->getName() << " wins the tournament!" << std::endl;
//    }
//    else {
//        std::cout << "The tournament ends in a draw!" << std::endl;
//    }
//}

void Tournament::declareWinner() const {
    std::cout << "Tournament over!" << std::endl;
    cout << "Player 1 amount won: " << player1->getRoundsWon() << endl;
    cout << "Player 2 amount won: " << player2->getRoundsWon() << endl;

    // Logic to determine the overall winner based on rounds won
    if (player1->getRoundsWon() > player2->getRoundsWon()) {
        std::cout << player1->getName() << " wins the tournament with "
            << player1->getRoundsWon() << " rounds won!" << std::endl;
    }
    else if (player2->getRoundsWon() > player1->getRoundsWon()) {
        std::cout << player2->getName() << " wins the tournament with "
            << player2->getRoundsWon() << " rounds won!" << std::endl;
    }
    else {
        // If the number of rounds won is equal, the tournament ends in a draw
        std::cout << "The tournament ends in a draw!" << std::endl;
    }
}


//void Tournament::declareWinner() const {
//    std::cout << "Tournament over!" << std::endl;
//    // Compare rounds won first
//    if (player1->getRoundsWon() > player2->getRoundsWon()) {
//        std::cout << player1->getName() << " wins the tournament based on rounds won!" << std::endl;
//    }
//    else if (player2->getRoundsWon() > player1->getRoundsWon()) {
//        std::cout << player2->getName() << " wins the tournament based on rounds won!" << std::endl;
//    }
//    else { // If rounds won are equal, use scores as a tiebreaker
//        if (scores[0] > scores[1]) {
//            std::cout << player1->getName() << " wins the tournament based on score!" << std::endl;
//        }
//        else if (scores[1] > scores[0]) {
//            std::cout << player2->getName() << " wins the tournament based on score!" << std::endl;
//        }
//        else {
//            std::cout << "The tournament ends in a draw!" << std::endl;
//        }
//    }
//}


bool Tournament::askToContinue() const {
    std::cout << "Would you like to play another round? (Y/N): ";
    char response;
    std::cin >> response;
    return (response == 'Y' || response == 'y');
}

void Tournament::resumeTournament(std::unique_ptr<Round> loadedRound) {
    // Assuming rounds won are cumulative and represent completed rounds
    int roundsWonByPlayer1 = loadedRound->getPlayer1()->getRoundsWon();
    int roundsWonByPlayer2 = loadedRound->getPlayer2()->getRoundsWon();
    // Current round number is the sum of rounds won by both players plus one
    currentRoundNumber = roundsWonByPlayer1 + roundsWonByPlayer2 + 1;

    // Display current tournament state
    cout << "Resuming Tournament at Round " << currentRoundNumber << "." << endl;
    loadedRound->getGameBoard().showBoard();
    cout << "It's " << loadedRound->getCurrentPlayer()->getName() << "'s turn." << endl;
    cout << "Human Rounds Won: " << roundsWonByPlayer1 << ", Score: " << loadedRound->getPlayer1()->getScore() << endl;
    cout << "Computer Rounds Won: " << roundsWonByPlayer2 << ", Score: " << loadedRound->getPlayer2()->getScore() << endl;

    loadedRound->continueRound();
    // Here, you would continue the gameplay using the loadedRound. Depending on your game's design, 
    // you might call a method to start or continue the round's gameplay.
    // For example:
    // loadedRound->continueGame(); // This is a hypothetical method you would need to implement in Round class.

    // After resuming and completing the current round, decide if the tournament continues
    if (askToContinue()) {
        playNextRound();
        // Continue to next round or end the tournament based on your logic
    }
}


