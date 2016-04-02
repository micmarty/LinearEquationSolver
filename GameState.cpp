#include "GameState.h"


GameState::GameState(int g, int a, int b)
{

}


GameState::~GameState()
{
}

bool operator==(const GameState& l, const GameState& r)
{
	bool equalPlayers = (l.g == r.g);
	bool equalA = (l.a == r.a);
	bool equalB = (l.b == r.b);
	if (equalPlayers && equalA && equalB)
		return true;
	else
		return false;
}