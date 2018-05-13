#pragma once

enum Game { Blackjack = 1, Craps };

int mainMenu();
Game gameSelectionMenu();
void showStatus();
void startGame();
Game gameSelection = Blackjack;
int money = 100;
int turns = 1;