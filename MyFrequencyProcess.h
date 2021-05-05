#include <stdio.h>
#include <math.h>
//#include "MyComplex.h"


void dft(MyComplex dst[], MyComplex src[], unsigned int length)
{
	unsigned int i, j;
	
	for(i = 0; i < length; i++){
		dst[i].real = dst[i].image = 0;
		for(j = 0; j < length; j++){
			MyComplex temp;
			MyComplex rot;
			
			rot.real = cos(-2 * M_PI * i * j / length);
			rot.image = sin(-2 * M_PI * i * j / length);
			
			mulComplex2(&temp, &src[j], &rot);
			addComplex1(&dst[i], &temp); 
		}
	}
}

void idft0(MyComplex dst[], MyComplex src[], unsigned int length)
{
	unsigned int i, j;
	
	for(i = 0; i < length; i++){
		dst[i].real = dst[i].image = 0;
		for(j = 0; j < length; j++){
			MyComplex temp;
			MyComplex rot;
			
			rot.real = cos(2 * M_PI * i * j / length);
			rot.image = sin(2 * M_PI * i * j / length);
			
			mulComplex2(&temp, &src[j], &rot);
			addComplex1(&dst[i], &temp); 
		}
	}
}

void idft(MyComplex dst[], MyComplex src[], unsigned int length)
{
	unsigned int i;
	idft0(dst, src, length);
	
	for(i = 0; i < length; i++){
		dst[i].real /= length;
		dst[i].image /= length;
	}
}

void fft(MyComplex dst[], MyComplex src[], unsigned int length)
{
	if(length % 2){
		dft(dst, src, length);
	}else{
		unsigned int i, j, half = length / 2;
		MyComplex* peven = (MyComplex*)malloc(sizeof(MyComplex) * half);
		MyComplex* podd = (MyComplex*)malloc(sizeof(MyComplex) * half);
		MyComplex* pevenft = (MyComplex*)malloc(sizeof(MyComplex) * half);
		MyComplex* poddft = (MyComplex*)malloc(sizeof(MyComplex) * half);
		
		for(i = 0; i < half; i++){
			peven[i] = src[2 * i];
			podd[i] = src[1 + 2 * i];
		}
		
		fft(pevenft, peven, half);
		fft(poddft, podd, half);
		
		for(i = 0; i < half; i++){			
			MyComplex temp;
			MyComplex rot;
			rot.real = cos(-2 * M_PI * i / length);
			rot.image = sin(-2 * M_PI * i/ length);
			
			mulComplex2(&temp, &poddft[i], &rot);
			addComplex2(&dst[i], &pevenft[i], &temp);
			subComplex2(&dst[i + half], &pevenft[i], &temp);
		}
		free(poddft);
		free(pevenft);
		free(podd);
		free(peven);
	}
}

void ifft0(MyComplex dst[], MyComplex src[], unsigned int length)
{
	if(length % 2){
		idft0(dst, src, length);
	}else{
		unsigned int i, j, half = length / 2;
		MyComplex* peven = (MyComplex*)malloc(sizeof(MyComplex) * half);
		MyComplex* podd = (MyComplex*)malloc(sizeof(MyComplex) * half);
		MyComplex* pevenft = (MyComplex*)malloc(sizeof(MyComplex) * half);
		MyComplex* poddft = (MyComplex*)malloc(sizeof(MyComplex) * half);
		
		for(i = 0; i < half; i++){
			peven[i] = src[2 * i];
			podd[i] = src[1 + 2 * i];
		}
		
		ifft0(pevenft, peven, half);
		ifft0(poddft, podd, half);
		
		for(i = 0; i < half; i++){			
			MyComplex temp;
			MyComplex rot;
			rot.real = cos(2 * M_PI * i / length);
			rot.image = sin(2 * M_PI * i/ length);
			
			mulComplex2(&temp, &poddft[i], &rot);
			addComplex2(&dst[i], &pevenft[i], &temp);
			subComplex2(&dst[i + half], &pevenft[i], &temp);
		}
		free(poddft);
		free(pevenft);
		free(podd);
		free(peven);
	}
}

void ifft(MyComplex dst[], MyComplex src[], unsigned int length)
{
	unsigned int i;
	ifft0(dst, src, length);
	
	for(i = 0; i < length; i++){
		dst[i].real /= length;
		dst[i].image /= length;
	}
}


void hilbert(MyComplex dst[], MyComplex src[], unsigned int length)
{
	unsigned int i;
	MyComplex* ptemp = (MyComplex*)malloc(sizeof(MyComplex) * length);

	fft(ptemp, src, length);
	for(i = 0; i < length / 2; i++){
		MyComplex temp;
		
		temp.real = ptemp[i].image;
		temp.image = -ptemp[i].real;
		ptemp[i] = temp;
		
		
		temp.real = -ptemp[length - 1 - i].image;
		temp.image = ptemp[length - 1 - i].real;
		ptemp[length - 1 - i] = temp;
	}	
	ifft(dst, ptemp, length);
	
	
	free(ptemp);
}

