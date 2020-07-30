/*
 * Data Structures and Algorithms
 * 15-04-2019
 * Assignment 1
 * ID:	1875 1084
 * Action.h
 *
 * This class stores the values of actions used to manipulate the board in order to find
 * a best move situation.
 *
 */

#ifndef ACTION_H_
#define ACTION_H_

struct Action {
	int src;
	int dest;
	double heuristic;

	Action(int s, int d, double h) :
			src(s), dest(d), heuristic(h) {
	}

	bool operator<(const Action &a) const {
		return heuristic < a.heuristic;
	}

	 bool operator==(const Action &a) const {
		 return src == a.src;
	 }

	void printAction() {
		cout << "Src: " << src << ", Dest: " << dest << endl;
	}

	int getSrc() {
		return src;
	}

	int getDest() {
		return dest;
	}

	int getHeuristic() {
		return heuristic;
	}

	void setAction(int s, int d) {
		src = s;
		dest = d;
	}

	void setHeuristic(double h) {
		heuristic = h;
	}

};

#endif /* ACTION_H_ */
