#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char **argv)
{

float f, step, beg, center ; // f - where bin is on x axis, step - number of steps (default 250), beg - see below
							// center - flag do you want bins shifted by half step default 1
int n, c ; // n - bin number in array, c - character from file
FILE *pFile ;

center = 1 ;
beg = 0 ; // beginning where histogram starts, default = 0

for (int i = 1; i < argc; i++) // don't know how else make flags
	{

	if (strcmp(argv[1], "--help") == 0) // compares strings
		{
		printf("help\n") ; // TODO write help
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

/*	TODO
	if (strcmp(argv[i], "-c") == 0) // step size
		{
		i++ ;
		center = strtof(argv[i], NULL) ;
		}

	if (strcmp(argv[i], "-c") == 0) // number of bins (max 250)
		{
		i++ ;
		center = strtof(argv[i], NULL) ;
		}

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

unsigned int a1[250] ;

for(int i = 0; i < 250; i++)
	a1[i] = 0 ;

pFile = fopen(argv[argc-1], "r") ;

step = 250 ;

if (pFile == NULL)
	{
	printf("File not found\n") ;
	return 1 ;
	}

c = fscanf(pFile, "%f", &f) ;

while (c != EOF)
	{
	f /= step ;
	n = (int) f ;
	
	if(n < 250)
		n[a1] ++ ;	

	c = fscanf(pFile, "%f", &f) ;
	} 

fclose(pFile) ;

pFile = fopen("datout.dat", "w") ;

for (int i = 0; i < 250; i++)
	{
	if (i < 250)
		fprintf(pFile, "%f %d\n", beg + step * (float)i + center * 0.5 * step, a1[i]) ;
	}

fclose(pFile) ;

return 0 ;

}


