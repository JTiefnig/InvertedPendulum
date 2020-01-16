#pragma once

#include "Individual.h"
#include <vector>
#include "SFML/Graphics.hpp"



class Pouplation
{
	std::vector<Individual> peps;

	double maxSuccess;

	

public:
	Pouplation(int size);
	~Pouplation();

	double getSuccess() const
	{
		return maxSuccess;
	}

	void timestep();

	void Render(sf::RenderTarget& target);

	void Breed();

	
	
};

