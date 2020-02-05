#include "ControlSystem.h"
#include <math.h>
#include "SFML/Graphics.hpp"
#include <iostream>



ControlSystem::ControlSystem()
	:K(4,1)
{
	// init itial state
	x(2, 0) = PI*0.99; // just testing

	
}


ControlSystem::~ControlSystem()
{
}

SystemState ControlSystem::function(const SystemState & state)
{

	// for L = 2
	/*MatrixXd K(4, 1);
	K(0, 0) = -1.716;
	K(1, 0) = -7.026;
	K(2, 0) = 142.53;
	K(3, 0) = 58.052;*/

	/*K(0, 0) = -0.1;
	K(1, 0) = -0.25;
	K(2, 0) = 2.65;
	K(3, 0) = 1.54;

	K = K * 1000.0;*/


	/*MatrixXd K(4, 1);
	K(0, 0) = -0.1;
	K(1, 0) = -0.3197;
	K(2, 0) = 4.6382;
	K(3, 0) = 4.7244;

	K = K * 1000.0;
*/


	//auto kk = K.transpose()*(state-xR);
	
	//std::cout << kk << std::endl;

	 //u =  -kk(0,0); 

	double maxu = 100;

	if (u > maxu)
		u = maxu;
	if (u < -maxu)
		u = -maxu;


	


	double x = state.getVal(0, 0);
	double dx = state.getVal(1, 0);
	double phi = state.getVal(2, 0);
	double dphi = state.getVal(3, 0);

	double Sy = sin(phi);
	double Cy = cos(phi);
	double D = m * L*L*(M + m * (1.0 - pow(Cy, 2)));

	SystemState ret;

	ret(0, 0) = dx;
	ret(1, 0) = (1 / D)*(-pow(m,2) * pow(L, 2) * g*Cy*Sy + m * pow(L, 2) * (m*L* pow(dphi,2) * Sy - d * dx)) + m * L*L*(1 / D)*u;
	ret(2, 0) = dphi;
	//ret(3, 0) = (1 / D)*((m + M)*m*g*L*Sy - m * L*Cy*(m*L*pow(dphi, 2) * Sy - d * dx)) - m * L*Cy*(1 / D)*u; //+ .01*randn;

	// my solution :

	double Z = m * L - m * Cy*Cy *m *L /(M+m);

	ret(3, 0) = g*m*Sy/Z - m*m*L*dphi*dphi*Sy*Cy/(m+M) - m/(m+M)*Cy*u/Z;


	return ret;
}

void ControlSystem::timestep(double dt)
{

	// Classical Runge-Kutta solver 


	SystemState k1 = function(x);
	SystemState k2 = function(x + (dt / 2.0 * k1));
	SystemState k3 = function(x + (dt / 2.0 * k2));
	SystemState k4 = function(x + dt * k3);

	x = x + dt / 6 * (k1 + k2 * 2.0 + 2.0 * k3 + k4);

}



void ControlSystem::render(sf::RenderTarget & target)
{
	// just very basic implementation of an visualization

	float scale = 20;

	// to get the cart centered on the screen

	sf::Vector2u windowsize = target.getSize();
	float offx = windowsize.x / 2.f;
	float offy = windowsize.y * 0.6f;

	sf::Color gray(100, 100, 100);


	float cartpx = offx  + scale * x(0, 0);
	float cartpy = offy;
	// main cart with wheels
	sf::RectangleShape cart(sf::Vector2f(120.f, 50.f));
	cart.setSize(sf::Vector2f(3*scale, 2*scale));
	cart.setPosition(cartpx - 1.5*scale, cartpy);
	//cart.setFillColor(gray);

	cart.setOutlineThickness(5);
	cart.setOutlineColor(gray);

	target.draw(cart);


	// wheels
	sf::CircleShape wheel(0.5*scale);
	wheel.setPointCount(8);
	wheel.setFillColor(sf::Color::Black);
	wheel.setPosition(cartpx-1.5*scale, cartpy + 2 * scale);
	target.draw(wheel);
	wheel.setPosition(cartpx+1.5*scale-scale, cartpy+2*scale);
	target.draw(wheel);



	// Pendlulum


	float ppx = cartpx + sin(x(2,0)) *L * scale;
	float ppy = cartpy + cos(x(2, 0)) *L * scale;


	sf::CircleShape m(0.5*scale);
	m.setPointCount(16);

	if (mark)
	{
		m.setFillColor(sf::Color::Red);
		mark = false;
	}
	else
	{
		m.setFillColor(gray);
	}
	

	m.setPosition(ppx-scale*0.5, ppy-scale*0.5);
	target.draw(m);


	// Pendulum line
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(cartpx, cartpy), sf::Color::Blue),
		sf::Vertex(sf::Vector2f(ppx, ppy), sf::Color::Blue)
	};

	target.draw(line, 2, sf::Lines);





}

void ControlSystem::setRuhelage(SystemState XR)
{

	xR = XR;
}

void ControlSystem::setStateParameter(MatrixXd k)
{
	K = k;
}
