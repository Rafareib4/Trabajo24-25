#include <stdlib.h>
#include <stdio.h>
#include "listaDistanciasMinimas.h"

void nuevaLista(tipoLista *lista){
    lista->ini = NULL;
    lista->fin = NULL;
}

void insertar(tipoLista *lista, distanciaYCaso elemento){
    celdaLista* nuevo;
    distanciaYCaso aux;
    nuevo = (celdaLista*)malloc(sizeof(celdaLista));
    nuevo->elemento = elemento;
    nuevo->sig = NULL;
    nuevo->ant = NULL;
    if(esNulaLista(*lista)){
        lista->ini = nuevo;
        lista->fin = nuevo;
    }
    else{
        nuevo->sig = lista->ini;
        lista->ini->ant = nuevo;
        lista->ini = nuevo;
        // NOTA: en el bucle primero se verifica nuevo->sig != NULL, porque si no estaríamos accediendo a memoria no válida
        while(nuevo->sig != NULL && nuevo->elemento.distancia > nuevo->sig->elemento.distancia){
            aux = nuevo->elemento;
            nuevo->elemento = nuevo->sig->elemento;
            nuevo->sig->elemento = aux;
            nuevo = nuevo->sig;
        }
    }
}

bool esNulaLista(tipoLista lista){
    return(lista.ini == NULL);
}

void eliminarMenor(tipoLista *lista){
    if(esNulaLista(*lista)){
        perror("ERROR: eliminando en lista nula\n");
    }
    else{
        celdaLista* aux;
        if(lista->ini->sig == NULL){
            aux = lista->ini;
            lista->ini = NULL;
            lista->fin = NULL;
            free(aux);
        }
        else{
            aux = lista->ini;
            lista->ini->sig->ant = NULL;
            lista->ini = lista->ini->sig;
            aux->sig = NULL;
            free(aux);
        }
    }
}

void eliminarTodosLosElementos(tipoLista *lista){
    if(esNulaLista(*lista)){
        perror("ERROR: eliminando en lista nula\n");
    }
    else{
        while(!esNulaLista(*lista)){
            eliminarMenor(lista);
        }
    }
}
