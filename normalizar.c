#include "normalizar.h"

//Acción para encontrar los valores mínimos y máximos para la glucosa, bmi y edad
void calcularMaxYMin(Patient pacientes[], MaxYMin* maximos_minimos, int num_pacientes){

    maximos_minimos->min_glucose = pacientes[0].glucose, maximos_minimos->max_glucose = pacientes[0].glucose;
    maximos_minimos->min_bmi = pacientes[0].bmi, maximos_minimos->max_bmi = pacientes[0].bmi;
    maximos_minimos->min_age = pacientes[0].age, maximos_minimos->max_age = pacientes[0].age;

    for (int i = 0; i < num_pacientes; i++){
        if (pacientes[i].glucose < maximos_minimos->min_glucose){
            maximos_minimos->min_glucose = pacientes[i].glucose;
        }
        if (pacientes[i].glucose > maximos_minimos->max_glucose){
            maximos_minimos->max_glucose = pacientes[i].glucose;
        }

        if (pacientes[i].bmi < maximos_minimos->min_bmi){
            maximos_minimos->min_bmi = pacientes[i].bmi;
        }
        if (pacientes[i].bmi > maximos_minimos->max_bmi){
            maximos_minimos->max_bmi = pacientes[i].bmi;
        }
        if (pacientes[i].age < maximos_minimos->min_age){
            maximos_minimos->min_age = pacientes[i].age;
        }
        if (pacientes[i].age > maximos_minimos->max_age){
            maximos_minimos->max_age = pacientes[i].age;
        }
    }
}

//Acción para normalizar los datos
void normalizeData(struct Patient pacientes[], int num_pacientes) {

    MaxYMin maximos_minimos;
    calcularMaxYMin(pacientes, &maximos_minimos, num_pacientes);
    for (int i = 0; i < num_pacientes; i++) {
        pacientes[i].glucose = (pacientes[i].glucose - maximos_minimos.min_glucose) / (maximos_minimos.max_glucose - maximos_minimos.min_glucose);
        pacientes[i].bmi = (pacientes[i].bmi - maximos_minimos.min_bmi) / (maximos_minimos.max_bmi - maximos_minimos.min_bmi);
        pacientes[i].age = (pacientes[i].age - maximos_minimos.min_age) / (maximos_minimos.max_age - maximos_minimos.min_age);
        pacientes[i].smoking_status = (pacientes[i].smoking_status)/2;
    }
}
