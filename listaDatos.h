#include <stdbool.h>

typedef struct Datos
{
    char sexo;
    float edad;
    char donde;
    char tamañoFam[4];
    char situacionPadres;
    char trabajoM[10];
    char trabajoP[10];
    char tutor[10];
    float tiempoEstudios;
    float suspensos;
    char apoyoFam[4];
    char actividades[4];
    char enfermeria[4];
    char internet[4];
    char pareja[4];
    float relacionFam;
    float tiempoLibre;
    float vidaSocial;
    float alcoholNoFinde;
    float alcoholFinde;
    float salud;
}Datos;

typedef Datos tipoElementoLista;

typedef struct celdaL{
	tipoElementoLista elem;
	struct celdaL *sig;
}celdaLista; 
typedef struct tipoL{
	celdaLista *ini;
	celdaLista *fin;
}tipoLista;

void nuevaLista(tipoLista *);

void insertar(tipoLista *, tipoElementoLista);

tipoElementoLista consultarPrimero(tipoLista);

tipoElementoLista consultarUltimo(tipoLista);

void eliminarLista(tipoLista *);

bool esNulaLista(tipoLista);

void imprimirLista(tipoLista lista);

