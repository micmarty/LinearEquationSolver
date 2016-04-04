#pragma once
#include<vector>
using namespace std;
class MonteCarloSimulation
{
private:
	int player1winsCounter;
	double probability;
	vector<double>results;
	vector<int>iterationsNumber;
	int resultOfGame();
public:
	MonteCarloSimulation();
	~MonteCarloSimulation();
	void play(int iterations);
	void displayResult();

};

