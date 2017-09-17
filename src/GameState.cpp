#include "GameState.h"
#include<iostream>
#include <algorithm>
#include<iomanip>

using namespace std;

vector<int> GameState::gameBoard(N + 6, 1);
vector<GameState*> GameState::queue;

vector<double> GameState::getEquation()
{
	return equation;
}

GameState::GameState(int g, int a, int b)
{
	this->g = g;
	this->a = a;
	this->b = b;

	c = 0;//intercept equals 0 at the beggining
				//further some fractions will be added to that variable
	positionInQueue = queue.size();
	generatedStates.reserve(6);	//tyle maksymalnie niewiadomych moze wygenerowac jeden stan
	factors.assign(6, 0.0);
	variablesUsed = 0;
}

bool GameState::elementFound(GameState* neededElement,int atPos)
{
	if (*GameState::queue[atPos] == *neededElement){
		return true;
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

				//new state has always default probability 1/6
				factors[d - 1] = 1 / 6.0;

				//if unknowState isn't currently in queue
				if (!elementFound(unknownState))
				{
					queue.push_back(unknownState);
				}
				
				//make sure that if some state is repeated, increase its probability by 1/6
				//all is about that, for eaxample: 1/6*x(1,4,2) + 1/6*x(1,4,2) = 2/6*x(1,4,2);
				int notFound = 0;
				int current = 0;
				for (int placeInGeneratedStates = 0; placeInGeneratedStates < generatedStates.size(); placeInGeneratedStates++)
				{
					//if found the same state in generated vector, increase probability
					if (*generatedStates[placeInGeneratedStates] == *unknownState)
					{
						factors[placeInGeneratedStates] += (1 / 6.0);
						break;						//break to stop further searching
					}
					else{
						notFound++;					//count fail comparisons
					}
					current = placeInGeneratedStates;
				}
				//if no duplicates found, you can add it as new, unique state
				if (notFound == generatedStates.size())
				{
					generatedStates.push_back(unknownState);
					variablesUsed++;				//also increase variable counter which means how many variables our object has generated
				}
				//printf("%lf*(%d, %d, %d) + ",factors[current], e, a + d + penalty, b);
			}//else - if player 'g' is out of board, he WINS
			else
				c += (1 / 6.0);	
		}
		if (g == 2)
		{
			//all comments are the same as aboveeee ^^^^^^
			if (gameBoard[b + d] != END_OF_BOARD)
			{
				int penalty = gameBoard[b + d] < 0 ? gameBoard[b + d] : 0;
				GameState* unknownState = new GameState(e, a, b + d + penalty);

				factors[d - 1] = 1 / 6.0;

				if (!elementFound(unknownState))
				{
					queue.push_back(unknownState);
				}

				int notFound = 0;
				int current = 0;
				for (int placeInGeneratedStates = 0; placeInGeneratedStates < generatedStates.size(); placeInGeneratedStates++)
				{
					if (*generatedStates[placeInGeneratedStates] == *unknownState)
					{
						factors[placeInGeneratedStates] += (1 / 6.0);
						break;
					}
					else{
						notFound++;
					}
					current = placeInGeneratedStates;
				}
				if (notFound == generatedStates.size())
				{
					generatedStates.push_back(unknownState);
					variablesUsed++;
				}
			}//else - if player 'g' is out of board, he WINS
			else
				c += 0;	//0 means that player nr 1 defeated
		}
	}
	
	////commented displaying features, not useful now
	//cout << c << endl;
	//for (int i = 0; i <variablesUsed; i++)
		//cout << factors[i] << " ";
	//cout << "|" << endl;
	//cout << "\b\b\b\033[K" << endl;//deletes excessive ' + 'sign
	//cout << variablesUsed << endl;
}

void GameState::fillEquation()
{
	//equation is supposed to look like this : 1 - x - y - z = 0

	//for each column:
	for (int i = 0; i < queue.size(); i++)
	{
		//if proper position, put '1' in here (executes only once).  
		if (i == positionInQueue)		
			equation.push_back(1);

		//action for filling elements to the left and to the right from positionInQueue
		//only if its a unknown variable(not an intercept)
		else if (i != positionInQueue && variablesUsed > 0)
		{
			int notFound = 0;	//how many misses during lookup 

			//for every generated state that our object added
			for (int g_i = 0; g_i < generatedStates.size(); g_i++)
			{
				//seek if present in queue
				if (elementFound(generatedStates[g_i],i))
				{
					equation.push_back(-factors[g_i]);	//every further element is substracted from 1
					variablesUsed--;			
					break;
				}
				notFound++;
			}
			if (notFound == generatedStates.size()){
				equation.push_back(0);					//zero for every non-generated state
														//like : 1 - x - 0*a - 0*b - 0*c - y - z = 0
			}

		}
		else
			equation.push_back(0);
		//all factors are pushed now
	}
	equation.push_back(c);				//now add an intercept at the end

	////commented displaying features, not useful now
	//display row in matrix for that state
	//cout << endl << endl<< "equation like 1  -x  -y  -z = intercept" << endl;
	
	//for (int i = 0; i < equation.size(); i++)
		//cout << " " << setprecision(2) << setw(8) << equation[i];
	//cout << endl << endl;
}