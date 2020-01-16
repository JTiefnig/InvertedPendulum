#pragma once
#include <SFML/Graphics.hpp>
#include "NeuralNet.h"
#include "ControlSystem.h"
#include <string>


class Individual
{
	double success;

	NeuralNet net;
	ControlSystem sys;
	

public:
	Individual();
	~Individual();

	void timestep(double dt);
	void Render(sf::RenderTarget& target);

	static Individual Breed(const Individual& a, float wa, const Individual& b, float wb);

	double getSuccess()
	{
		return success;
	}


	

	std::string toString() const
	{
		return net.toString();
	}

protected:


	void CalculateSuccess();

};

