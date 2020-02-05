#include "NeuralNet.h"



NeuralNet::NeuralNet()
	:mat(4,1)
{
	MatrixXd K(4, 1);
	K(0, 0) = -0.1;
	K(1, 0) = -0.3197;
	K(2, 0) = 4.6382;
	K(3, 0) = 4.7244;

	K = K * 1000.0;

	mat = K;
}


NeuralNet::~NeuralNet()
{
}

NeuralNet NeuralNet::RandomNet(float range)
{
	NeuralNet ret;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(-range, range);

	for (int i = 0; i < 4; i++)
	{
		ret.mat(i, 0) = dist(mt);
	}
	return ret;
}

MatrixXd NeuralNet::forward(const MatrixXd & input)
{
	return (mat.transpose())*input;
}

NeuralNet NeuralNet::Breed(const NeuralNet & a, double wa, const NeuralNet & b, double wb)
{

	// single layer case;
	wa = 1;
	wb = 1;

	MatrixXd aa = wa * a.mat;

	MatrixXd bb = wb * b.mat;

	NeuralNet ret;
	ret.mat = (aa+bb) * (1/(wa+wb));

	double variator = abs(ret.mat.sum())*0.01 + 1;

	ret.mat += MatrixXd::Random(ret.mat.rows(), ret.mat.cols(), -variator, variator);


	return ret;
}
