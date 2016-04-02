#include "stdafx.h"
#include<iostream>
#include<vector>
#include<algorithm>

#include"GameState.h"
using namespace std;

#define N 6
#define END_OF_BOARD 0
vector<int> gameBoard(N + 6, 1);//na zapas zeby nie wyjsc za zakres

vector<GameState> queue;

void setPenalties();


int x(int g, int a, int b)
{	
	printf("x(%d, %d, %d) = ", g, a, b);
	
	int x_result = 0;
	int e = g == 1 ? 2 : 1;			//e - enemy

	//testing dice rolling result
	for (int d = 1; d <= 6; d++)	//d - dice roll result
	{  
		if (g == 1)
		{
			if (gameBoard[a + d] != END_OF_BOARD)
			{
				int penalty = gameBoard[a + d] < 0 ? gameBoard[a + d] : 0;
				GameState unknownState = GameState(e, a + d + penalty, b);

				//if no identical unknown game state is found, then add it to our queue
				if (find(queue.begin(), queue.end(), unknownState) == queue.end())
					queue.push_back(unknownState);
				
				printf("1/6*(%d, %d, %d) + ", e, a+d + penalty, b);
			}//else - if player 'g' is out of board, he WINS
			else
			{
				printf("1/6 + ");	//1 means that player nr 1 won
			}
		}
		if (g == 2)
		{
			if (gameBoard[b + d] != END_OF_BOARD)
			{
				int penalty = gameBoard[b + d] < 0 ? gameBoard[b + d] : 0;
				printf("1/6*(%d, %d, %d) + ", e, a, b + d + penalty);
			}//else - if player 'g' is out of board, he WINS
			else
			{
				printf("0/6 + ");//0 means that player nr 1 defeated
			}
		}
		
	}
	cout << "\b\b\b\033[K" << endl;//deletes excessive ' + 'sign
	return x_result;
}

int _tmain(int argc, _TCHAR* argv[])
{
	setPenalties();
	/*for (int i = 0; i < gameBoard.size(); i++)
	{
		cout << gameBoard[i] << " ";
	}cout << endl;*/
	return 0;
}

void setPenalties()
{
	vector<vector<int>> p = { { 4, -2 }, { 5, -2 } };	//p - penalties
	for (int p_i = 0; p_i < p.size(); p_i++)			//p_i - penalty index
	{
		gameBoard[p_i] = p[p_i][1];						//set penalty on proper board tile, 
		//value of the penelty is nr1 element in each p subarray
	}
	for (int i = 0; i < 6; i++)
		gameBoard[N + i] = END_OF_BOARD;
}