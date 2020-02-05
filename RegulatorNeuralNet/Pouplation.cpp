#include "Pouplation.h"
#include <iostream>


Pouplation::Pouplation(int size)
{
	peps = std::vector<Individual>(size);
}


Pouplation::~Pouplation()
{
}

void Pouplation::timestep()
{
	
	
	for (auto&& i : peps)
	{
		for(int c = 5; c>0; c--)
			i.timestep(0.06);
		
		if (i.getSuccess() < maxSuccess)
			maxSuccess = i.getSuccess();
	}
}

void Pouplation::Render(sf::RenderTarget & target)
{
	for (auto&& i : peps)
	{
		if (maxSuccess*1.1 > i.getSuccess())
		{
			i.Mark();
		}
		i.Render(target);
	}
		
}

void Pouplation::Breed()
{
	double success = 10e10;
	Individual Best;
	// Find the best 
	// System Platzhirsch 
	// Der Beste bekommt alle (leicht zu programmieren)

	for (auto&& i : peps)
	{
		if (i.getSuccess() < success)
		{
			success = i.getSuccess();
			Best = i;
		}
	}
		
	maxSuccess = success;

	if (success < 0.01)
		success = 0.01;// anti 0 div

	for (auto&& i : peps)
	{

		double wa = 1 / (i.getSuccess()<0.01? 0.01 : i.getSuccess() ) ;
		double wb = 1 / success;

		if (wa * 2 < wb)
		{
			std::cout << "rand new" << std::endl;
			i = Individual();
			wa = wb;
		}

 		i = Individual::Breed(i, wa, Best, wb);
	}


	std::cout << "Max Success: " << maxSuccess << std::endl;

	std::cout << std::endl << "Best: " << std::endl << Best.toString() << std::endl << std::endl;

}
