#include "stdafx.h"
#include<iostream>
#include<vector>
#include<algorithm>

#include"GameState.h"
using namespace std;

typedef GameState gs;

void setPenalties();

int _tmain(int argc, _TCHAR* argv[])
{
	setPenalties();
	GameState initial = GameState(1, 0, 0);
	initial.fillEquation();

	for (int i = 0; i < gs::queue.size(); i++)
		gs::queue[i]->fillEquation();

	/*for (int i = 0; i < GameState::gameBoard.size(); i++)
	{
		cout << GameState::gameBoard[i] << " ";
	}cout << endl;*/
	return 0;
}

void setPenalties()
{
	//NO PENALTIES AT THIS TIME
	vector<vector<int>> p = { { 0, 1 }, { 0, 1 } };	//p - penalties
	for (int p_i = 0; p_i < p.size(); p_i++)			//p_i - penalty index
	{
		GameState::gameBoard[p[p_i][0]] = p[p_i][1];						//set penalty on proper board tile, 
		//value of the penelty is nr1 element in each p subarray
	}
	for (int i = 0; i < 6; i++)
		GameState::gameBoard[N + i] = END_OF_BOARD;
}