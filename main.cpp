// main.cpp

#include <iostream>
#include <cstdlib>
#include <time.h>
#include "header.h"

using namespace std;

int main() {
	
	cout << "Tic Tac Toe v1.1\n";
	cout << "By Sophie Garrett\n";
	cout << endl;
	
	// Go to the main menu.
	menu();
	
	return 0;
}

void menu() {
	
	int players;
	int difficulty = 0;
	
	// Find out how many people are playing.
	cout << "How many players? ";
	cin >> players;
	
	// There cannot be less than 1 or more than 2 players.
	while (players != 1 && players != 2) {
		cout << "Invalid number of players. Please enter 1 or 2.\n";
		cout << "How many players? ";
		cin >> players;
	}
	
	// If there is one player, ask the user whether they want Easy or Hard difficulty.
	if (players == 1) {
		cout << "Enter 1 for easy difficulty or 2 for hard: ";
		cin >> difficulty;
	
		// Make sure that the user's difficulty selection is valid.
		while (difficulty != 1 && difficulty != 2) {
			cout << "Invalid difficulty. Please enter 1 or 2: ";
			cin >> difficulty;
		}
	}
	
	// Define and initialize an object of class Game.
	Game G;
	G.initialize(players, difficulty);
	
	// Start the game.
	G.startGame();
	
	// Return to the menu after a game or after an error message.
	menu();

}
