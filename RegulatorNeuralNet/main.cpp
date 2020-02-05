
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include "ControlSystem.h"
#include "Pouplation.h"

#include "Matrix.h"



void drawEnvironment(sf::RenderTarget & target)
{


	sf::Vector2u windowsize = target.getSize();
	//float offx = windowsize.x / 2.f;
	float offy = windowsize.y * 0.7f;


	sf::Vertex floor[] =
	{
		sf::Vertex(sf::Vector2f(0, offy), sf::Color::Black),
		sf::Vertex(sf::Vector2f(windowsize.x, offy), sf::Color::Black)
	};

	target.draw(floor, 5, sf::Lines);
}





int main()
{
	std::vector<sf::Shape*> myShapes;

	sf::RenderWindow window(sf::VideoMode(1200, 600), "Inverted Pendulum");

	
	
	
	Pouplation pop(10);

	// for L = 10
	/*MatrixXd K(4, 1);
	K(0, 0) = -0.1;
	K(1, 0) = -0.3197; 
	K(2, 0) = 4.6382;
	K(3, 0) = 4.7244;

	K = K * 1000.0;
*/
	

	bool done = false;
	bool autotrain = false;

	int counter = 0;


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed)
			{

				int mx = event.mouseButton.x;
				int windWidth = window.getSize().x / 2;
				double  sollpos = (mx - windWidth) / 20.0;
				
			
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					if (!done)
					{
						pop.Breed();
						done = true;
					}
					
				}

				if (event.key.code == sf::Keyboard::Right)
				{
					autotrain != autotrain;
				}

				
			}

			else
			{
				done = false;
			}
			
			if (event.type == sf::Event::KeyReleased)
			{
				
				
			}


				
		}

		if (autotrain)
		{
			if (20 < counter)
			{
				pop.Breed();
				counter = 0;
			}
				
			counter++;
		}



		sf::sleep(sf::milliseconds(10));

		window.clear(sf::Color::White);


		pop.timestep();

		drawEnvironment(window);

		pop.Render(window);

		window.display();

	}

	return 0;
}