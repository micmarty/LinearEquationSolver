#include "GameState.h"
#include<iostream>
#include <algorithm>

using namespace std;

vector<int> GameState::gameBoard(N + 6, 1);
vector<GameState*> GameState::queue;

GameState::GameState(int g, int a, int b)
{
	this->g = g;
	this->a = a;
	this->b = b;

	c = 0;//intercept equals 0 at the beggining
				//further some fractions will be added to that variable
	positionInQueue = queue.size();
}

bool GameState::elementFound(GameState* neededElement)
{
	for (int i = 0; i < GameState::queue.size(); i++){
		if (*GameState::queue[i] == *neededElement)
			return true;
	}
	return false;
}

GameState::~GameState()
{
	//nothing to deallocate
}

bool GameState::operator==(const GameState &r)
{
	bool equalPlayers = (g == r.g);
	bool equalA = (a == r.a);
	bool equalB = (b == r.b);
	if (equalPlayers && equalA && equalB)
		return true;
	else
		return false;
}

void GameState::fillQueue()
{
 	printf("x(%d, %d, %d) = ", g, a, b);
	int e = g == 1 ? 2 : 1;			//e - enemy

	//testing dice rolling result
	for (int d = 1; d <= 6; d++)	//d - dice roll result
	{
		if (g == 1)
		{
			if (gameBoard[a + d] != END_OF_BOARD)
			{
				int penalty = gameBoard[a + d] < 0 ? gameBoard[a + d] : 0;
				GameState* unknownState = new GameState(e, a + d + penalty, b);

				//if no identical unknown game state is found, then add it to our queue
				if (!elementFound(unknownState))
					queue.push_back(unknownState);

				printf("1/6*(%d, %d, %d) + ", e, a + d + penalty, b);
			}//else - if player 'g' is out of board, he WINS
			else
			{	
				c += (1 / 6.0);	
			}
		}
		if (g == 2)
		{
			if (gameBoard[b + d] != END_OF_BOARD)
			{
				int penalty = gameBoard[b + d] < 0 ? gameBoard[b + d] : 0;
				GameState* unknownState = new GameState(e, a, b + d + penalty);

				//if no identical unknown game state is found, then add it to our queue
				if (!elementFound(unknownState))
					queue.push_back(unknownState);

				printf("1/6*(%d, %d, %d) + ", e, a, b + d + penalty);
			}//else - if player 'g' is out of board, he WINS
			else
			{
				c += 0;	//0 means that player nr 1 defeated
			}
			
		}
		

	}
	cout << c << endl;
	//cout << "\b\b\b\033[K" << endl;//deletes excessive ' + 'sign
}

void GameState::fillEquation()
{
	for (int i = 0; i < queue.size(); i++){
		if (i < positionInQueue)		//fill equation with 0 until proper position is reached
			equation.push_back(0);
		if (i == positionInQueue)		//if proper position, put 1 in here
			equation.push_back(1);
		else if (i > positionInQueue)	//every further element is substracted from 1
			equation.push_back(-1 / 6.0);
	}//all factors are pushed now
	
	equation.push_back(c);				//now add an intercept at the end


	//display row in matrix for that state
	cout << endl << endl<< "equation like 1  -x  -y  -z = intercept" << endl;
	for (int i = 0; i < equation.size(); i++)
		cout << equation[i] << " ";
}