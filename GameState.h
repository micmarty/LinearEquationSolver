#pragma once
class GameState
{
private:
	int g;	//which player is rolling a dice in this turn
	int a;	//1st player position
	int b;	//2nd player position
	int c;	//intercept
public:
	GameState(int g, int a, int b);
	~GameState();

	friend bool operator==(const GameState& l, const GameState& p);
};


