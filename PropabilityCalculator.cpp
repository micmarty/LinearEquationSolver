#include "stdafx.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<iomanip>
#include<ctime>

#include"GameState.h"
#include"Matrix.h"
#include"MonteCarloSimulation.h"
using namespace std;

//shortcut for such a long class name
typedef GameState gs;

void setPenalties()
{
	//p - penalties
	//{field, value}
	vector<vector<int>> p = {
		{ 4, -1 }, { 5, -3 }, { 6, -5 }, { 7, -7 }, { 13, -1 }, { 14, -3 }, { 15, -5 }, { 20, -1 }, { 24, -1 },
		{ 25, -3 }, { 26, -5 }
	};
	for (int p_i = 0; p_i < p.size(); p_i++)			//p_i - penalty index
	{
		GameState::gameBoard[p[p_i][0]] = p[p_i][1];	//set penalty on proper board tile, 
		//value of penalty's field is nr 0  in each p subarray
		//value of the penalty is nr 1 element in each p subarray
	}
	for (int i = 0; i < 6; i++)
		GameState::gameBoard[N + i] = END_OF_BOARD;
}


void generateMatrix(Matrix &M)
{
	clock_t start = clock();
	int i;//iterator for further loops

	for (i = 0; i < gs::queue.size(); i++)//do the same for every gamestate in the queue
		gs::queue[i]->fillQueue();


	//loops ^    can't be merged.Queue must be filled completely before we enter the next loop.
	for (i = 0; i < gs::queue.size(); i++)
	{
		gs::queue[i]->fillEquation();//for every game state in queue, generate linear equation, so that we can push the row into matrix
		M.pushRow(gs::queue[i]->getEquation());

	}
	cout << "generating matrix took: " << (clock() - start) / (double)CLOCKS_PER_SEC << endl;
}

void calculateUnknownsFromMatrix(Matrix &M)
{
	clock_t start=clock();
	//make a copy before modifying it
	vector<vector<double>> copyofM = M.getMatrix();

	M.gaussSeidel();				//first matrix algorithm
	cout << "Gauss-Seidel took:      " << (clock() - start) / (double)CLOCKS_PER_SEC << endl;

	M.loadMatrix(copyofM);			//load matrix from copy

	start = clock();
	M.gaussElimination();			//second matrix algorithm
	cout << "Gauss took:             " << (clock() - start) / (double)CLOCKS_PER_SEC << endl;
}

void runMonteCarloSimulation(MonteCarloSimulation &monte,int iterations)
{
	clock_t start = clock();
	monte.play(iterations);				//simulate random play million times
	cout << "Monte Carlo took:       " << (clock() - start) / (double)CLOCKS_PER_SEC << endl;
}
int _tmain(int argc, _TCHAR* argv[])
{
//--INITIALIZATIONS

	srand(time(NULL));
	gs::queue.reserve(1000);//I need to make sure that push_pack on vector is O(1). 
							//If there would be a lack of space in allocated memory,
							//vector would deallocate whole content and rewrite it in bigger memory area(I try to avoid this).
							//1000 is enough for N=28
	
	setPenalties();			//create proper board(overwrite default '1', where needed with penaulty value)

	
	GameState initial = GameState(1, 0, 0);//create first state -  x(1,0,0);
	Matrix M = Matrix();//create our matrix, that is our main calculation's structure
	gs::queue.push_back(&initial);	//add as first gamestate
//---------------------------------------------------------------------------------------------------------------------


//--GENERATING MATRIX FOR GAME
	generateMatrix(M);				
	//all calculations'done
	//now matrix is completely filled with data
//---------------------------------------------------------------------------------------------------------------------


//--RUN THREE ALGORITHMS
	calculateUnknownsFromMatrix(M);						//run both Gauss and Gauss-Seidel matrix algorithms
	MonteCarloSimulation monte = MonteCarloSimulation();//instance of third method
	runMonteCarloSimulation(monte,1000);					//run simulation for monte
	runMonteCarloSimulation(monte, 10000);
	runMonteCarloSimulation(monte, 100000);
	runMonteCarloSimulation(monte, 1000000);
//---------------------------------------------------------------------------------------------------------------------


//--DISPLAY RESULTS - probabilities for three methods 
	M.displayResults();									//show results of both matrix algorithms
	monte.displayResult();								//show result of monte-carlo algorithm
//---------------------------------------------------------------------------------------------------------------------	


//--BOARD DISPLAYING at the end
	cout << endl << endl<< "How this board looks like..." << endl;
	for (int i = 0; i < GameState::gameBoard.size()-6; i++)
		cout << "|" << setw(3) << GameState::gameBoard[i];
	cout << endl;
//---------------------------------------------------------------------------------------------------------------------
	return 0;
}

