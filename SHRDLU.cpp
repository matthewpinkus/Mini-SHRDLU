/*
 * Data Structures and Algorithms
 * 15-04-2019
 * Assignment 1
 * SHRDLU.cpp
 *
 * Main file for Mini-SHRDLU.
 *
 */

#include <stack>
#include <list>
#include <vector>
#include <queue>
#include <iterator>
#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <iomanip>

using namespace std;

#include "State.h"
#include "Solver.h"
#include "HumanInput.h"
#include "Action.h"
#include "Game.h"
#include "Goal.h"

int main() {
	Game game;
	game.play();
	return 0;
}
