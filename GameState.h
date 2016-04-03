#pragma once
#include<vector>
using namespace std;

#define N 3				//board length
#define END_OF_BOARD 0	//value that means - 'if you are here, you won'

class GameState
{
private:
	int g;			//which player is rolling a dice in this turn
	int a;			//1st player position
	int b;			//2nd player position
	double c;		//intercept

	int positionInQueue;
	int variablesUsed;

	vector<GameState*>generetedStates;
	vector<double> equation;//holds factors(PL wspó³czynniki)

public:
	static vector<int> gameBoard;
	static vector<GameState*> queue;

	//must-have
	GameState(int g, int a, int b);
	~GameState();

	//useful methods
	void fillQueue();
	void fillEquation();
	bool elementFound(GameState* neededElement);
	bool elementFound(GameState* neededElement,int foundAt);

	vector<double> getEquation();
	
	//comparison operator
	bool operator==(const GameState &r);
};


