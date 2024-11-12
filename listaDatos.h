#include <stdbool.h>

typedef struct Datos
{
    bool cirugia;
    char edad[10];
    float temperaturaRectal;
    int pulso;
    int frecuenciaRespiracion;
    char temperaturaExtremidades[10];
    char dolor[20];
    char distensionAbdominal[10];
    char tuboNasogastrico [10];
    char heces [20];
    int volumenCelulas;
    float proteina;
    char resultado[20];
    bool lesionCirugia;
    int lesion;

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

