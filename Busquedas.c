/***
Algoritmos de búsqueda.

Programa de ejemplo del problema de los pancakes para IA I.

	BusqProf	Búsqueda en profundidad normal.
	BusqProfAct	Búsqueda en profundidad, actualizando la
			profundidad máxima.

Miguel Ángel Norzagaray Cosío
20170912
*/
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>

#include "Pancakes.h"
#include "Cola.h"

/** BusqProf
	Búsqueda en profundidad normal.

    s:		Cadena que representa los pancakes
    n_ant:	La cantidad de pancakes recien volteados

*/
void BusqProf(char *s, int n_ant)
{
	if ( !strncmp(s,Objetivo,Tam) ) {
		putchar('!');
		if ( TamSolucion < TamMejorSolucion ) {
			putchar('!');
			for ( int i = 0; i < TamSolucion ; i++ )
				MejorSolucion[i] = SolucionActual[i];
			TamMejorSolucion = TamSolucion;
		}
		return;
	}
	if ( MaxProf <= TamSolucion )
		return;

	for ( int i = 2 ; i <= Tam ; i++ ) {
		if ( i == n_ant )
			continue;
		Voltear(s,i);
		putchar('\n');
		for ( int j=0 ; j<TamSolucion+1 ; j++ )
			printf("\t");
		printf("%d %s", i, s);
		SolucionActual[TamSolucion++] = i;
		BusqProf(s,i);
		Voltear(s,i);
		TamSolucion--;
	}
}

/** BusqProfAct
	Búsqueda en profundidad, actualizando la profundidad máxima.

    s:		Cadena que representa los pancakes
    n_ant:	La cantidad de pancakes recien volteados
*/
void BusqProfAct(char *s, int n_ant)
{
	int i;

	if ( !strncmp(s,Objetivo,Tam) ) {
		putchar('!');
		if ( TamSolucion < TamMejorSolucion ) {
			putchar('!');
			for ( i = 0; i < TamSolucion ; i++ )
				MejorSolucion[i] = SolucionActual[i];
			TamMejorSolucion = TamSolucion;
			MaxProf = TamMejorSolucion;
		}
		return;
	}
	if ( MaxProf <= TamSolucion )
		return;

	for ( i = 2 ; i <= Tam ; i++ ) {
		if ( i == n_ant )
			continue;
		Voltear(s,i);
		putchar('\n');
		for ( int j=0 ; j<TamSolucion+1 ; j++ )
			printf("\t");
		printf("%d %s", i, s);
		SolucionActual[TamSolucion++] = i;
		BusqProfAct(s,i);
		Voltear(s,i);
		TamSolucion--;
	}
}

/** BusqProfIterativa
	Búsqueda en profundidad creciente.

    s:		Cadena que representa los pancakes
    n_ant:	La cantidad de pancakes recien volteados

*/
void BusqProfIterativa(char* s, int n_ant)
{
	int BusqProfIt(char *s, int n_ant);

	SolucionEncontrada = 0;
	for ( MaxProf=1 ; !SolucionEncontrada  || MaxProf<3 ; MaxProf++ ) {
		printf("\n\nProfundidad = %d", MaxProf);
		TamSolucion=0;
		TamMejorSolucion=MAX;
		putchar('\n');
		printf("%s", s);
		if ( BusqProfIt(s, 0) )
			break;
	}
}

/** BusqProfIt
	Búsqueda en profundidad normal.

    s:		Cadena que representa los pancakes
    n_ant:	La cantidad de pancakes recien volteados

*/
int BusqProfIt(char *s, int n_ant)
{
	int i;

	if ( !strncmp(s,Objetivo,Tam) ) {
		puts("!");
		SolucionEncontrada = 1;
		if ( TamSolucion < TamMejorSolucion ) {
			for ( i = 0; i < TamSolucion ; i++ )
				MejorSolucion[i] = SolucionActual[i];
			TamMejorSolucion = TamSolucion;
		}
		return 1;
	}
	if ( MaxProf <= TamSolucion )
		return 0;

	for ( i = 2 ; i <= Tam ; i++ ) {
		if ( i == n_ant )
			continue;
		Voltear(s,i);
		putchar('\n');
		for ( int j=1 ; j<=TamSolucion+1 ; j++ )
			printf("\t");
		printf("%d %s", i, s);
		SolucionActual[TamSolucion++] = i;
		if ( BusqProfIt(s,i) ) {
			Voltear(s,i);
			return 1;
		}
		Voltear(s,i);
		TamSolucion--;
	}
	return 0;
}

/** BusqAmpli
	Búsqueda en amplitud normal.

    s:		Cadena que representa los pancakes
*/
void BusqAmpli(char *s)
{
	int i, n_ant=0;
	char Cad[MAX];
	Cola C;
	struct Nodo *R;

	if ( !strncmp(Cad,Objetivo,Tam) )
		return;
	SetUpCola(&C);
	AgregarCola(&C, 0, 0, NULL, s);
	printf("\n%s\n",s);
	while ( !ColaVacia(&C) ) {
		R = SacarCola(&C);
		strcpy(Cad,R->s);
		n_ant = R->n;
		printf("<%s\n",Cad);
		for ( i = 2 ; i <= Tam ; i++ ) {
			if ( i == n_ant )
				continue;
			Voltear(Cad,i);
			for ( int k=0 ; k<R->Prof+1 ; k++ )
				putchar('\t');
			printf("%d>%s\n",i,Cad);
			if ( !strncmp(Cad,Objetivo,Tam) )
				goto SOLUCION;
			AgregarCola(&C, i, R->Prof+1,R,Cad);
			Voltear(Cad,i);
		}
	}
SOLUCION:
	TamMejorSolucion = R->Prof+1;
	MejorSolucion[R->Prof] = i;
	while ( R->p ) {
		MejorSolucion[R->Prof-1]=R->n;
		R = R->p;
	}
}

/** AStar

	Busqueda en amplitud con cola de prioridad.
*/
void AStar(char *s)
{
	int i, h, n_ant=0;
	char Cad[MAX];
	Cola C;
	struct Nodo *R;

	if ( !strncmp(Cad,Objetivo,Tam) )
		return;
	SetUpCola(&C);
	AgregarColaPriori(&C, 0, 0, 0, NULL, s);
	printf("\n%s %d\n",s,h3(s));
	while ( !ColaVacia(&C) ) {
		R = SacarCola(&C);
		strcpy(Cad,R->s);
		n_ant = R->n;
		printf("<%d%s\n",R->Priori,Cad);
		for ( i = 2 ; i <= Tam ; i++ ) {
			if ( i == n_ant )
				continue;
			Voltear(Cad,i);
			for ( int k=0 ; k<R->Prof+1 ; k++ )
				putchar('\t');
			printf("%d>%s ",i,Cad);
			if ( !strncmp(Cad,Objetivo,Tam) )
				goto SOLUCION;
			h = R->Prof + H(Cad);
			printf("%d\n",h);
			AgregarColaPriori(&C, i, R->Prof+1,h,R,Cad);
			Voltear(Cad,i);
		}
	}
SOLUCION:
    printf("%d\n",h);
	TamMejorSolucion = R->Prof+1;
	MejorSolucion[R->Prof] = i;
	while ( R->p ) {
		MejorSolucion[R->Prof-1]=R->n;
		R = R->p;
	}
}

/** IDA

	Iterative Deepening A*.
*/
float IDA(char *s)
{
	int Cota, i;
	float t;
	float Busq_IDA(char *s, int ant, int Cota);

	Cota = H(s);
	printf("\n%s",s);
	do {
		printf("\n\nCota: %d\n%s",Cota,s);
		t = Busq_IDA(s, 0, Cota);
		if ( t == ENCONTRADO ) {
			TamMejorSolucion = TamSolucion;
			for ( i = 0; i < TamSolucion ; i++ )
				MejorSolucion[i] = SolucionActual[i];
			return ENCONTRADO;
		}
		if ( t == INFINITO  ||  t == Cota )
			return INFINITO;
		Cota = t;
	} while ( 1 );
}

float Busq_IDA(char *s, int n_ant, int Cota)
{
	int i;
	float f, t, min;

	if ( !strncmp(s,Objetivo,Tam) )
		return 1;

	f = TamSolucion + H(s);	/* f = g + h */

	if ( f > Cota )
		return f;

	min = INFINITO;
	for ( i = 2 ; i <= Tam ; i++ ) {
		if ( i == n_ant )
			continue;
		Voltear(s,i);
		SolucionActual[TamSolucion++] = i;
		{putchar('\n');
		for ( int j=0 ; j<TamSolucion ; j++ )
			printf("\t");
		printf("%d%s%d", i, s, h4(s)+TamSolucion);}
		t = Busq_IDA(s,i,Cota);
		if ( t == ENCONTRADO )
			return ENCONTRADO;
		if ( t<min )
			min = t;
		Voltear(s,i);
		TamSolucion--;
	}
	return min;
}

#ifdef __cplusplus
}
#endif

/* Fin de archivo */
