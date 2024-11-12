#include "structCaballos.h"
#include "fragmenta.h"
#include <stdlib.h>
#include <string.h>

#define MAX_CABALLOS 1000

int main() {
    FILE *archivo = fopen("dataset.csv", "r");
    char lineaTexto[100];
    char** textoFragmentado;
    if (archivo == NULL) {
        perror("No se pudo abrir el archivo.\n");
        return 1; // Salida con error
    }

    struct Datos datos[MAX_CABALLOS];

    int num_caballos = 0;

    // Lee los datos del archivo y los almacena en un array de datos

    while(fgets(lineaTexto, 100, archivo) != NULL && num_caballos < MAX_CABALLOS){
        textoFragmentado = fragmenta(lineaTexto);

        strcpy(datos[num_caballos].edad, textoFragmentado[0]);
        datos[num_caballos].cirugia = (bool)textoFragmentado[1];
        datos[num_caballos].temperaturaRectal = atof(textoFragmentado[2]);
        datos[num_caballos].pulso = atof(textoFragmentado[3]);
        datos[num_caballos].frecuenciaRespiracion = atof(textoFragmentado[4]);
        strcpy(datos[num_caballos].temperaturaExtremidades, textoFragmentado[5]);
        strcpy(datos[num_caballos].dolor, textoFragmentado[6]);
        strcpy(datos[num_caballos].distensionAbdominal, textoFragmentado[7]);
        strcpy(datos[num_caballos].tuboNasogastrico, textoFragmentado[8]);
        strcpy(datos[num_caballos].heces, textoFragmentado[9]);
        datos[num_caballos].volumenCelulas = atof(textoFragmentado[10]);
        datos[num_caballos].proteina = atof(textoFragmentado[11]);
        strcpy(datos[num_caballos].resultado, textoFragmentado[12]);
        datos[num_caballos].lesionCirugia = (bool)textoFragmentado[13];

        num_caballos++;
    }

    // Imprime los datos de los datos en la consola

    for (int i = 0; i < num_caballos; i++) {
        printf("Datos del caballo %d: ", i + 1);
        printf("    Edad: %s ", datos[i].edad);
        printf("    Cirugia: %d ", (int)datos[i].cirugia);
        printf("    Temperatura Rectal: %0.2f ", datos[i].temperaturaRectal);
        printf("    Pulso: %0.2f ", datos[i].pulso);
        printf("    Frecuencia Respiratoria %0.2f ", datos[i].frecuenciaRespiracion);
        printf("    Temperatura Extremidades: %s ", datos[i].temperaturaExtremidades);
        printf("    Dolor: %s ", datos[i].dolor);
        printf("    Distension Abdominal: %s ", datos[i].distensionAbdominal);
        printf("    Tubo Nasogastrico: %s ", datos[i].tuboNasogastrico);
        printf("    Heces: %s ", datos[i].heces);
        printf("    Volumen de las celulas: %0.2f ", datos[i].volumenCelulas);
        printf("    Proteinas: %0.2f ", datos[i].proteina);
        printf("    Resultado: %s ", datos[i].resultado);
        printf("    Lesion cirugia: %d ", (int)datos[i].lesionCirugia);
        printf("\n");
    }

    // Cierra el archivo

    fclose(archivo);

    return 0; // Salida exitosa
}

