#pragma once
#include "Player.h"
#include <string>

class HumanPlayer :public Player {
public:
    HumanPlayer() = default;
    explicit HumanPlayer(const string& name);

    void askPlayer() override;
    void selectPiece(char row, int col) override;
    void setDestination(char row, int col) override;
    std::pair<char, int> getSelectedPiece() const override;
    std::pair<char, int> getDestination() const override;
    std::string properNotation(std::pair<int, int> position) const override;
};