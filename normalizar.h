#include <stdio.h>
#include <stdbool.h>
#include <listaDatos.h>
#define MAX_PATIENTS 1000


typedef struct MaxYMin{
    float min_glucose, max_glucose;
    float min_bmi, max_bmi;
    float min_age, max_age;
} MaxYMin; //Nota: no ponemos el del smoking_status porque sabemos que su valor máximo es dos y el mínimo es 0

void calcularMaxYMin(Patient[], MaxYMin*, int);

void normalizeData(Patient[], int);
