#include <stdio.h>
#include <math.h>

typedef double ElementType;

typedef struct
{
	ElementType real, image;
}MyComplex;


void dumpMyComplexes(FILE* fp, MyComplex data[], unsigned int length)
{
	unsigned int i;
	for(i = 0; i < length; i++){
		fprintf(fp, "%d %lf %lf\n", i, data[i].real, data[i].image);
	}
}

void* addComplex2(MyComplex* pdst, MyComplex* pleft, MyComplex* pright)
{
	pdst->real = pleft->real + pright->real;
	pdst->image = pleft->image + pright->image;
}

void* subComplex2(MyComplex* pdst, MyComplex* pleft, MyComplex* pright)
{
	pdst->real = pleft->real - pright->real;
	pdst->image = pleft->image - pright->image;
}

void* mulComplex2(MyComplex* pdst, MyComplex* pleft, MyComplex* pright)
{
	pdst->real = pleft->real * pright->real - pleft->image * pright->image;
	pdst->image = pleft->real * pright->image + pleft->image * pright->real;
}

void* addComplex1(MyComplex* pdst, MyComplex* psrc)
{
	pdst->real += psrc->real;
	pdst->image += psrc->image;
}

void* subComplex1(MyComplex* pdst, MyComplex* psrc)
{
	pdst->real -= psrc->real;
	pdst->image -= psrc->image;
}

void* mulComplex1(MyComplex* pdst, MyComplex* psrc)
{
	ElementType real = pdst->real * psrc->real - pdst->image * psrc->image;
	ElementType image = pdst->real * psrc->image + pdst->image * psrc->real;
	pdst->real = real;
	pdst->image = image;
}



