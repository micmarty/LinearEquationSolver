#include "stdafx.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<iomanip>

#include"GameState.h"
using namespace std;

//shortcut for such a long class name
typedef GameState gs;

//free function's declarations
void setPenalties();

int _tmain(int argc, _TCHAR* argv[])
{
	setPenalties();

	//create first state -  x(1,0,0);
	GameState initial = GameState(1, 0, 0);
	gs::queue.push_back(&initial);	//add as first gamestate

	initial.fillQueue();			//build needed unknown variables to the queue
	initial.fillEquation();			//build equation form it(single matrix row)

	//do the same for every gamestate in the queue
	for (int i = 1; i < gs::queue.size(); i++)
	{	
		gs::queue[i]->fillQueue();
		gs::queue[i]->fillEquation();
	}
		




	//helpful board displaying
	cout << endl << endl<< "How this board looks like..." << endl;
	for (int i = 0; i < GameState::gameBoard.size()-6; i++)
		cout << "|" << setw(3) << GameState::gameBoard[i];
	cout << endl;

	return 0;
}

void setPenalties()
{
	//NO PENALTIES AT THIS TIME
	vector<vector<int>> p = { { 4, 1 }, { 5, 1 } };	//p - penalties
	for (int p_i = 0; p_i < p.size(); p_i++)			//p_i - penalty index
	{
		GameState::gameBoard[p[p_i][0]] = p[p_i][1];						//set penalty on proper board tile, 
		//value of the penelty is nr1 element in each p subarray
	}
	for (int i = 0; i < 6; i++)
		GameState::gameBoard[N + i] = END_OF_BOARD;
}