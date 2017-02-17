#include "Vonmises.h"
#include<math.h>
/*
calculate scalar by Vomises formula
*/
double tev::Vonmises(double sig1, double sig2, double sig3, double t1, double t2, double t3)
{
	double scalar = 0.0;
	scalar= double(sqrt((pow(sig1 - t1, 2) + pow(t1 - t3, 2) + pow(t3 - sig1, 2) + 6 * (pow(sig2, 2) + pow(t2, 2) + pow(sig3, 2))) / 2));
	return scalar;
}
