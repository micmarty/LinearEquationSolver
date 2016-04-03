#pragma once
#include<vector>
using namespace std;

class Matrix
{
private:
	vector<vector<double>> M;
public:
	Matrix();
	~Matrix();
	void pushRow(vector<double>r);
	void display();
	void gaussSeidel();
};

