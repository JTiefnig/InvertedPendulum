
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include "ControlSystem.h"

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

	ControlSystem sys;

	sys.setRuhelage(SystemState(0, 0, PI, 0));



	// for L = 10
	MatrixXd K(4, 1);
	K(0, 0) = -0.1;
	K(1, 0) = -0.3197;
	K(2, 0) = 4.6382;
	K(3, 0) = 4.7244;

	K = K * 1000.0;

	sys.setStateParameter(K);


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
				std::cout << "target" << sollpos << std::endl;

				std::cout << "ist " << sys.xR(0,0) << std::endl;
				sys.setRuhelage(SystemState(sollpos, 0, PI, 0));
				sys.setStateParameter(K);
			
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Left)
				{
					sys.setRuhelage(SystemState(0, -3, PI, 0));
					auto mk = K;
					mk(0, 0) = 0;
					sys.setStateParameter(mk);
				}
					

				if (event.key.code == sf::Keyboard::Right)
				{
					sys.setRuhelage(SystemState(0, 3, PI, 0));
					auto mk = K;
					mk(0, 0) = 0;
					sys.setStateParameter(mk);
				}
					
			}
			
			if (event.type == sf::Event::KeyReleased)
			{
				sys.setRuhelage(SystemState(0, 0, PI, 0));
				
			}


				
		}



		sf::sleep(sf::milliseconds(10));

		window.clear(sf::Color::White);


		for(int i =10; i>0; i--)
			sys.timestep(0.02);

		drawEnvironment(window);

		sys.render(window);

		window.display();

	}

	return 0;
}