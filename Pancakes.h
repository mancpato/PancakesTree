#ifndef PANCAKES_H_INCLUDED
#define PANCAKES_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#define MAX	200

float INFINITO;
float ENCONTRADO;

int MaxProf;	/// Límite de movimientos
int TamSolucion;
int Tam;	/// Cuántos pancakes hay en total
int SolucionEncontrada;
int TamMejorSolucion;

char Objetivo['z'-'a'+2];
int SolucionActual[MAX];
int MejorSolucion[MAX];

void Voltear(char *, int);
void Desordenar(char *,int);

void BusqProf(char *, int);
void BusqProfAct(char *s, int n_ant);
void BusqProfIterativa(char *, int );
void BusqAmpli(char *s);
void AStar(char *s);
float IDA(char *s);

int (*H)(char*);	// La función que será empleada.
int h1(char *s);
int h2(char *s);
int h3(char *s);
int h4(char *s);
int h5(char *s);

#ifdef __cplusplus
extern "C"  }
#endif

#endif // PANCAKES_H_INCLUDED
