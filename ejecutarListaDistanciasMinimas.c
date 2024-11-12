#include<stdio.h>
#include "listaDistanciasMinimas.h"

int main(){
	tipoLista lista;
    distanciaYCaso a1, a2, a3, a4, a5;
    a1.distancia = 0.7;
    a2.distancia = 0.75;
    a3.distancia = 0.6;
    a4.distancia = 0.9;
    a5.distancia = 0.83;
    a1.stroke = true;
    a2.stroke = false;
    a3.stroke = false;
    a4.stroke = true;
    a5.stroke = false;
    nuevaLista(&lista);
    insertar(&lista, a1);
    insertar(&lista, a2);
    insertar(&lista, a3);
    insertar(&lista, a4);
    insertar(&lista, a5);

    while(!esNulaLista(lista)){
            printf("Distancia: %f   Caso: %d\n", lista.ini->elemento.distancia, (int)lista.ini->elemento.stroke);
            eliminarMenor(&lista);
        }
    return(0);
}
