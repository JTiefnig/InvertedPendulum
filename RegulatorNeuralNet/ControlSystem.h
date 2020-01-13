#pragma once
#include <SFML/Graphics.hpp>
#include "MatrixXd.h"
#include <math.h>

#define PI 3.1415

// CartPend
// Imlementation of an inverted Pendulum 
// 
// author Johannes Tiefnig




class SystemState : public MatrixXd
{

public: 
	SystemState(double x, double dx, double phi, double dphi)
		:MatrixXd(4, 1)
	{
		v[0][0] = x;
		v[1][0] = dx;
		v[2][0] = phi;
		v[3][0] = dphi;
	}
	SystemState()
		:MatrixXd(4, 1)
	{}

	SystemState(const Matrix<double>& temp)
		:MatrixXd(4, 1)
	{
		if (temp.cols() != 1)
			return;

		for (int i = 0; i < 4 && i < temp.rows(); i++)
		{
			v[i][0] = temp.getVal(i, 0);
		}
	
	}

};




class ControlSystem
{

	// Model variables
	double m = 1;
	double M = 5;
	double L = 10;
	double g = -10;
	double d = 1;

	
	MatrixXd K;

public:

	SystemState xR;

	ControlSystem();
	~ControlSystem();

	SystemState x; // 

	// Nonlinear differential equationion 
	SystemState function(const SystemState& state);

	void timestep(double dt);


	void render(sf::RenderTarget& target);


	void setRuhelage(SystemState XR);
	void setStateParameter(MatrixXd k);
};





