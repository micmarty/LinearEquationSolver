#pragma once

class MonteCarloSimulation
{
private:
	int player1winsCounter;
	double probability;
	int resultOfGame();
public:
	MonteCarloSimulation();
	~MonteCarloSimulation();
	void play();
	void displayResult();

};

