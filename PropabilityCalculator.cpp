#include "stdafx.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<iomanip>

#include"GameState.h"
#include"Matrix.h"
#include"MonteCarloSimulation.h"
using namespace std;

//shortcut for such a long class name
typedef GameState gs;

//free function's declarations
void setPenalties();

int _tmain(int argc, _TCHAR* argv[])
{
	setPenalties();

	////create first state -  x(1,0,0);
	//GameState initial = GameState(1, 0, 0);

	////create our matrix, that is our main calculation's structure
	//Matrix M = Matrix();


	//gs::queue.push_back(&initial);	//add as first gamestate
	////do the same for every gamestate in the queue
	//for (int i = 0; i < gs::queue.size(); i++)
	//{	
	//	gs::queue[i]->fillQueue();
	//}
	////loops can't be merged
	//for (int i = 0; i < gs::queue.size(); i++)
	//{
	//	gs::queue[i]->fillEquation();
	//	M.pushRow(gs::queue[i]->getEquation());
	//}
	//	
	////all calculations'done
	////now matrix is completely filled with data

	////make a copy before modifying it
	//vector<vector<double>> copyofM= M.getMatrix();
	//M.gaussSeidel();
	//
	////load matrix from copy
	//M.loadMatrix(copyofM);
	//M.gaussElimination();

	////show results
	//M.displayResults();


	MonteCarloSimulation monte = MonteCarloSimulation();
	monte.play();
	monte.displayResult();

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
	vector<vector<int>> p = { { 2, -1 }, { 4, -1 }, { 6, -1 }, { 11, -1 }, { 13, -1 }, { 15, -14 }, { 20, -1 }, { 22, -1 }, { 24,
		-1 }, { 26, -25 } };	//p - penalties
	for (int p_i = 0; p_i < p.size(); p_i++)			//p_i - penalty index
	{
		GameState::gameBoard[p[p_i][0]] = p[p_i][1];						//set penalty on proper board tile, 
		//value of the penelty is nr1 element in each p subarray
	}
	for (int i = 0; i < 6; i++)
		GameState::gameBoard[N + i] = END_OF_BOARD;
}