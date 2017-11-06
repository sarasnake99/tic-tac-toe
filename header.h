// header.h

void menu();

class Game {
	
	private:
		int p, d, currentPlayer, turns, winner;
		bool gameover, moveChosen;
		char array[3][3];
	
	public:
		void initialize(int players, int difficulty);
		void startGame();
		void showBoard();
		void userTurn();
		void cpuTurn();
		void chooseMove(char c, int &y, int &x);
		void isGameOver();
	
};
