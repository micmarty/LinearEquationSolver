#include "MonteCarloSimulation.h"
#include"GameState.h"
#include<ctime>
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
void MonteCarloSimulation::play()
{
	srand(time(NULL));
	for (int game = 0; game < 1000000; game++)
	{
		player1winsCounter += resultOfGame();
	}
	probability = player1winsCounter / 1000000.0;
}

void MonteCarloSimulation::displayResult()
{
	cout << "x(1,0,0) = Monte Carlo Simulation\t" << setprecision(36) << probability << endl;
}
