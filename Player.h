#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <utility>
using namespace std;

class Player {
protected:
    string playerName; //user name
    std::pair<char, int> piece; //piece selection
    std::pair<char, int> destination; // desired move spot
    char pieceType; // B or W

public:
    Player() = default; // default cons
    //initialize a player name 
    explicit Player(const std::string& name) : playerName(name) {}
    //destructor
    virtual ~Player() {} 
    // getting input from player
    virtual void askPlayer() = 0; 
    // select a piece on the board
    virtual void selectPiece(char row, int col) = 0; 
    //set desired location
    virtual void setDestination(char row, int col) = 0;
    //retrieve selected piece
    virtual pair<char, int> getSelectedPiece() const = 0;
    //retrieve chosen destination
    virtual pair<char, int> getDestination() const = 0;
    // trying to convert to a chess like format ( want to accept moves as A6)
    virtual string properNotation(std::pair<int, int> position) const = 0;
    //set the player name 
    //retrieve name 
    string getName() const { return playerName; }
    // setting color piece for player 
    void setPieceType(char type) { pieceType = type; };
    // retrieve piece color 
    char getPieceType() const { return pieceType; }
};

#endif


