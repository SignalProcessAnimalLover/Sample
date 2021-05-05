#include <stdio.h>
#include <math.h>
//#include "MyComplex.h"


void makeIQ(MyComplex signal[], unsigned int length)
{
	unsigned int i;
	MyComplex* ptemp = (MyComplex*)malloc(sizeof(MyComplex) * length);

	hilbert(ptemp, signal, length);
	for(i = 0; i < length; i++){
		signal[i].image = ptemp[i].real;
	} 
	free(ptemp);
}

unsigned int demodulateQPSK(unsigned char** ppsymbols, MyComplex samples[], unsigned int sample_length, unsigned int sr, unsigned int cf, unsigned int br, double initial_theta)
{
	unsigned int i, j, symbol_length = sample_length * br / sr;
	unsigned char* psymbols = (unsigned char*)malloc(sizeof(unsigned char) * symbol_length);
	MyComplex* p = (MyComplex*)malloc(sizeof(MyComplex) * sample_length);
	
	
	for(i = 0; i < sample_length; i++){//各サンプルに搬送波の逆相を掛ける。
		MyComplex rot, temp;

		ElementType theta = 2 * M_PI * i * cf / sr + initial_theta;// / centerfreq;
		rot.real = cos(-theta);
		rot.image = sin(-theta);
			
				
		mulComplex2(&p[i], &samples[i], &rot);
		fprintf(stdout ,"%d %lf %lf\n", i, p[i].real, p[i].image);
	}
	
	for(i = 0; i < symbol_length; i++){//信号空間上に配置されたサンプルからシンボルを得る。
		unsigned char symbol_map[2][2] = { {0, 3} ,{1, 2} };
		unsigned int start_sample = i * sr / br, end_sample = (1 + i) * sr/ br;
		ElementType x = 0, y = 0;
		
		for(j = start_sample; j < end_sample && j < sample_length; j++){
			x += p[j].real;
			y += p[j].image;
		}
		x /= (end_sample - start_sample);//多サンプルに跨ったシンボルについては
		y /= (end_sample - start_sample);//平均を取る。
		//fprintf(stdout ,"%lf %lf\n", x, y);
		psymbols[i] = symbol_map[0 < x ?  0 : 1][0 < y? 0 : 1];
	}
	
	free(p);
	*ppsymbols = psymbols;
	return symbol_length;
}





