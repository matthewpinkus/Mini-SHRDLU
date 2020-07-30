/*
 * Data Structures and Algorithms
 * 15-04-2019
 * Assignment 1
 * ID:	1875 1084
 * State.h
 *
 * This class handles the state of the board.
 * All functions relating to manipulating data is stored here
 *
 */

#ifndef STATE_H_
#define STATE_H_

#include "Action.h"
#include "Goal.h"
class State {
private:
	int BOARDSIZE;
	int NUMBER_OF_PLACES;
	int NUMBER_OF_BLOCKS;
public:
	vector<vector<int>> vec;
	bool operator==(State s) {
		for (int i = 0; i < BOARDSIZE; i++)
			for (int j = 0; j < BOARDSIZE; j++)
				if (s.vec[i][j] != vec[i][j])
					return false;
		return true;
	}

	bool operator!=(State s) {
		for (int i = 0; i < BOARDSIZE; i++)
			for (int j = 0; j < BOARDSIZE; j++)
				if (s.vec[i][j] != vec[i][j])
					return true;
		return false;
	}

	State();

	// Initializing user specified boardsize values
	State(int bSize) {
		BOARDSIZE = bSize;
		NUMBER_OF_PLACES = BOARDSIZE * BOARDSIZE;
		NUMBER_OF_BLOCKS = (BOARDSIZE * BOARDSIZE) - BOARDSIZE;
		generateState();
		pushDown();
	}

	// Copy constructor
	State(const State &state) {
		BOARDSIZE = state.BOARDSIZE;
		NUMBER_OF_PLACES = BOARDSIZE * BOARDSIZE;
		NUMBER_OF_BLOCKS = (BOARDSIZE * BOARDSIZE) - BOARDSIZE;
		vec.resize(BOARDSIZE, vector<int>(BOARDSIZE, 0));
		for (int i = 0; i < BOARDSIZE; i++)
			for (int j = 0; j < BOARDSIZE; j++)
				vec[i][j] = state.vec[i][j];
	}

	// Returns state if the action(src, dest, //heuristic) is a valid move
	State nextState(Action action) {
		State newState(*this);
		return newState;
	}

	int getRow(int row) {
		return row;
	}

	int getCol(int col) {
		return col;
	}

	int getBoardSize();
	// Returns users specified boardsize.

	void generateState();
	// Generates the initial state of the game

	bool checkState(int block, int row, int col);
	// Checks if the row and column has desired block value

	void printBoard() const;
	// Prints the board

	void pushDown();
	// Pushes all non zero numbers to bottom of board

	int removeBlockFrom(int col);
	// Removes block from top of specified column

	bool insertBlockTo(int col, int value);
	// Inserts value to specified column

	bool moveBlock(int src, int dest, priority_queue<Goal> &conjunctives);
	// Removes block from top of a column and replaces designated column with source block

	bool isOnTop(int val);
	// Returns true if value is on top of column

	int getColPos(int val);
	// Returns column position

	int getRowPos(int val);
	// Returns row position in vector of specified value

	int getTopColumnBlock(int col);
	// Returns value of block in specified column

	int getBlockValue(int row, int col);
	// Returns value of specified cell in vector
};

int State::getBoardSize() {
	return BOARDSIZE;
}

/* STATE OF BOARD FUNCTIONS */
void State::generateState() {
	/* List is used to store the placement of randomly generated locations to be removed
	 * as to not have any repeats  */
	list<int> listPlace;
	for (int i = 0; i < NUMBER_OF_PLACES; i++)
		listPlace.push_back(i);

	// Iterator for removing locations from list
	list<int>::iterator itr = listPlace.begin();

	// Filling the vector of vectors with 0
	vec.resize(BOARDSIZE, vector<int>(BOARDSIZE, 0));

	for (int i = 1, rng = 0; i < NUMBER_OF_BLOCKS + 1; i++) {
		// 'rng' is random location within list to place 'i' into vector
		rng = rand() % listPlace.size();
		advance(itr, rng);
		int row = *itr / BOARDSIZE;
		int col = *itr % BOARDSIZE;
		vec[row][col] = i;
		// Remove randomly selected location and point iterator to beginning of list
		listPlace.erase(itr);
		itr = listPlace.begin();
	}
}

bool State::checkState(int block, int row, int col) {
	if (vec[row][col] == block)
		return true;
	return false;
}

void State::printBoard() const {
	for (int i = 0; i < BOARDSIZE; i++) {
		cout << " ---" << setw(2);
	}
	for (int i = 0; i < BOARDSIZE; i++) {
		cout << "\n|" << setw(2);
		for (int j = 0; j < BOARDSIZE; j++) {
			if (vec[i][j] >= 100)
				cout << vec[i][j] << "|" << setw(2);
			else
				cout << vec[i][j] << " |" << setw(2);
		}
	}
	cout << endl;
	for (int i = 0; i < BOARDSIZE; i++) {
		cout << " ---" << setw(2);
	}
	cout << endl;

}

/* ACTIONS TO ALTER BOARD FUNCTIONS */

void State::pushDown() {
	stack<int> col;
	for (int row = 0; row < BOARDSIZE; row++) {
		for (int column = 0; column < BOARDSIZE; column++) {
			if (vec[column][row] != 0) { // Top down search for non zero numbers in column to add to stack
				col.push(vec[column][row]);
			}
		}

		for (int k = BOARDSIZE - 1; k >= 0; k--) { // Replacing column with arranged stack numbers from bottom up
			if (!col.empty()) {
				vec[k][row] = col.top();
				col.pop();
			} else
				vec[k][row] = 0;
		}
	}
}

int State::removeBlockFrom(int column) {
	for (int row = 0; row < BOARDSIZE; row++) {
		int block = vec[row][column];
		if (block != 0) {
			vec[row][column] = 0;
			return block;
		}
	}
	return -1;
}

bool State::insertBlockTo(int column, int value) {
	for (int row = 0; row < BOARDSIZE; row++) {
		int val = vec[BOARDSIZE - row - 1][column];
		if (val == 0) {
			vec[BOARDSIZE - row - 1][column] = value;
			return true;
		}
	}
	return false;
}

bool State::moveBlock(int src, int dest, priority_queue<Goal> &conjunctives) {
	Goal g = conjunctives.top();
	for (unsigned int i = 0; i < conjunctives.size(); i++) {
		if (vec[g.getRow()][g.getCol()] == g.getVal()){
			return false;
		}
	}

	if (vec[0][dest] != 0) {
		return false;
	}

	if (src == dest) {
		return false;
	}

	int block = removeBlockFrom(src);
	return insertBlockTo(dest, block);
}

bool State::isOnTop(int val) {
	for (int row = BOARDSIZE - 1; row >= 0; row--) {
		for (int col = BOARDSIZE - 1; col >= 0; col--) {
			int block = vec[row][col];
			if (block == val && vec[row - 1][col] <= 0) {
				cout << "Column Full, program thinks block on top"
						<< vec[0][col] << endl;
				return true;
			}
		}
	}
	return false;
}

int State::getTopColumnBlock(int col) {
	for (int row = 0; row < BOARDSIZE; row++) {
		int block = vec[row][col];
		if (block != 0) {
			return block;
		}
	}
	return -1;
}

int State::getColPos(int val) {
	for (int row = 0; row < BOARDSIZE; row++)
		for (int col = 0; col < BOARDSIZE; col++)
			if (vec[row][col] == val)
				return col;
	return -1;
}

int State::getRowPos(int val) {
	for (int row = 0; row < BOARDSIZE; row++)
		for (int col = 0; col < BOARDSIZE; col++)
			if (vec[row][col] == val)
				return row;
	return -1;
}

int State::getBlockValue(int row, int col) {
	return vec[row][col];
}

#endif /* STATE_H_ */
