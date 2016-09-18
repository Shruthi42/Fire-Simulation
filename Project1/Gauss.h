#pragma once
#include  "Constants.h"


double gaussian(int x, double mean, double sigmaSquared)
{
	double fx = (exp((-1*pow((x-mean),2))/(2*sigmaSquared)));
	return fx;
}
