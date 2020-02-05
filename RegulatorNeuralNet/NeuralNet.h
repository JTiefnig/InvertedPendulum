#pragma once

#include <vector>
#include <math.h>
#include "MatrixXd.h"
#include <random>
#include <string>
#include <sstream>




struct MyStruct
{

};


class NeuralNet
{

	// just for Testing single layer

	MatrixXd mat;

public:
	NeuralNet();
	NeuralNet(const MatrixXd& mat);
	~NeuralNet();

	static NeuralNet RandomNet(float range);


	// Get Output to Given inupt

	MatrixXd forward(const MatrixXd& input);

	// Breed

	static NeuralNet Breed(const NeuralNet& a, double wa, const NeuralNet& b, double wb);


	std::string toString() const
	{

		std::stringstream a;
		a << mat;

		return a.str();
	}

};

