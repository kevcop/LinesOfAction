#include "Tournament.h"
#include <iostream>
/**
 * Function Name: Tournament
 * Purpose: Constructor for the Tournament class, initializing two players.
 * Parameters:
 *     p1, a shared pointer to Player, representing the first player.
 *     p2, a shared pointer to Player, representing the second player.
 * Return Value: None
 * Algorithm:
 *     1. Initialize player1 and player2 with p1 and p2, respectively.
 *     2. Set currentRoundNumber to 0 and initialize scores for both players to 0.
 * Reference: None
 */
Tournament::Tournament(shared_ptr<Player> p1, shared_ptr<Player> p2)
    : player1(p1), player2(p2), currentRoundNumber(0), scores(2, 0) {
}

/**
 * Function Name: playNextRound
 * Purpose: Initiates and plays the next round of the tournament.
 * Parameters: None
 * Return Value: None
 * Algorithm:
 *     1. Increment the current round number and announce the start of the new round.
 *     2. Start a new round with the two players and determine the winner.
 *     3. Update the scores and determine the starting player for the next round.
 *     4. Display the updated scores after the round.
 *     5. Ask the user if they wish to continue with another round or declare the overall tournament winner.
 * Reference: None
 */
void Tournament::playNextRound() {
    //increment round number 
    currentRoundNumber++;
    //indicate which round number is being played
    cout << "Starting round " << currentRoundNumber << endl;
    //create a newe round with the players
    Round round(player1, player2);
    //start the round with a designated starting player
    round.startGame(startingPlayer);


    // Retrieve the winner from the round and display the outcome
    shared_ptr<Player> roundWinner = round.getRoundWinner();

    // Update startingPlayer for the next round
    startingPlayer = roundWinner; 
    //output necessary messages indicating who won and score
    if (roundWinner == player1) {
        scores[0] = round.getPlayer1Score();
        cout << player1->getName() << " wins the round with "
            << scores[0] << " points!" << endl;
    }
    else if (roundWinner == player2) {
        scores[1] = round.getPlayer2Score();
        cout << player2->getName() << " wins the round with "
            << scores[1] << " points!" << endl;
    }
    else {
        cout << "The round ends in a draw." << endl;
    }
    //display scores at the end of a row
    displayScores();
    //ask  if users would like to play another round
    if (askToContinue()) {
        playNextRound();
    }
    //if no desire to play another round, determine an overall winner of the tournament
    else {
        declareWinner();
    }
}
/**
 * Function Name: displayScores
 * Purpose: Displays the current scores of the tournament.
 * Parameters: None
 * Return Value: None
 * Algorithm:
 *     1. Print the scores of both players after the current round.
 * Reference: None
 */
void Tournament::displayScores() const {
    //display scores
    cout << "Scores after round " << currentRoundNumber << ":" << endl;
    cout << player1->getName() << ": " << scores[0] << endl;
    cout << player2->getName() << ": " << scores[1] << endl;
}
/**
 * Function Name: getCurrentRoundNumber
 * Purpose: Retrieves the current round number of the tournament.
 * Parameters: None
 * Return Value: The current round number as an integer.
 * Algorithm: Simply returns the value of the currentRoundNumber member variable.
 * Reference: None
 */
int Tournament::getCurrentRoundNumber() const {
    //return current round num
    return currentRoundNumber;
}

/**
 * Function Name: declareWinner
 * Purpose: Declares the overall winner of the tournament based on rounds won.
 * Parameters: None
 * Return Value: None
 * Algorithm:
 *     1. Compare the number of rounds won by each player to determine the tournament winner.
 *     2. Announce the winner or declare a draw if the number of rounds won is equal.
 * Reference: None
 */
void Tournament::declareWinner() const {
    cout << "Tournament over!" << endl;
    cout << "Player 1 amount won: " << player1->getRoundsWon() << endl;
    cout << "Player 2 amount won: " << player2->getRoundsWon() << endl;

    // Logic to determine the overall winner based on rounds won
    if (player1->getRoundsWon() > player2->getRoundsWon()) {
        cout << player1->getName() << " wins the tournament with "
            << player1->getRoundsWon() << " rounds won!" << endl;
    }
    else if (player2->getRoundsWon() > player1->getRoundsWon()) {
        cout << player2->getName() << " wins the tournament with "
            << player2->getRoundsWon() << " rounds won!" << endl;
    }
    else {
        // If the number of rounds won is equal, the tournament ends in a draw
        cout << "The tournament ends in a draw!" << endl;
    }
}
/**
 * Function Name: askToContinue
 * Purpose: Asks the user if they wish to continue with another round.
 * Parameters: None
 * Return Value: A boolean indicating whether the user wishes to continue.
 * Algorithm:
 *     1. Prompt the user to decide if they want to play another round.
 *     2. Return true for yes, false for no.
 * Reference: None
 */
bool Tournament::askToContinue() const {
    //prompt user if they would like to play another round
    cout << "Would you like to play another round? (Y/N): ";
    char response;
    cin >> response;
    return (response == 'Y' || response == 'y');
}
/**
 * Function Name: resumeTournament
 * Purpose: Resumes the tournament from a previously saved round.
 * Parameters:
 *     loadedRound, a unique pointer to a Round object representing the loaded round state.
 * Return Value: None
 * Algorithm:
 *     1. Set the current round number based on the loaded round's details.
 *     2. Display the current tournament state and proceed with the loaded round.
 *     3. Decide if the tournament continues after the loaded round based on user input.
 * Reference: None
 */
void Tournament::resumeTournament(unique_ptr<Round> loadedRound) {
    // set the current round number by adding amount of rounds won by both players + 1
    int roundsWonByPlayer1 = loadedRound->getPlayer1()->getRoundsWon();
    int roundsWonByPlayer2 = loadedRound->getPlayer2()->getRoundsWon();
    currentRoundNumber = roundsWonByPlayer1 + roundsWonByPlayer2 + 1;

    // Display current tournament state
    cout << "Resuming Tournament at Round " << currentRoundNumber << "." << endl;
    loadedRound->getGameBoard().showBoard();
    //indicate whose turn it is 
    cout << "It's " << loadedRound->getCurrentPlayer()->getName() << "'s turn." << endl;
    //display amount of rounds per player
    cout << "Human Rounds Won: " << roundsWonByPlayer1 << ", Score: " << loadedRound->getPlayer1()->getScore() << endl;
    cout << "Computer Rounds Won: " << roundsWonByPlayer2 << ", Score: " << loadedRound->getPlayer2()->getScore() << endl;
    //resume round
    loadedRound->continueRound();
   

    // ask if another round would like to be played **NOT CURRENTLY WORKING
    if (askToContinue()) {
        playNextRound();
    }
}


