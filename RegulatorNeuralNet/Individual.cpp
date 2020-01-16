#include "Individual.h"



Individual::Individual()
{
	net = NeuralNet::RandomNet(100);
	success = 0;

	
	sys.setRuhelage(SystemState(0, 0, PI, 0));
	
}


Individual::~Individual()
{
}

void Individual::timestep(double dt)
{
	double u = -net.forward(sys.x - sys.xR)(0,0);
	sys.setInput(u);
	sys.timestep(dt);
	CalculateSuccess();
}

void Individual::Render(sf::RenderTarget & target)
{
	sys.render(target);
}

Individual Individual::Breed(const Individual & a, float wa, const Individual & b, float wb)
{
	Individual ret;

	ret.net = NeuralNet::Breed(a.net, wa, b.net, wb);

	return ret;
}

void Individual::CalculateSuccess()
{
	MatrixXd Q(4, 4);

	Q(0, 0) = 1;
	Q(1, 1) = 1;
	Q(2, 2) = 100;
	Q(3, 3) = 1000;

	auto div = sys.x - sys.xR;

	success += (div.transpose()*Q*div)(0,0);
}
