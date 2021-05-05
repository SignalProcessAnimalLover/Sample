#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>
#include "MyComplex.h"
#include "MyFrequencyProcess.h"
#include "modulate.h"
#include "demodulate.h" 


#define N (1024)
#define M (1024)

#define SR (128)
#define CF (5)
#define BR (16)
#define PHASE (4)
#define ENERGY (100)
#define INITIAL_THETA (0)

unsigned int setSignal(MyComplex** ppsamples)
{
	unsigned int i, sample_length;
	unsigned char symbols[N * BR / SR];
	
	for(i = 0; i < N * BR / SR; i++){
		symbols[i] = i % PHASE;
	}
	sample_length =  modulateQPSK(ppsamples, symbols, N * BR / SR, ENERGY, SR, CF, BR, INITIAL_THETA);

	return sample_length;
}
void receiveSignal(MyComplex samples[])
{
	unsigned int i, symbol_length;
	unsigned char* psymbols;
	
	symbol_length = demodulateQPSK(&psymbols, samples, N, SR, CF, BR, INITIAL_THETA);
	
	for(i = 0; i < symbol_length; i++){
		fprintf(stdout, "%d %d\n", i, psymbols[i]);
	}
} 
int main(int argc, char *argv[])
{
	unsigned int i, j, k;
	MyComplex original[N], result[N], fftresult[N], invdft[N], invfft[N], hresult[N];
	MyComplex* ptemp = NULL;
	
	setSignal(&ptemp);
	memcpy(original, ptemp, N * sizeof(MyComplex) );
	free(ptemp);
	
	makeIQ(original, M);

	receiveSignal(original);
	//dumpMyComplexes(stdout, original, N);
}
