#pragma once
#ifndef GAME_H
#define GAME_H
#define PLAYER_h
#include "Player.h"
#include <iostream>

using namespace std;

class Game {
private:
	Player p1;
	Player p2;
	Player currrentPlayerTurn;
public:
	Game(Player p1, Player p2);
	void coinToss();
	void switchTurn();
};
#endif // !GAME_H
