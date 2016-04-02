#include "GameState.h"
#include<iostream>
using namespace std;

vector<int> GameState::gameBoard(N + 6, 1);
vector<GameState> GameState::queue;

GameState::GameState(int g, int a, int b)
{
	this->g = g;
	this->a = a;
	this->b = b;

	c = 0;//intercept equals 0 at the beggining
				//further some fractions will be added to that variable
	
	fillEquation();
}

GameState::~GameState()
{
	//nothing to deallocate
}

bool operator==(const GameState& l, const GameState& r)
{
	bool equalPlayers = (l.g == r.g);
	bool equalA = (l.a == r.a);
	bool equalB = (l.b == r.b);
	if (equalPlayers && equalA && equalB)
		return true;
	else
		return false;
}

void GameState::fillEquation()
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
				GameState unknownState = GameState(e, a + d + penalty, b);

				//if no identical unknown game state is found, then add it to our queue
				if (find(queue.begin(), queue.end(), unknownState) == queue.end())
					queue.push_back(unknownState);

				printf("1/6*(%d, %d, %d) + ", e, a + d + penalty, b);
			}//else - if player 'g' is out of board, he WINS
			else
			{	
				c += 1 / 6;			//
				printf("1/6 + ");	//1 means that player nr 1 won
			}
		}
		if (g == 2)
		{
			if (gameBoard[b + d] != END_OF_BOARD)
			{
				int penalty = gameBoard[b + d] < 0 ? gameBoard[b + d] : 0;
				GameState unknownState = GameState(e, a, b + d + penalty);

				//if no identical unknown game state is found, then add it to our queue
				if (find(queue.begin(), queue.end(), unknownState) == queue.end())
					queue.push_back(unknownState);

				printf("1/6*(%d, %d, %d) + ", e, a, b + d + penalty);
			}//else - if player 'g' is out of board, he WINS
			else
			{
				c += 0;
				printf("0/6 + ");//0 means that player nr 1 defeated
			}
		}

	}
	cout << "\b\b\b\033[K" << endl;//deletes excessive ' + 'sign
}