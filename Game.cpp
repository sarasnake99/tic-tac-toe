// Game.cpp

#include <iostream>
#include <cstdlib>
#include <time.h>
#include "header.h"

using namespace std;

// Start the game.
void Game::startGame() {
	
	// Use a while loop to keep playing until the game is over.
	while (gameover == false) {
		
		// Display the board.
		showBoard();
		
		// Check whether the game is singleplayer or multiplayer.
		if (p == 1) {
			// If it is the user's turn, call the userTurn function.
			if (currentPlayer == 1)
				userTurn();
			// If it is the computer's turn, call the cpuTurn function.
			else
				cpuTurn();
		}
		
		else {
			// If the game is multiplayer, have the current user take a turn.
			userTurn();
		}
		
		// Switch which player's turn it is.
		if (currentPlayer == 1)
			currentPlayer = 2;
		else
			currentPlayer = 1;
		
		// Update the number of turns that have passed.
		turns += 1;
		
		// Check whether or not the game is over.
		isGameOver();
	}
	
	// Display the board one last time.
	showBoard();
	
	// Display a game-over message.
	cout << "Game over.\n";
	
	// Display the winner.
	if (winner == 0)
		cout << "The game ended in a draw!\n";
	else if (p == 1 && winner == 1)
		cout << "You won! Congratulations!\n";
	else if (p == 2 && winner == 1)
		cout << "The winner is Player 1!\n";
	else if (p == 1 && winner == 2)
		cout << "The computer won. Try again!\n";
	else
		cout << "The winner is Player 2!\n";
	
	cout << endl;
	
}

// Function for initializing the game
void Game::initialize(int players, int difficulty) {
	p = players;
	d = difficulty;
	currentPlayer = 1;
	turns = 0;
	winner = 0;
	gameover = false;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			array[i][j] = ' ';
		}
	}
}

// Function for displaying the tic-tac-toe board
void Game::showBoard() {
	cout << endl;
	cout << " " << array[0][0] << " | " << array[0][1] << " | " << array[0][2] << endl;
	cout << "---|---|---" << endl;
	cout << " " << array[1][0] << " | " << array[1][1] << " | " << array[1][2] << endl;
	cout << "---|---|---" << endl;
	cout << " " << array[2][0] << " | " << array[2][1] << " | " << array[2][2] << endl;
	cout << endl;
}

// Function for a user's turn
void Game::userTurn() {
	
	// Declare integers for user-entered coordinates.
	int y, x;
	
	// State which player's turn it is.
	cout << "It is now player " << currentPlayer << "'s turn.\n";
	
	cout << endl;
	
	cout << "Where would you like to place your piece?\n";
	cout << "Enter a y-coordinate and an x-coordinate, separated by a space.\n";
	cout << "Note: 0 0 is in the upper-left corner.\n";
	cin >> y >> x;
	
	// Check whether or not the user's input is valid.
	while (y < 0 || y > 2 || x < 0 || x > 2) {
		cout << "Invalid space! Please choose another: ";
		cin >> y >> x;
	}
	
	// Check whether or not the space is already occupied.
	while (array[y][x] != ' ') {
		cout << "That space is already taken! Please choose another: ";
		cin >> y >> x;
	}
	
	// If the space is clear, change the array's value to the user's symbol.
	if (currentPlayer == 1)
		array[y][x] = 'x';
	else
		array[y][x] = 'o';
	
}

// Function for the computer's turn
void Game::cpuTurn() {
	
	// Declare integers for the move's coordinates.
	int y, x;
	
	// State that it is the computer's turn.
	cout << "It is now the computer's turn.\n";
	
	cout << endl;
	
	// If the difficulty is set to Easy, have the computer randomly generate a move.
	if (d == 1) {
		
		srand(time(0));
		y = rand() % 3;
		x = rand() % 3;
		
		// Check whether or not the space is occupied.
		while (array[y][x] != ' ') {
			y = rand() % 3;
			x = rand() % 3;
		}
	}
	
	// If the difficulty is set to Hard, have the computer decide a move strategically.
	else {
		
		// Set moveChosen to false, if it isn't already.
		moveChosen = false;
		
		// First, check whether or not the computer can win within one move.
		// If the computer occupies two spaces in a row anywhere on the board,
		// it should attempt to take the final space.
		
		// Call the chooseMove function.
		chooseMove('o', y, x);
		
		// If the computer cannot win on this turn, it should check whether or not
		// the player is about to win. If they are about to win, then the
		// computer should stop them from winning. This is a very similar
		// process to the process used to find out whether or not
		// the computer can win on its next turn.
		if (moveChosen == false)
			chooseMove('x', y, x);
		
		// If a move hasn't been chosen, check if the middle space is empty; if it is,
		// take it.
		if (moveChosen == false) {
			if (array[1][1] == ' ') {
				moveChosen = true;
				y = 1;
				x = 1;
			}
		}
		
		// There is a very specific circumstance that needs an extra bit of code to handle.
		if (moveChosen == false) {
			if (turns == 3 && array[1][1] == 'o') {
				if (array[0][0] == 'x' && array[2][2] == 'x') {
					moveChosen = true;
					y = 0;
					x = 1;
				}
				else if (array[2][0] == 'x' && array[0][2] == 'x') {
					moveChosen = true;
					y = 0;
					x = 1;
				}
			}
		}
		
		// If a move hasn't been chosen, check if the corners are empty; if a corner
		// is empty, take it.
		if (moveChosen == false) {
			if (array[0][0] == ' ') {
				moveChosen = true;
				y = 0;
				x = 0;
			}
			else if (array[0][2] == ' ') {
				moveChosen = true;
				y = 0;
				x = 2;
			}
			else if (array[2][0] == ' ') {
				moveChosen = true;
				y = 2;
				x = 0;
			}
			else if (array[2][2] == ' ') {
				moveChosen = true;
				y = 2;
				x = 2;
			}
		}
			
		// If a move still hasn't been chosen, the computer should randomly choose a move.
		if (moveChosen == false) {
			srand(time(0));
			y = rand() % 3;
			x = rand() % 3;
		
			// Check whether or not the space is occupied.
			while (array[y][x] != ' ') {
				y = rand() % 3;
				x = rand() % 3;
			}
		}
	}
	
	// Change the chosen space's value to the computer's symbol.
	array[y][x] = 'o';
	
}

// Function for choosing a move
void Game::chooseMove(char c, int &y, int &x) {
	
	// This function checks whether or not either player is able to win
	// on their next move. It then sets the computer's move to the space
	// that would complete the three-in-a-row line. Since this function is
	// very similar for checking whether the computer can win and checking
	// whether the player can win, I decided to make it a function
	// so that I don't have to write the same thing twice.
		
	// First, check the rows.
	for (int i = 0; i < 3; i++) {
		if (array[i][0] == c && array[i][1] == c && array[i][2] == ' ') {
			moveChosen = true;
			y = i;
			x = 2;
		}
		else if (array[i][1] == c && array[i][2] == c && array[i][0] == ' ') {
			moveChosen = true;
			y = i;
			x = 0;
		}
		else if (array[i][0] == c && array[i][2] == c && array[i][1] == ' ') {
			moveChosen = true;
			y = i;
			x = 1;
		}
	}
	
	// Next, check the columns.
	for (int i = 0; i < 3; i++) {
		if (array[0][i] == c && array[1][i] == c && array[2][i] == ' ') {
			moveChosen = true;
			y = 2;
			x = i;
		}
		else if (array[1][i] == c && array[2][i] == c && array[0][i] == ' ') {
			moveChosen = true;
			y = 0;
			x = i;
		}
		else if (array[0][i] == c && array[2][i] == c && array[1][i] == ' ') {
			moveChosen = true;
			y = 1;
			x = i;
		}
	}
	
	// Finally, check the diagonals.
	if (array[0][0] == c && array[1][1] == c && array[2][2] == ' ') {
		moveChosen = true;
		y = 2;
		x = 2;
	}
	else if (array[1][1] == c && array[2][2] == c && array[0][0] == ' ') {
		moveChosen = true;
		y = 0;
		x = 0;
	}
	else if (array[0][0] == c && array[2][2] == c && array[1][1] == ' ') {
		moveChosen = true;
		y = 1;
		x = 1;
	}
	else if (array[0][2] == c && array[1][1] == c && array[2][0] == ' ') {
		moveChosen = true;
		y = 2;
		x = 0;
	}
	else if (array[1][1] == c && array[2][0] == c && array[0][2] == ' ') {
		moveChosen = true;
		y = 0;
		x = 2;
	}
	else if (array[0][2] == c && array[2][0] == c && array[1][1] == ' ') {
		moveChosen = true;
		y = 1;
		x = 1;
	}		
}

// Function for determining whether or not the game is over
void Game::isGameOver() {
	
	// The game cannot be over if less than 5 turns have passed.
	if (turns < 5)
		gameover = false;
	
	// If between 5 and 9 turns have passed, then the game may or may not be over.
	if (turns >= 5 && turns <= 9) {
		// The game is over when either player has three pieces in a row. Put another way,
		// this means that the game is over when either player occupies an entire row,
		// column, or diagonal.
		
		// First, check the rows.
		for (int i = 0; i < 3; i++) {
			if (array[i][0] == 'x' && array[i][1] == 'x' && array[i][2] == 'x') {
				gameover = true;
				winner = 1;
			}
			else if (array[i][0] == 'o' && array[i][1] == 'o' && array[i][2] == 'o') {
				gameover = true;
				winner = 2;
			}
		}
		
		// Next, check the columns.
		for (int i = 0; i < 3; i++) {
			if (array[0][i] == 'x' && array[1][i] == 'x' && array[2][i] == 'x') {
				gameover = true;
				winner = 1;
			}
			else if (array[0][i] == 'o' && array[1][i] == 'o' && array[2][i] == 'o') {
				gameover = true;
				winner = 2;
			}
		}
		
		// Finally, check the diagonals.
		if (array[0][0] == 'x' && array[1][1] == 'x' && array[2][2] == 'x') {
			gameover = true;
			winner = 1;
		}
		else if (array[0][0] == 'o' && array[1][1] == 'o' && array[2][2] == 'o') {
			gameover = true;
			winner = 2;
		}
		else if (array[0][2] == 'x' && array[1][1] == 'x' && array[2][0] == 'x') {
			gameover = true;
			winner = 1;
		}
		else if (array[0][2] == 'o' && array[1][1] == 'o' && array[2][0] == 'o') {
			gameover = true;
			winner = 2;
		}
		
	}
	
	// The game is automatically over when 9 turns have passed, since there are only 9 squares.
	// All winner checks have already been completed, so if the game reaches this point
	// without a winner having been decided, then there must be no winner.
	if (turns >= 9)
		gameover = true;
		
}
