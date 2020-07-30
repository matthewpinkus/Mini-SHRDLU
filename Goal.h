/*
 * Data Structures and Algorithms
 * 15-04-2019
 * Assignment 1
 * ID:	1875 1084
 * Goal.h
 *
 * This class holds the values of all user desired goal positions
 *
 */


#ifndef GOAL_H_
#define GOAL_H_

class Goal {
private:
	int val;
	int row;
	int col;
public:
	bool operator<(const Goal g) const {
		if (row > g.row || (row == g.row && col > g.col)
				|| (row == g.row && col == g.col && val > g.val)) {
			return false;
		} else {
			return true;
		}
	}
	Goal() {

	}

	Goal(int v, int r, int c) :
			val(v), row(r), col(c) {
	}

	void setGoal(int v, int r, int c) {
		val = v;
		row = r;
		col = c;
	}

	void printGoal() const {
		cout << "(" << val << ", " << row << ", " << col << ")" << endl;
	}

	int getVal() {
		return val;
	}

	int getRow() {
		return row;
	}

	int getCol() {
		return col;
	}

};

#endif /* GOAL_H_ */
