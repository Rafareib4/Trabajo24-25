#include "normalizar.h"
#include "fragmenta.h"
#include "listaDistanciasMinimas.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NUM_FALLOS -2 //Marca de fallo
#define SALTAR_FALLOS -1

bool convert_string_to_bool(char* textoFragmentado){
    return strcmp(textoFragmentado, "1") == 0 || strcmp(textoFragmentado, "1\n") == 0;
}

void imprimirDatos(Patient pacientes[], int num_pacientes){
    for (int i = 0; i < num_pacientes; i++){
        printf("Datos del paciente %d: ", i + 1);
        printf("    Género: %s ", pacientes[i].gender);
        printf("    Edad: %.0f", pacientes[i].age);
        printf("    Hipertensión: %d ", (int)pacientes[i].hypertension);
        printf("    Enfermedad cardíaca: %d ", (int)pacientes[i].heart_disease);
        printf("    Casado alguna vez: %d ", (int)pacientes[i].ever_married);
        printf("    Tipo de trabajo: %s ", pacientes[i].work_type);
        printf("    Residencia: %s ", pacientes[i].residence);
        printf("    Glucosa: %.2f ", pacientes[i].glucose);
        printf("         BMI: %.2f ", pacientes[i].bmi);
        printf("    Estado de fumador: %.0f", pacientes[i].smoking_status);
        printf("    Derrame cerebral: %d ", (int)pacientes[i].stroke);
        printf("\n");
    }
}

void imprimirDatosNormalizados(Patient pacientes[], int num_pacientes){
    for (int i = 0; i < num_pacientes; i++) {
        printf("Datos normalizados del paciente %d: ", i + 1);
        printf("    genero: %s",pacientes[i].gender);
        printf("    edad: %.2f", pacientes[i].age);
        printf("    hipertension: %d",(int)pacientes[i].hypertension);
        printf("    enfermedad cardíaca: %d",(int)pacientes[i].heart_disease);
        printf("    residencia: %s", pacientes[i].residence);
        printf("    trabajo: %s", pacientes[i].work_type);
        printf("    Glucosa: %.2f", pacientes[i].glucose);
        printf("    BMI: %.2f", pacientes[i].bmi);
        printf("    fumador: %.2f", pacientes[i].smoking_status);
        printf("    Derrame cerebral: %d\n",(int)pacientes[i].stroke);
    }
}

int main(){
    FILE *archivo = fopen("dataset.csv", "r");
    char lineaTexto[100];
    char** textoFragmentado;
    if (archivo == NULL) {
        perror("No se pudo abrir el archivo.\n");
        exit(-1); // Salida con error
    }

    struct Patient pacientes[MAX_PATIENTS]; //Constante MAX_PATIENTS declarada en normalizar.h

    int num_pacientes = 0;
    char res;

    // Lee los datos del archivo y los almacena en un array de pacientes
    while(fgets(lineaTexto, 100, archivo) != NULL && num_pacientes < MAX_PATIENTS){
        textoFragmentado = fragmenta(lineaTexto);
        pacientes[num_pacientes].num = num_pacientes;
        strcpy(pacientes[num_pacientes].gender, textoFragmentado[0]);
        pacientes[num_pacientes].age = atoi(textoFragmentado[1]);
        pacientes[num_pacientes].hypertension = convert_string_to_bool(textoFragmentado[2]);
        pacientes[num_pacientes].heart_disease = convert_string_to_bool(textoFragmentado[3]);
        pacientes[num_pacientes].ever_married = convert_string_to_bool(textoFragmentado[4]);
        strcpy(pacientes[num_pacientes].work_type, textoFragmentado[5]);
        strcpy(pacientes[num_pacientes].residence, textoFragmentado[6]);
        pacientes[num_pacientes].glucose = atof(textoFragmentado[7]);
        pacientes[num_pacientes].bmi = atof(textoFragmentado[8]);
        pacientes[num_pacientes].smoking_status = atoi(textoFragmentado[9]);
        pacientes[num_pacientes].stroke = convert_string_to_bool(textoFragmentado[10]);
        num_pacientes++;
    }

    // Imprime los datos de los pacientes en la consola
    //imprimirDatos(pacientes, num_pacientes);

    normalizeData(pacientes, num_pacientes);

    // Imprimir los datos normalizados
    //imprimirDatosNormalizados(pacientes, num_pacientes);

    //Calcular distancias
    float dist_age, dist_bmi, dist_glucose, dist_smoking_status, dist_total, dist_gender, dist_hypertension, dist_heart_disease, dist_ever_married, dist_work_type, dist_residence;
    tipoLista lista;
    distanciaYCaso elementoLista;
    int knn, k;
    int contador1, contador0, contadorAciertos, contadorFallos, contadorWilson;
    float probabilidad;
    bool prediccion, check;
    char resW;
    knn = num_pacientes;
    contadorWilson = 0;
    do{
        contadorAciertos = 0;
        contadorFallos = 0;
        printf("Qué número de K quieres usar (1 <= K < %d): ", knn);
        scanf("%d", &k);
        while(k >= knn || k < 1){
            printf("Error, la K no es válida introdúcela de nuevo (1 <= K < %d): ", knn);
            scanf("%d", &k);
        }
        printf("Quieres usar Wilson si ejecutas otra vez knn s/n: ");
        scanf(" %c", &resW);
        int indice1, indice2;
        nuevaLista(&lista);
        for (indice1 = 0; indice1 < num_pacientes; indice1++){
            contador1 = 0;
            contador0 = 0;
            while(pacientes[indice1].num == SALTAR_FALLOS){
                indice1++;
            }
            for (indice2 = 0; indice2 < num_pacientes; indice2++){
                while(indice1 == indice2 || pacientes[indice2].num == SALTAR_FALLOS){
                    indice2++;
                }
                dist_gender = 1;
                dist_hypertension =1;
                dist_heart_disease = 1;
                dist_ever_married = 1;
                dist_work_type = 1;
                dist_residence = 1;
                dist_age = fabs(pacientes[indice1].age - pacientes[indice2].age);
                dist_glucose = fabs(pacientes[indice1].glucose - pacientes[indice2].glucose);
                dist_bmi = fabs(pacientes[indice1].bmi - pacientes[indice2].bmi);
                dist_smoking_status = fabs(pacientes[indice1].smoking_status - pacientes[indice2].smoking_status);
                if(pacientes[indice1].hypertension == pacientes[indice2].hypertension){
                    dist_hypertension = 0;
                }
                if(pacientes[indice1].heart_disease == pacientes[indice2].heart_disease){
                    dist_heart_disease = 0;
                }
                if(pacientes[indice1].ever_married == pacientes[indice2].ever_married){
                    dist_ever_married = 0;
                }
                if(strcmp(pacientes[indice1].gender, pacientes[indice2].gender)== 0){
                    dist_gender = 0;
                }
                if(strcmp(pacientes[indice1].work_type, pacientes[indice2].work_type)== 0){
                    dist_work_type = 0;
                }
                if(strcmp(pacientes[indice1].residence, pacientes[indice2].residence)== 0){
                    dist_residence = 0;
                }
                dist_total = sqrt(dist_age * dist_age + dist_bmi * dist_bmi + dist_glucose * dist_glucose + dist_smoking_status * dist_smoking_status + dist_ever_married + dist_gender + dist_heart_disease + dist_hypertension + dist_residence + dist_work_type);
                elementoLista.distancia = dist_total;
                elementoLista.stroke = pacientes[indice2].stroke;
                insertar(&lista, elementoLista);
            }
            check = lista.ini->elemento.stroke;
            for (indice2 = 0; indice2 < k; indice2++){
                if(lista.ini->elemento.stroke == 1){
                    contador1++;
                }
                else{
                    contador0++;
                }
                eliminarMenor(&lista);
            }
            if (contador0 < contador1){
                prediccion = 1;
            }
            else if (contador0 > contador1){
                prediccion = 0;
            }
            else if (contador0 == contador1){
                prediccion = check;
            }
            if (prediccion == pacientes[indice1].stroke){
                contadorAciertos++;
            }
            else if(prediccion != pacientes[indice1].stroke && (resW == 's' || resW == 'S')){
                contadorFallos++;
                pacientes[indice1].num = NUM_FALLOS;

            }
            if(!esNulaLista(lista)){
                eliminarTodosLosElementos(&lista);
            }
        }
        probabilidad = ((float)contadorAciertos / (float)knn) * 100;
        if(resW == 's' || resW == 'S'){
            for(int i = 0; i < num_pacientes; i++){
                if(pacientes[i].num == NUM_FALLOS){
                    pacientes[i].num = SALTAR_FALLOS;
                }
            }
            contadorWilson++;
            printf("La probabilidad de acierto para %d casos con K = %d, con %d wilson es: %.5f%%\n", knn, k, contadorWilson - 1, probabilidad);
        }
        else{
            printf("La probabilidad de acierto para %d casos con K = %d, con %d wilson es: %.5f%%\n", knn, k, contadorWilson, probabilidad);
        }
        printf("numero de aciertos: %d   numero de datos: %d\n", contadorAciertos, knn);
        knn = knn - contadorFallos;
        printf("Deseas ejecutar otra vez knn s/n: ");
        scanf(" %c", &res);
    } while (res == 's' || res == 'S');


    fclose(archivo);
    return 0; // Salida exitosa
}

