#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <utility>
using namespace std;

class Player {
protected:
    std::string playerName;
    char colorSelect;
    int turn;
    std::pair<char, int> piece;
    std::pair<char, int> destination;

public:
    Player() = default;
    explicit Player(const std::string& name) : playerName(name) {}
    virtual ~Player() {}

    virtual void askPlayer() = 0;
    virtual void selectPiece(char row, int col) = 0; // Made abstract (pure virtual)
    virtual void setDestination(char row, int col) = 0; // Corrected type and made abstract
    virtual std::pair<char, int> getSelectedPiece() const = 0;
    virtual std::pair<char, int> getDestination() const = 0;
    virtual std::string properNotation(std::pair<int, int> position) const = 0;

    void setPlayerName(const std::string& name) { playerName = name; }
    std::string getName() const { return playerName; }
    bool operator==(const Player& other) const {
        return playerName == other.playerName;
    }
};

#endif

 // !PLAYER_H

