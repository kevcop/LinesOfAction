#include "HumanPlayer.h"
#include <iostream>
using namespace std;

/**
 * Function Name: HumanPlayer
 * Purpose: Constructor for creating a HumanPlayer with a given name.
 * Parameters:
 *     name, a string. The name of the human player.
 * Return Value: None
 * Algorithm: Assign the provided name to the playerName member variable.
 * Reference: None
 */
HumanPlayer::HumanPlayer(const string& name) : Player(name) {}

/**
 * Function Name: askPlayer
 * Purpose: Prompts the user to enter their name and stores it.
 * Parameters: None
 * Return Value: None
 * Algorithm:
 *     1. Prompt the user with "Enter your name: ".
 *     2. Read the input name into the playerName variable.
 * Reference: None
 */
void HumanPlayer::askPlayer() {
    //prompt for a name
    cout << "Enter your name: ";
    cin >> playerName;
}
/**
 * Function Name: selectPiece
 * Purpose: Records the player's chosen piece to move.
 * Parameters:
 *     row, a char. The row part of the piece's location.
 *     col, an int. The column part of the piece's location.
 * Return Value: None
 * Algorithm: Store the row and column as a pair in the piece member variable.
 * Reference: None
 */
void HumanPlayer::selectPiece(char row, int col) {
    //setting initial position for move
    piece = make_pair(row, col);
}

/**
 * Function Name: setDestination
 * Purpose: Sets the desired destination for the selected piece.
 * Parameters:
 *     row, a char. The row part of the destination.
 *     col, an int. The column part of the destination.
 * Return Value: None
 * Algorithm: Store the row and column as a pair in the destination member variable.
 * Reference: None
 */
void HumanPlayer::setDestination(char row, int col) {
    //setting destination of move
    destination = make_pair(row, col);
}


/**
 * Function Name: getSelectedPiece
 * Purpose: Retrieves the player's selected piece.
 * Parameters: None
 * Return Value: A pair of char and int representing the selected piece's location.
 * Algorithm: Return the piece member variable.
 * Reference: None
 */
pair<char, int> HumanPlayer::getSelectedPiece() const {
    //return the requested piece 
    return piece;
}

/**
 * Function Name: getDestination
 * Purpose: Retrieves the desired destination for the move.
 * Parameters: None
 * Return Value: A pair of char and int representing the move's destination.
 * Algorithm: Return the destination member variable.
 * Reference: None
 */
pair<char, int> HumanPlayer::getDestination() const {
    //return desired destination
    return destination;
}
/**
 * Function Name: properNotation
 * Purpose: Converts board position to a string in chess notation.
 * Parameters:
 *     position, a pair<int, int>. The position on the board to convert.
 * Return Value: A string representing the position in chess notation.
 * Algorithm:
 *     1. Convert the column index to a character starting from 'A'.
 *     2. Add 1 to the row index and convert it to a string.
 *     3. Concatenate the column letter and row number into a single string.
 * Reference: None
 */
string HumanPlayer::properNotation(pair<int, int> position) const {
    // Convert column index to a character starting from 'A' and row index to a 1-based value
    return string(1, static_cast<char>('A' + position.first)) + to_string(position.second + 1);
}

//char and int were chosen to better represent a chess like style. Rows are denoted by letters and columns are denoted by numbers
//proper notation function will transform these values into the desired ones.