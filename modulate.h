#include <stdio.h>
#include <math.h>

//#include "MyComplex.h"




unsigned int modulateQPSK(MyComplex** ppsamples, unsigned char symbols[], unsigned int symbol_length, double energy, unsigned int sr, unsigned int cf, unsigned int br, double initial_theta)
{
	unsigned int i, sample_length = symbol_length * sr / br;
	MyComplex* psamples = (MyComplex*)malloc( sizeof(MyComplex)  * sample_length);
	
	for(i = 0; i < sample_length; i++){
		double theta = initial_theta + (1 + (2 * (symbols[i * br / sr] % 4) ) )* M_PI / 4 + 2 * M_PI * i * cf / sr;
		psamples[i].real = energy * cos(theta);
		psamples[i].image = 0;
		
		fprintf(stderr, "%d %d %lf \n",i, symbols[i * br / sr],  energy * cos(initial_theta + (1 + (2 * (symbols[i * br / sr] % 4) ) ) * M_PI / 4) );
	}
	
	*ppsamples = psamples;
	
	//fprintf(stdout, "%lf\n", (*ppsamples)[5].real);
	return sample_length;
}
