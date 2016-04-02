#include "GameState.h"
#include<iostream>
#include <algorithm>
#include<iomanip>

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
	variablesUsed = 0;
}

bool GameState::elementFound(GameState* neededElement,int foundAt)
{
	for (int i = 0; i < GameState::queue.size(); i++){
		if (*GameState::queue[i] == *neededElement && i == foundAt){
			return true;
		}
			
	}
	return false;
}

bool GameState::elementFound(GameState* neededElement)
{
	for (int i = 0; i < GameState::queue.size(); i++){
		if (*GameState::queue[i] == *neededElement){
			return true;
		}

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
 	//printf("x(%d, %d, %d) = ", g, a, b);
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
				{
					queue.push_back(unknownState);
					
				}
				generetedStates.push_back(unknownState);
				variablesUsed++;
				//printf("1/6*(%d, %d, %d) + ", e, a + d + penalty, b);
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
				{
					queue.push_back(unknownState);
					
					
				}
				generetedStates.push_back(unknownState); 
				variablesUsed++;
				//printf("1/6*(%d, %d, %d) + ", e, a, b + d + penalty);
			}//else - if player 'g' is out of board, he WINS
			else
			{
				c += 0;	//0 means that player nr 1 defeated
			}
			
		}
		

	}
	//cout << c << endl;
	//cout << "\b\b\b\033[K" << endl;//deletes excessive ' + 'sign
	//cout << variablesUsed << endl;
}

void GameState::fillEquation()
{
	for (int i = 0; i < 8; i++)
	{
		//if proper position, put '1' in here (executes only once)
		if (i == positionInQueue)		
			equation.push_back(1);

		//action for filling elements to the left and to the right from positionInQueue
		//only if its a unknown variable(not an intercept)
		else if (i != positionInQueue && variablesUsed > 0)
		{
			int notFound = 0;	//how many misses during lookup 

			for (int g_i = 0; g_i < generetedStates.size(); g_i++)
			{
				if (g == 2 && a == 2 && b == 1)
					int a = 1;
				if (elementFound(generetedStates[g_i],i))
				{
					equation.push_back(-1 / 6.0);	//every further element is substracted from 1
					variablesUsed--;
					break;
				}
				notFound++;
			}
			if (notFound == generetedStates.size()){
				equation.push_back(0);
			}

		}
		else
			equation.push_back(0);
		//all factors are pushed now
	}
	equation.push_back(c);				//now add an intercept at the end
	//display row in matrix for that state
	//cout << endl << endl<< "equation like 1  -x  -y  -z = intercept" << endl;
	for (int i = 0; i < equation.size(); i++)
		cout << " " << setprecision(2) << setw(8) << equation[i];
	cout << endl << endl;
}