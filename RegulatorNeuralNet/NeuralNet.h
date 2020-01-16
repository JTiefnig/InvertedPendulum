#pragma once

#include <vector>
#include <math.h>
#include "MatrixXd.h"
#include <random>
#include <string>
#include <sstream>






class NeuralNet
{

	// just for Testing single layer

	MatrixXd mat;

public:
	NeuralNet();
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

