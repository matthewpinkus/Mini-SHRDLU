/*
 * Data Structures and Algorithms
 * 15-04-2019
 * Assignment 1
 * Game.h
 *
 * This class receives user input board size, initialises the board with desired size, and calls
 * to HumanInput.h for user desired values. This information is passed to the Solver class to find a goal state.
 *
 */

#ifndef GAME_H_
#define GAME_H_
#include "Goal.h"

class Game {
private:
	Solver solve;
public:
	void play();
	void getHumanInput(Goal g);
};

void Game::play() {
	Goal goals;
	getHumanInput(goals);
	cout << "\nEnd of program.";

}

void Game::getHumanInput(Goal g) {
	srand(time(0));
	priority_queue<Goal> target_goals;
	int boardSize;
	do {
		cout << "Enter a board size greater than 3: ";
		cin >> boardSize;
	} while (boardSize < 3);

	State *board = new State(boardSize);
	cout << "Board size set, initializing state and pushing down.\n";
	board->printBoard();

	HumanInput h = HumanInput(boardSize);

	h.getGoals(target_goals);

	solve.seekGoal(*board, g, target_goals);
}
#endif /* GAME_H_ */
