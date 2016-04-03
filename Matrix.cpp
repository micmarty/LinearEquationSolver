#include "Matrix.h"
#include"GameState.h"
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

void Matrix::gaussSeidel()
{
	const int n = GameState::queue.size();
	const int column_b = n;

	for (int k = 0; k < n - 1; k++)
	{
		for (int i = k + 1; i < n; i++)
		{
			double m = M[i][k] / M[k][k];
			for (int j = k + 1; j < n; j++)
				M[i][j] -= m * M[k][j];
			M[i][column_b] -= m * M[k][column_b];
		}
	}
	double *x = new double[n];
	x[n-1] = M[n - 1][column_b] / M[n - 1][column_b - 1];
	for (int i = n - 2; i >= 0; i--)
	{
		x[i] = M[i][column_b];//i albo l
		for (int j = i + 1; j < n; j++)
		{
			x[i] -= M[i][j] * x[j];
		}
		x[i] /= M[i][i];
	}
	for (int i = 0; i < n; i++)
	{
		cout <<setprecision(36)<< "x[" << i << "] = " << x[i] << endl;
	}
	
}