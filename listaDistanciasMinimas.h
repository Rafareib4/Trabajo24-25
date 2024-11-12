#include <stdbool.h>
typedef struct distanciaYCaso{
	float distancia;
	bool stroke;
}distanciaYCaso;
typedef struct celdaL{
	struct distanciaYCaso elemento;
	struct celdaL *sig;
	struct celdaL *ant;
}celdaLista;
typedef struct tipoL{
	celdaLista *ini;
	celdaLista *fin;
}tipoLista;

void nuevaLista(tipoLista *);

void insertar(tipoLista *, distanciaYCaso);

bool esNulaLista(tipoLista);

void eliminarMenor(tipoLista *);

void eliminarTodosLosElementos(tipoLista *);
