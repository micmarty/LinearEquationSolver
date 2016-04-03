#pragma once
#include<vector>
using namespace std;

class Matrix
{
	private:
		vector<vector<double>> M;	//matrix
		int n;						//matrix dimensions(square matrix)
		int b_columnIndex;			//index of intercepts column

		vector<double>x1;			//results from gauss-seidel calculations
		vector<double>x2;			//results from gaussian elimination calculations

	public:
		Matrix();
		~Matrix();

		void pushRow(vector<double>r);
		vector<vector<double>> getMatrix();
		void loadMatrix(vector<vector<double>> copyofM);

		void gaussSeidel();
		void gaussElimination();

		void displayMatrix();
		void displayResults();
};

