#include "MonteCarloSimulation.h"
#include"GameState.h"
#include<iostream>
#include<iomanip>
using namespace std;

#define WON 1
#define LOOSE 0

MonteCarloSimulation::MonteCarloSimulation()
{
	player1winsCounter = 0;
	probability = 0;
}


MonteCarloSimulation::~MonteCarloSimulation()
{
}

int MonteCarloSimulation::resultOfGame()
{
	int player1Position = 0;
	int player2Position = 0;
	int diceRollingResult = 0;//unknown yet
	
	while (true)
	{
		//player nr 1
		diceRollingResult = rand() % 6 + 1;
		player1Position += diceRollingResult + GameState::gameBoard[player1Position + diceRollingResult];

		//player nr 2
		diceRollingResult = rand() % 6 + 1;
		player2Position += diceRollingResult + GameState::gameBoard[player2Position + diceRollingResult];

		if (player1Position >= N)
			return WON;
		else if (player2Position >= N)
			return LOOSE;
	}
}
void MonteCarloSimulation::play(int iterations)
{
	player1winsCounter = 0;			//clear that EVERY time
	for (int game = 0; game < iterations; game++)
	{
		player1winsCounter += resultOfGame();
	}
	probability = player1winsCounter / (double)iterations;
	results.push_back(probability);
	iterationsNumber.push_back(iterations);
}

void MonteCarloSimulation::displayResult()
{
	for (int i = 0; i < results.size();i++)
		cout << "x(1,0,0) = Monte Carlo Simulation\t" << setprecision(36) << results[i]<<" for "<<iterationsNumber[i]<<" iterations" << endl;
}
