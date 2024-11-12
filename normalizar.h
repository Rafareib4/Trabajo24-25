#include <stdio.h>
#include <stdbool.h>
#include <structCaballos.h>
#define MAX_PATIENTS 1000


typedef struct MaxYMin{
    float minTemperaturaRectal, maxTemperaturaRectal;
    float minPulso, maxPulso;
    float minFrecuenciaResp, maxFrecuenciaResp;
    float minVolumenCelulas, maxVolumenCelulas;
    float minProteina, maxProteina;
} MaxYMin; //Nota: no ponemos el del smoking_status porque sabemos que su valor máximo es dos y el mínimo es 0

void calcularMaxYMin(Datos[], MaxYMin*, int);

void normalizeData(Datos[], int);
