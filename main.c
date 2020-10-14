/** Pancakes

    Impresión del árbol de llamadas.

    Miguel Ángel Norzagaray Cosío
    20170831 (llegando la tormenta tropical Lidia)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PROF 	7
#define TAM         6

#include "Pancakes.h"

int main()
{
	int i;
	int DesordenInicial = 20;
	char Pancakes[64], PancakesOriginal[64];


	/* Globales */
	INFINITO = 1.0/0.0;
	ENCONTRADO = 1.0;
	MaxProf = MAX_PROF;
	TamSolucion=0;
	TamMejorSolucion=MAX;
	Tam = TAM;
	H = h4;
	strcpy(Objetivo, "abcdefghijklmnopqrstuvwxyz");
	strncpy(Pancakes,Objetivo,Tam);
	Pancakes[Tam] = '\0';

	puts("\nPancakes - para inteligencia artificial I");
	puts("Impresión del árbol de llamadas\n");
	printf("Desordenando ...");
	Desordenar(Pancakes,DesordenInicial);
	printf(": %s\n",Pancakes);
	strcpy(PancakesOriginal,Pancakes);

	/* Estableciendo un desorden específico

	MaxProf = 4;
	Tam = 4;
	strcpy(Pancakes,"badc");/// badc
	strcpy(PancakesOriginal,Pancakes);
	printf(": %s\n",Pancakes);*/

	printf("\nConstruyendo árboles . . . \n");
	///BusqProf(Pancakes,0);
	puts("* * * * * * * * * * * * * * * * * *");
	puts("Profundidad Iterativa:");
	BusqProfIterativa(Pancakes,0);
	puts("* * * * * * * * * * * * * * * * * *");
	puts("Amplitud:");BusqAmpli(Pancakes);
	puts("* * * * * * * * * * * * * * * * * *");
	puts("AStar:");AStar(Pancakes);
	puts("* * * * * * * * * * * * * * * * * *");
	puts("IDA:");IDA(Pancakes);

	printf("\n\nFin de programa.\n");

	return 0;
}

void Desordenar(char *s, int n)
{
	int i,i_ant;
	int L = strlen(s)-1;
	time_t t;

	srand((unsigned) time(&t));

	i_ant = 0;
	for ( ; n>0 ; n--) {
		i = rand()%L + 2;
		if ( i == i_ant ) {
			n++;
			continue;
		}
		Voltear(s,i);
		i_ant = i;
	}
}

void Voltear(char *s, int n)
{
	char c;
	int i,j,L;

	if ( n < 2 )
		return;
	L = strlen(s);
	if ( n>L )
		return;

	for ( i = L-n, j = L-1 ; i<j ; i++,j-- ) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

/* Fin de archivo */
