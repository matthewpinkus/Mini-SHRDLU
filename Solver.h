/*
 * Data Structures and Algorithms
 * 15-04-2019
 * Assignment 1
 * Solver.h
 *
 * This class obtains all legal actions in a given state, giving each action a heuristic value
 * to optimise the chosen action. Each state is recorded in a vector for use as a template of
 * non-winning states.
 *
 */

#ifndef SOLVER_H_
#define SOLVER_H_
#include "Goal.h"

class Solver {
private:
	bool isGoalState;
	int steps = 0;
public:
	vector<State> usedStates;
	// Vector for all previous states visited

	priority_queue<Action> getLegalActions(State *s, Goal g, priority_queue<Goal> &target_goals);
	// Queue for all legal actions with heuristic values

	int calculateHeuristic(State &state, Goal g, int src, int srcRow, int dest,
			int blockVal);
	// Calculates heuristic value of passed state

	bool seekGoal(State board, Goal g, priority_queue<Goal> &target_goals);
	// Searches for a goal state

};

bool Solver::seekGoal(State state, Goal g, priority_queue<Goal> &target_goals) {
	do {
		Goal g = target_goals.top();
		int goalVal = g.getVal();
		int goalRow = g.getRow();
		int goalCol = g.getCol();
		cout << "Attempting to find state: " << goalVal << " from " << goalRow << " to "
				<< goalCol << endl;
		do {
			if (state.checkState(goalVal, goalRow, goalCol)) {
				cout << "!!! GOAL ACHIEVED !!! \nSteps taken: " << steps << endl;
				target_goals.pop();
				break;
			}
			priority_queue < Action > temp = getLegalActions(&state, g, target_goals);
			Action action = temp.top();
			int src = action.getSrc();
			int dest = action.getDest();
			int blockVal = state.getTopColumnBlock(src);
			state = state.nextState(action);
			state.moveBlock(src, dest, target_goals);
			cout << "Best move: " << blockVal << " from " << src << " to "
					<< dest << " H: " << action.getHeuristic() << endl;
			state.printBoard();
			steps++;
		} while (steps < 100);
		if (steps > 100)
			cout << "Target not found." << endl;
		if (target_goals.size() == 0) {
			cout << "All goals have been satisfied!";
			return true;
		}
	} while (target_goals.size() > 0);

	return false;
}
// passing through target goals to get conjunctive conditions in moveBlock function
priority_queue<Action> Solver::getLegalActions(State *s, Goal g, priority_queue<Goal> &target_goals) {
	priority_queue < Action > legalActions;
	for (int src = 0; src < s->getBoardSize(); src++) {
		for (int dest = 0; dest < s->getBoardSize(); dest++) {
			State *temp = new State(*s);
			// Obtaining block values for precise heuristics
			int blockVal = temp->getTopColumnBlock(src);
			int srcRow = temp->getRowPos(blockVal);
			if (temp->moveBlock(src, dest, target_goals)) {
				int heuristic = calculateHeuristic(*temp, g, src, srcRow, dest,
						blockVal);
				Action action = Action(src, dest, heuristic);
				legalActions.push(action);
				usedStates.push_back(*temp);
			}
		}
	}
	return legalActions;
}

int Solver::calculateHeuristic(State &state, Goal g, int srcCol, int srcRow,
		int destCol, int blockVal) {
	// Checking against previous states
	for (unsigned int i = 0; i < usedStates.size(); i++)
		if (usedStates[i] == state)
			return 0;

	// VALUE OF GOAL BLOCK
	int goalVal = g.getVal();

	// VALUES OF GOAL ROW AND COLUMN
	int goalRow = g.getRow();
	int goalCol = g.getCol();

	// VALUES OF GOAL ROW AND COLUMN IN CURRENT STATE
	int currentGoalCol = state.getColPos(goalVal);
	int currentGoalRow = state.getRowPos(goalVal);

	// BOARDSIZE PARAMETER
	int bSize = state.getBoardSize();
	//	cout << "bSize: " << bSize << ", ";

	// ROW VALUE OF DESTINATION BLOCK
	int destRow = state.getRowPos(state.getTopColumnBlock(destCol));

	// Best possible outcome
	if (blockVal == goalVal && destRow == goalRow && destCol == goalCol)
		return 100;
	// Not handling goal block, is in goal position, goal block is on top of a column
	else if (blockVal != goalVal && srcRow == goalRow && srcCol == goalCol
			&& currentGoalRow == 0)
		return 95;
	// Puts goal block on top of a column which is not the goal column, if the goal is not at the top of a column
	else if (blockVal == goalVal && destRow == 0 && goalRow != 0
			&& destCol != goalCol)
		return 90;
	// Not handling goal block, is in goal position, moves to column where goal block isnt
	else if (blockVal != goalVal && srcRow == goalRow && srcCol == goalCol
			&& destCol != currentGoalCol)
		return 85;
	// Not handling goal block, top row is empty, goal block is in current column and destination is the goal column
	else if (blockVal != goalVal && srcRow != 0 && destRow == 0
			&& currentGoalCol == srcCol && destCol == goalCol)
		return 80;
	// Goal block is in goal column and not in right position and destination is top of column
	else if (blockVal == goalVal && currentGoalCol == srcCol && destRow == 0)
		return 75;
	// Not handling goal block, is in current goal column, moves to column where goal block isnt
	else if (blockVal != goalVal && srcCol == currentGoalCol
			&& destCol != currentGoalCol)
		return 70;
	// Not handling goal block, is in goal column and column is full
	else if (blockVal != goalVal && srcCol == goalCol && srcRow == 0)
		return 65;
	// Not handling goal block, is in goal column
	else if (blockVal != goalVal && srcCol == goalCol)
		return 60;
	// Goal block is in goal column and not in right position and destinaion isnt empty
	else if (blockVal == goalVal && currentGoalCol == goalCol
			&& destRow != bSize - 1)
		return 55;
	// Goal block is in goal column and not in right position
	else if (blockVal == goalVal && srcCol == goalCol)
		return 50;
	// Column is full
	else if (srcRow == 0)
		return 45;
	// Destination column is empty
	else if (destRow == bSize - 1)
		return 40;
	return 15;
}

#endif /* SOLVER_H_ */

