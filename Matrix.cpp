#include "Matrix.h"
#include<iostream>
#include<iomanip>
using namespace std;

Matrix::Matrix()
{
}


Matrix::~Matrix()
{
}

void Matrix::pushRow(vector<double>r)
{
	//add whole row to matrix at the end
	M.push_back(r);
}

void Matrix::display()
{
	for (int y = 0; y < M.size(); y++)
	{
		for (int x = 0; x < M[0].size(); x++)
		{
			cout << "|" <<setprecision(3)<< setw(8) << M[y][x];
		}cout << endl << endl;
	}
}