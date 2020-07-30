/*
 * Data Structures and Algorithms
 * 15-04-2019
 * Assignment 1
 * ID:	1875 1084
 * HumanInput.h
 *
 *  This class receives information from the user: Block to move, desired row/column positions
 *
 */

#ifndef HUMANINPUT_H_
#define HUMANINPUT_H_

class HumanInput {
private:
	int BOARDSIZE;
	int NUMBER_OF_BLOCKS;
public:
	HumanInput() {

	}

	HumanInput(int bSize) {
		BOARDSIZE = bSize;
		NUMBER_OF_BLOCKS = (BOARDSIZE * BOARDSIZE) - BOARDSIZE;
	}
	void getGoals(priority_queue<Goal> &target_goals);
	// Receives input from user.

	bool isValidInput(int &block, int &row, int &column);
	// Checks that user has entered correct parameters
};

void HumanInput::getGoals(priority_queue<Goal> &target_goals) {
	vector<int> goals;
	list<int> targets;

	// Initialising which blocks can be chosen
	for (int i = 1; i <= NUMBER_OF_BLOCKS; i++)
		targets.push_back(i);




	int block, row, col;
	bool recurringBlock;
	char ans;
	do {
		do {
			cout << "Enter block value, 1 - " << NUMBER_OF_BLOCKS << ": ";
			cin >> block;
			cout << "\nEnter a row: ";
			cin >> row;
			cout << "\nEnter a column: ";
			cin >> col;
			for (unsigned int i = 0; i < goals.size(); i++) {
				if (goals[i] == block) {
					cout << "\nA goal of this block has already been added"
							<< endl;
					recurringBlock = true;
				} else
					recurringBlock = false;
			}
		} while (!isValidInput(block, row, col) || recurringBlock);

		goals.push_back(block);
		targets.remove(block);

		Goal g;
		g.setGoal(block, row, col);
		target_goals.push(g);
		cout << "\nAdded Goal: Block " << block << " to row " << row
				<< ", column " << col;
		cout << "\nY to enter another goal: ";
		cin >> ans;
		cout << endl;
	} while (ans == 'y' || ans == 'Y');

	return;
}


bool HumanInput::isValidInput(int &block, int &row, int &col) {
	// Making sure block, row, and col are within the bounds of the boardsize.
	if (0 < block && block <= NUMBER_OF_BLOCKS && 0 <= row
			&& row <= BOARDSIZE - 1 && 0 <= col && col <= BOARDSIZE - 1)
		return true;
	return false;
}
#endif /* HUMANINPUT_H_ */
