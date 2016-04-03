#include "stdafx.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<iomanip>

#include"GameState.h"
#include"Matrix.h"
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

	//initial.fillQueue();			//build needed unknown variables to the queue
	//initial.fillEquation();			//build equation form it(single matrix row)
	
	//create our matrix, that is our main calculation's structure
	Matrix M = Matrix();

	//do the same for every gamestate in the queue
	for (int i = 0; i < gs::queue.size(); i++)
	{	
		gs::queue[i]->fillQueue();
		
	}

	for (int i = 0; i < gs::queue.size(); i++)
	{
		gs::queue[i]->fillEquation();
		M.pushRow(gs::queue[i]->getEquation());
	}
		
	//all calculations'done
	//now matrix is completely filled with data

	//M.display();
	M.gaussSeidel();


	//helpful board displaying
	cout << endl << endl<< "How this board looks like..." << endl;
	for (int i = 0; i < GameState::gameBoard.size()-6; i++)
		cout << "|" << setw(3) << GameState::gameBoard[i];
	cout << endl;

	return 0;
}

void setPenalties()
{ //{ 4, -2 }, { 5, -2 }, { 7, -5 }, { 9, -3 }, { 14, -12 }, { 15, -2 }, { 17, -7 }, { 19, -8 }, { 21, -3 },
//{ 22, -16 }, { 25, -9 }
	 
	//NO PENALTIES AT THIS TIME
	vector<vector<int>> p = { { 2, -1 }, { 4, -1 }, { 6, -1 }, { 11, -8 }, { 13, -10 }, { 15, -12 }, { 18, -13 }, { 20, -15 }, { 22, -17 }, { 24, -1 }, { 26, -3 } };	//p - penalties
	for (int p_i = 0; p_i < p.size(); p_i++)			//p_i - penalty index
	{
		GameState::gameBoard[p[p_i][0]] = p[p_i][1];						//set penalty on proper board tile, 
		//value of the penelty is nr1 element in each p subarray
	}
	for (int i = 0; i < 6; i++)
		GameState::gameBoard[N + i] = END_OF_BOARD;
}