#include <stdio.h>
#include <stdbool.h>
#define MAX_CABALLOS 1000

typedef struct Datos
{
    bool cirugia;
    char edad[10];
    float temperaturaRectal;
    float pulso;
    float frecuenciaRespiracion;
    char temperaturaExtremidades[10];
    char dolor[20];
    char distensionAbdominal[10];
    char tuboNasogastrico [10];
    char heces [20];
    float volumenCelulas;
    float proteina;
    char resultado[20];
    bool lesionCirugia;

}Datos;
