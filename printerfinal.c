#include "structPaciente.h"
#include "fragmenta.h"
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 1000

int main() {
    FILE *archivo = fopen("dataset.csv", "r");
    char lineaTexto[100];
    char** textoFragmentado;
    if (archivo == NULL) {
        perror("No se pudo abrir el archivo.\n");
        return 1; // Salida con error
    }

    struct Patient pacientes[MAX_PATIENTS];

    int num_pacientes = 0;

    // Lee los datos del archivo y los almacena en un array de pacientes
    while(fgets(lineaTexto, 100, archivo) != NULL && num_pacientes < MAX_PATIENTS){
        textoFragmentado = fragmenta(lineaTexto);
        strcpy(pacientes[num_pacientes].gender, textoFragmentado[0]);
        pacientes[num_pacientes].age = atoi(textoFragmentado[1]);
        pacientes[num_pacientes].hypertension = (bool)textoFragmentado[2];
        pacientes[num_pacientes].heart_disease = (bool)textoFragmentado[3];
        pacientes[num_pacientes].ever_married = (bool)textoFragmentado[4];
        strcpy(pacientes[num_pacientes].work_type, textoFragmentado[5]);
        strcpy(pacientes[num_pacientes].residence, textoFragmentado[6]);
        pacientes[num_pacientes].glucose = atof(textoFragmentado[7]);
        pacientes[num_pacientes].bmi = atof(textoFragmentado[8]);
        pacientes[num_pacientes].smoking_status = atoi(textoFragmentado[9]);
        pacientes[num_pacientes].stroke = (bool)textoFragmentado[10];
        num_pacientes++;
    }

    // Imprime los datos de los pacientes en la consola
    for (int i = 0; i < num_pacientes; i++) {
        printf("Datos del paciente %d: ", i + 1);
        printf("    Género: %s ", pacientes[i].gender);
        printf("    Edad: %d ", pacientes[i].age);
        printf("    Hipertensión: %d ", (int)pacientes[i].hypertension);
        printf("    Enfermedad cardíaca: %d ", (int)pacientes[i].heart_disease);
        printf("    Casado alguna vez: %d ", (int)pacientes[i].ever_married);
        printf("    Tipo de trabajo: %s ", pacientes[i].work_type);
        printf("    Residencia: %s ", pacientes[i].residence);
        printf("    Glucosa: %.2f ", pacientes[i].glucose);
        printf("    BMI: %.2f ", pacientes[i].bmi);
        printf("    Estado de fumador: %d ", pacientes[i].smoking_status);
        printf("    Derrame cerebral: %d ", (int)pacientes[i].stroke);
        printf("\n");
    }

    // Cierra el archivo
    fclose(archivo);

    return 0; // Salida exitosa
}

