#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void help()
	{

	printf("How to use this thing:\n \
	a.out [options] file\n\n \
	OPTIONS:\n \
	--help\t print this\n \
	-b\t beginning - where the first bin should be placed on x axis (float), default 0\n \
	-c\t centering - should output add half step to bin x axis (0 - no, 1 - yes), default 1\n \
	-n\t number of bins - set number of bins, default 250\n \
	-s\t step size - how wide are bins, default 1\n\n") ;

	}


int main(int argc, char **argv)
{

if (argc == 1)
	{
	printf("File not found\n") ;
	exit(1) ;
	}

float f, step, beg, center ; // f - where bin is on x axis, step - number of steps (default 250), beg - see below
							// center - flag do you want bins shifted by half step default 1
int n, c ; // n - bin number in array, c - character from file, arSize - number of bins (default 250)
unsigned int *pArray, arSize ; // pointer to array, array size

FILE *pFile ;

center = 1 ;
beg = 0 ; // beginning where histogram starts, default = 0
arSize = 250 ;
step = 1 ;


for (int i = 1; i < argc; i++) // don't know how else make flags
	{

	if (strcmp(argv[1], "--help") == 0) // compares strings
		{
		help() ;
		return 0 ;
		}

	if (strcmp(argv[i], "-b") == 0) // where is start
		{
		i++ ;
		beg = strtof(argv[i], NULL) ;
		}

	if (strcmp(argv[i], "-c") == 0) // centering
		{
		i++ ;
		center = strtof(argv[i], NULL) ;
		}

	if (strcmp(argv[i], "-n") == 0) // number of bins (max 250)
		{
		i++ ;
		arSize = strtof(argv[i], NULL) ;
		}

	if (strcmp(argv[i], "-s") == 0) // step size
		{
		i++ ;
		step = strtof(argv[i], NULL) ;
		}

/*	TODO
	if (strcmp(argv[i], "-c") == 0) // column number because for now file has to be just 1 column of values to divide
		{
		i++ ;
		center = strtof(argv[i], NULL) ;
		}

	if (strcmp(argv[i], "-c") == 0) // separator
		{
		i++ ;
		center = strtof(argv[i], NULL) ;
		}

*/

	}

pArray = (unsigned int *) calloc(arSize, sizeof(unsigned int)) ; // allocate memory

if (pArray == NULL)
	{
	printf("calloc NULL pointer\nToo many bins!'n") ;
	exit(1) ;
	}

pFile = fopen(argv[argc-1], "r") ;

if (pFile == NULL)
	{
	printf("File not found\n") ;
	exit(1) ;
	}

c = fscanf(pFile, "%f", &f) ;

while (c != EOF)
	{
	f /= step ;
	n = (int) f ;
	
	if(n < arSize)
		*(pArray + n) = *(pArray + n) + 1 ;

	c = fscanf(pFile, "%f", &f) ;
	} 

fclose(pFile) ;

pFile = fopen("datout.dat", "w") ;

for (int i = 0; i < arSize; i++)
		fprintf(pFile, "%f %d\n", beg + step * (float)i + center * 0.5 * step, *(pArray+i)) ;

free(pArray) ; // free allocated memory. I don't wanna to find out what happens if I don't
fclose(pFile) ;

return 0 ;

}


