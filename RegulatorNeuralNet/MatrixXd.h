#pragma once
#include "Matrix.h"

class MatrixXd : public Matrix<double>
{
public:


	MatrixXd(int m, int n);
	MatrixXd(const Matrix<double>& temp)
		:Matrix(temp)
	{}

};