#pragma once
#include "Matrix.h"
#include <random>

class MatrixXd : public Matrix<double>
{
public:


	MatrixXd(int m, int n);
	MatrixXd(const Matrix<double>& temp)
		:Matrix(temp)
	{}

	
	operator double() const
	{
		return v[0][0];
	}


	static MatrixXd Random(int m, int n, double min =0.0, double max=1.0)
	{
		MatrixXd ret(m, n);
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<double> dist(min, max);

		for(int i=0; i<m; i++)
			for (int j = 0; j < n; j++)
			{
				ret(i, j) = dist(mt);
			}

		return ret;
	}

	double sum() const
	{
		double ret=0;
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
			{
				ret += v[i][j];
			}

		return ret;
	}


};