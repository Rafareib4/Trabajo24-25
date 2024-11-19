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

void imprimirDatos(Patient caballos[], int num_caballos){
    for (int i = 0; i < num_caballos; i++){
        printf("Datos del paciente %d: ", i + 1);
        printf("    Edad: %s ", caballos[i].edad);
        printf("    Temperatura Rectal: %.2f ", caballos[i].temperaturaRectal);
        printf("    Pulso: %.2f ", caballos[i].pulso);
        printf("    Frecuencia Respiracion: %.2f ", caballos[i].frecuenciaRespiracion);
        printf("    Temperatura Extremidades: %s ", caballos[i].temperaturaExtremidades);
        printf("    Dolor: %s ", caballos[i].dolor);
        printf("    Distension Abdominal: %s ", caballos[i].distensionAbdominal);
        printf("    Tubo Nasogastrico: %s ", caballos[i].tuboNasogastrico);
        printf("    Heces: %s ", caballos[i].heces);
        printf("    Volumen Celular: %.2f ", caballos[i].volumenCelulas);
        printf("    Proteina: %.2f ", caballos[i].proteina);
        printf("    Operado: %d ", (int)caballos[i].cirugia);
        printf("    Lesion: %d ", (int)caballos[i].lesionCirugia);
        printf("    Resultado: %d", (int)caballos[i].resultado);
        printf("\n");
    }
}

int main(){
    FILE *archivo = fopen("datasetDefinitivo.csv", "r");
    char lineaTexto[100];
    char** textoFragmentado;
    if (archivo == NULL) {
        perror("No se pudo abrir el archivo.\n");
        exit(-1); // Salida con error
    }


    int num_caballos = 0;
    char res;

    // Lee los datos del archivo y los almacena en un array de caballos
    while(fgets(lineaTexto, 100, archivo) != NULL && num_caballos < MAX_CABALLOS){
        textoFragmentado = fragmenta(lineaTexto);
        caballos[num_caballos].num = num_caballos;
        caballos[num_caballos].cirugia = convert_string_to_bool(textoFragmentado[0]);
        strcpy(caballos[num_caballos].edad, textoFragmentado[1]);
        caballos[num_caballos].temperaturaRectal = atof(textoFragmentado[2]);
        caballos[num_caballos].pulso = atof(textoFragmentado[3]);
        caballos[num_caballos].frecuenciaRespiracion = atof(textoFragmentado[4]);
        strcpy(caballos[num_caballos].temperaturaExtremidades, textoFragmentado[5]);
        strcpy(caballos[num_caballos].dolor, textoFragmentado[6]);
        strcpy(caballos[num_caballos].distensionAbdominal, textoFragmentado[7]);
        strcpy(caballos[num_caballos].tuboNasogastrico, textoFragmentado[8]);
        strcpy(caballos[num_caballos].heces, textoFragmentado[9]);
        caballos[num_caballos].volumenCelulas = atof(textoFragmentado[10]);
        caballos[num_caballos].proteina = atof(textoFragmentado[11]);
        caballos[num_caballos].resultado = convert_string_to_bool(textoFragmentado[12]);
        caballos[num_caballos].lesionCirugia = convert_string_to_bool(textoFragmentado[13]);
        num_caballos++;
    }

    // Imprime los datos de los caballos en la consola
    imprimirDatos(caballos, num_caballos);

    normalizeData(caballos, num_caballos);

    //Calcular distancias
    float dist_edad, dist_cirugia, dist_temperaturaRectal, dist_pulso, dist_total, dist_frecuenciaRespiracion, dist_temperaturaExtremidades, dist_dolor, dist_distensionAbdominal, dist_tuboNasogastrico, dist_heces, dist_volumenCelulas, dist_proteina, dist_resultado, dist_lesionCirugia;
    tipoLista lista;
    distanciaYCaso elementoLista;
    int numKnn, k;
    int contador1, contador0, contadorAciertos, contadorFallos, contadorWilson;
    float probabilidad;
    bool prediccion, check;
    char resW;
    knn = num_caballos;
    contadorWilson = 0;
    do{
        contadorAciertos = 0;
        contadorFallos = 0;
        printf("Qué número de K quieres usar (1 <= K < %d): ", numKnn);
        scanf("%d", &k);
        while(k >= numKnn || k < 1){
            printf("Error, la K no es válida introdúcela de nuevo (1 <= K < %d): ", knn);
            scanf("%d", &k);
        }
        printf("Quieres usar Wilson si ejecutas otra vez knn s/n: ");
        scanf(" %c", &resW);
        int indice1, indice2;
        nuevaLista(&lista);
        for (indice1 = 0; indice1 < num_caballos; indice1++){
            contador1 = 0;
            contador0 = 0;
            while(caballos[indice1].num == SALTAR_FALLOS){
                indice1++;
            }
            for (indice2 = 0; indice2 < num_caballos; indice2++){
                while(indice1 == indice2 || caballos[indice2].num == SALTAR_FALLOS){
                    indice2++;
                }
                dist_cirugia = 1;
                dist_edad =1;
                dist_temperaturaExtremidades = 1;
                dist_dolor = 1;
                dist_distensionAbdominal = 1;
                dist_tuboNasogastrico = 1;
                dist_heces = 1;
                dist_resultado = 1;
                dist_lesionCirugia = 1;

                dist_temperaturaRectal = fabs(caballos[indice1].temperaturaRectal - caballos[indice2].temperaturaRectal);
                dist_pulso = fabs(caballos[indice1].pulso - caballos[indice2].pulso);
                dist_frecuenciaRespiracion = fabs(caballos[indice1].frecuenciaRespiracion - caballos[indice2].frecuenciaRespiracion);
                dist_volumenCelulas = fabs(caballos[indice1].volumenCelulas - caballos[indice2].volumenCelulas);
                dist_proteina = fabs(caballos[indice1].proteina-caballos[indice2].proteina);

                if(caballos[indice1].cirugia == caballos[indice2].cirugia){
                    dist_cirugia = 0;
                }
                if(caballos[indice1].resultado == caballos[indice2].resultado){
                    dist_resultado = 0;
                }
                if(caballos[indice1].lesionCirugia == caballos[indice2].lesionCirugia){
                    dist_lesionCirugia = 0;
                }
                if(strcmp(caballos[indice1].dolor, caballos[indice2].dolor)== 0){
                    dist_dolor = 0;
                }
                if(strcmp(caballos[indice1].distensionAbdominal, caballos[indice2].distensionAbdominal)== 0){
                    dist_distensionAbdominal = 0;
                }
                if(strcmp(caballos[indice1].edad, caballos[indice2].edad)== 0){
                    dist_edad = 0;
                }
                if(strcmp(caballos[indice1].temperaturaExtremidades, caballos[indice2].temperaturaExtremidades)== 0){
                    dist_temperaturaExtremidades = 0;
                }
                if(strcmp(caballos[indice1].tuboNasogastrico, caballos[indice2].tuboNasogastrico)== 0){
                    dist_tuboNasogastrico = 0;
                }
                if(strcmp(caballos[indice1].heces, caballos[indice2].heces)== 0){
                    dist_heces = 0;
                }
                dist_total = sqrt(dist_temperaturaRectal * dist_temperaturaRectal + dist_pulso * dist_pulso + dist_frecuenciaRespiracion * dist_frecuenciaRespiracion + dist_volumenCelulas * dist_volumenCelulas + dist_proteina*dist_proteina + dist_cirugia + dist_resultado + dist_lesionCirugia + dist_dolor + dist_distensionAbdominal + dist_edad + dist_temperaturaExtremidades + dist_tuboNasogastrico + dist_heces);
                elementoLista.distancia = dist_total;
                elementoLista.stroke = caballos[indice2].stroke;
                insertar(&lista, elementoLista);
            }
            check = lista.ini->elemento.resultado;
            for (indice2 = 0; indice2 < k; indice2++){
                if(lista.ini->elemento.resultado == 1){
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
            if (prediccion == caballos[indice1].resultado){
                contadorAciertos++;
            }
            else if(prediccion != caballos[indice1].resultado && (resW == 's' || resW == 'S')){
                contadorFallos++;
                caballos[indice1].num = NUM_FALLOS;

            }
            if(!esNulaLista(lista)){
                eliminarTodosLosElementos(&lista);
            }
        }
        probabilidad = ((float)contadorAciertos / (float)numKnn) * 100;
        if(resW == 's' || resW == 'S'){
            for(int i = 0; i < num_caballos; i++){
                if(caballos[i].num == NUM_FALLOS){
                    caballos[i].num = SALTAR_FALLOS;
                }
            }
            contadorWilson++;
            printf("La probabilidad de acierto para %d casos con K = %d, con %d wilson es: %.5f%%\n", numKnn, k, contadorWilson - 1, probabilidad);
        }
        else{
            printf("La probabilidad de acierto para %d casos con K = %d, con %d wilson es: %.5f%%\n", numKnn, k, contadorWilson, probabilidad);
        }
        printf("numero de aciertos: %d   numero de datos: %d\n", contadorAciertos, numKnn);
        numKnn = numKnn - contadorFallos;
        printf("Deseas ejecutar otra vez knn s/n: ");
        scanf(" %c", &res);
    } while (res == 's' || res == 'S');


    fclose(archivo);
    return 0; // Salida exitosa
}

