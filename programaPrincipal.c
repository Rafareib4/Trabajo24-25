#include <stdio.h>
#include "fragmenta.h"
#include <string.h>
#include <stdlib.h>
#include "listaDatos.h"
#include "maxMonticulo.h"
#include <math.h>
#include <unistd.h>
#define MAX 999999

typedef struct compFinal{
    int cant;
    float distMin;
}compFinal;

void normalizar(Datos* datos)
{
    datos->edad = (datos->edad - 15) / (22 - 15);
    datos->tiempoEstudios = (datos->tiempoEstudios - 1) / (4 - 1);
    datos->suspensos = (datos->suspensos - 0) / (3 - 0);
    datos->relacionFam = (datos->relacionFam - 1) / (5 - 1);
    datos->tiempoLibre = (datos->tiempoLibre - 1) / (5 - 1);
    datos->vidaSocial = (datos->vidaSocial - 1) / (5 - 1);
    datos->alcoholNoFinde= (datos->alcoholNoFinde - 1) / (5 - 1);
    datos->salud = (datos->salud - 1) / (5 - 1);
}

void meterDatosStruct (Datos* datos, char** fg)
{
    datos->sexo = *fg[0];
    datos->edad = atoi(fg[1]);
    datos->donde = *fg[2];
    strcpy(datos->tamañoFam, fg[3]);
    datos->situacionPadres = *fg[4];
    strcpy(datos->trabajoM, fg[5]);
    strcpy(datos->trabajoP, fg[6]);
    strcpy(datos->tutor, fg[7]);
    datos->tiempoEstudios = atoi(fg[8]);
    datos->suspensos = atoi(fg[9]);
    strcpy(datos->apoyoFam, fg[10]);
    strcpy(datos->actividades, fg[11]);
    strcpy(datos->enfermeria, fg[12]);
    strcpy(datos->internet, fg[13]);
    strcpy(datos->pareja, fg[14]);
    datos->relacionFam = atoi(fg[15]);
    datos->tiempoLibre = atoi(fg[16]);
    datos->vidaSocial = atoi(fg[17]);
    datos->alcoholNoFinde = atoi(fg[18]);
    datos->alcoholFinde = atoi(fg[19]);
    datos->salud = atoi(fg[20]);
}


float calcularDistancia(Datos dato, celdaLista* celda)
{
    float total;
    total = 0;
    if (dato.sexo != celda->elem.sexo)
    {
        total += 1 * 1;
    }
    total += (dato.edad - celda->elem.edad) * (dato.edad - celda->elem.edad);
    if (dato.donde != celda->elem.donde)
    {
        total += 1 * 1;
    }
    if (strcmp(dato.tamañoFam, celda->elem.tamañoFam) != 0)
    {
        total += 1 * 1;
    }
    if (dato.situacionPadres != celda->elem.situacionPadres)
    {
        total += 1 * 1;
    }
    if (strcmp(dato.trabajoM, celda->elem.trabajoM) != 0)
    {
        total += 1 * 1;
    }
    if (strcmp(dato.trabajoP, celda->elem.trabajoP) != 0)
    {
        total += 1 * 1;
    }
    if (strcmp(dato.tutor, celda->elem.tutor) != 0)
    {
        total += 1 * 1;
    }
    total += (dato.tiempoEstudios - celda->elem.tiempoEstudios) * (dato.tiempoEstudios - celda->elem.tiempoEstudios);
    total += (dato.suspensos - celda->elem.suspensos) * (dato.suspensos - celda->elem.suspensos);
    if (strcmp(dato.apoyoFam, celda->elem.apoyoFam) != 0)
    {
        total += 1 * 1;
    }
    if (strcmp(dato.actividades, celda->elem.actividades) != 0)
    {
        total += 1 * 1;
    }
    if (strcmp(dato.enfermeria, celda->elem.enfermeria) != 0)
    {
        total += 1 * 1;
    }
    if (strcmp(dato.internet, celda->elem.internet) != 0)
    {
        total += 1 * 1;
    }
    if (strcmp(dato.pareja, celda->elem.pareja) != 0)
    {
        total += 1 * 1;
    }
    total += (dato.relacionFam - celda->elem.relacionFam) * (dato.relacionFam - celda->elem.relacionFam);
    total += (dato.tiempoLibre - celda->elem.tiempoLibre) * (dato.tiempoLibre - celda->elem.tiempoLibre);
    total += (dato.vidaSocial - celda->elem.vidaSocial) * (dato.vidaSocial - celda->elem.vidaSocial);
    total += (dato.salud - celda->elem.salud) * (dato.salud - celda->elem.salud);

    return sqrtf(total);
}

void compararK1todos(tipoLista* lista)
{
    celdaLista* aComparar;
    celdaLista* recorrido;

    aComparar = lista -> ini; //Ponemos el puntero al primer elemento de la lista
    float alcoholMinimo, distanciaMinima, distancia2, alcoholAComparar, total, acertados, fallos, porcentaje;
    distanciaMinima = MAX;
    total = 0;
    acertados = 0;

    while (aComparar != lista -> fin)
    {
        distanciaMinima = MAX;

        alcoholAComparar = aComparar -> elem.alcoholFinde; //Recogemos en esta variable el valor que queremos acertar
        recorrido = lista -> ini;

        while(recorrido != lista -> fin)
        {
            if(recorrido != aComparar) //Para no compararlo consigo mismo
            {
                distancia2 = calcularDistancia(recorrido -> elem, aComparar);

                if(distanciaMinima > distancia2)
                {
                    distanciaMinima = distancia2;
                    alcoholMinimo = recorrido->elem.alcoholFinde;
                }
            }
            recorrido = recorrido -> sig;
        }
        printf("\n\nLa distancia  es de %0.5f, el alcohol de los findes de ese dato es de %0.0f y el que predecimos es de %0.0f\n", distanciaMinima, alcoholAComparar, alcoholMinimo);

        if(alcoholMinimo == alcoholAComparar)
        {
            total++;
            acertados++;
        }
        else
        {
            total++;
        }
        aComparar = aComparar -> sig;
    }

    fallos = total - acertados;
    printf("\nTOTAL: %0.0f, ACERTADOS: %0.0f, FALLOS: %0.0f\n",total,acertados,fallos);
    porcentaje = (acertados / total) * 100;
    printf("%f%% de acierto\n", porcentaje);
}

float compararKNN(tipoLista* lista, int num, bool escribir)
{
    celdaLista* aComparar;
    celdaLista* recorrido;

    aComparar = lista -> ini; //Ponemos el puntero al primer elemento de la lista
    int alcoholMinimo, alcoholAComparar;
    float distancia2, porcentaje, total, acertados, fallos;
    total = 0;
    acertados = 0;

    tipoMaxMonticulo mon;
    tipoElementoMaxMonticulo tupla;
    nuevoMaxMonticulo(&mon,num);


    while (aComparar != lista -> fin)
    {
        tupla.distancia = MAX;
        tupla.alcohol = MAX;
        while (!esVacio(mon)) //Vaciamo el monticulo y
        {
            eliminarElemento(&mon);
        }
        while (!estaLleno(mon)) //Lo llenamos de distancias maximas
        {
            insertarMaxMonticulo(&mon,tupla);
        }

        alcoholAComparar = aComparar -> elem.alcoholFinde; //Recogemos en esta variable el valor que queremos acertar
        recorrido = lista -> ini;

        while(recorrido != lista -> fin)
        {
            if(recorrido != aComparar)
            {
                distancia2 = calcularDistancia(recorrido -> elem, aComparar);

                if(devolverRaiz(mon).distancia > distancia2)//Si la mayor distancia del monticulo es mayor que la nuestra, metemos nuestro dato
                {
                    eliminarElemento(&mon);
                    tupla.distancia = distancia2;
                    tupla.alcohol = recorrido->elem.alcoholFinde;
                    insertarMaxMonticulo(&mon, tupla);
                }
            }
            recorrido = recorrido -> sig;
        }
        if(escribir == true) //Para printear o no
        {
            printf("\n\nEl alcohol que buscamos es de %d ", alcoholAComparar);
        }

        compFinal cantidades[5]; //Array de 5 huecos en la que guardaremos la cantidad que acierta de cada tipo(entre 1/5) y la distancia mínima a través del struct compFinal
        cantidades[0].cant = 0;
        cantidades[0].distMin = MAX;
        cantidades[1].cant = 0;
        cantidades[1].distMin = MAX;
        cantidades[2].cant = 0;
        cantidades[2].distMin = MAX;
        cantidades[3].cant = 0;
        cantidades[3].distMin = MAX;
        cantidades[4].cant = 0;
        cantidades[4].distMin = MAX;

        int i;
        for(i = 0; i < mon.pos; i++) //Sumamos la cantidad de variables y guardamos distancias minimas
        {
            if (mon.array[i].alcohol == 1)
            {
                cantidades[0].cant++;
                if (mon.array[i].distancia < cantidades[0].distMin)
                {
                    cantidades[0].distMin = mon.array[i].distancia;
                }
            }
            else if (mon.array[i].alcohol == 2)
            {
                cantidades[1].cant++;
                if (mon.array[i].distancia < cantidades[1].distMin)
                {
                    cantidades[1].distMin = mon.array[i].distancia;
                }
            }
            else if (mon.array[i].alcohol == 3)
            {
                cantidades[2].cant++;
                if (mon.array[i].distancia < cantidades[2].distMin)
                {
                    cantidades[2].distMin = mon.array[i].distancia;
                }
            }
            else if (mon.array[i].alcohol == 4)
            {
                cantidades[3].cant++;
                if (mon.array[i].distancia < cantidades[3].distMin)
                {
                    cantidades[3].distMin = mon.array[i].distancia;
                }
            }
            else if (mon.array[i].alcohol == 5)
            {
                cantidades[4].cant++;
                if (mon.array[i].distancia < cantidades[4].distMin)
                {
                    cantidades[4].distMin = mon.array[i].distancia;
                }
            }
        }
        alcoholMinimo = 0;
        for(i = 1; i < 5; i++) //Guardamos el alcohol del que tenga mayor cantidad, en caso de empate el de menor distancia
        {
            if (cantidades[alcoholMinimo].cant < cantidades[i].cant)
            {
                alcoholMinimo = i;
            }
            else if (cantidades[alcoholMinimo].cant == cantidades[i].cant)
            {
                if (cantidades[alcoholMinimo].distMin > cantidades[i].distMin)
                {
                    alcoholMinimo = i;
                }
            }
        }

        alcoholMinimo++;
        if(escribir == true)
        {
            printf("y el alcohol que predecimos es de %d\n", alcoholMinimo);
        }
        if(alcoholMinimo == alcoholAComparar)
        {
            total++;
            acertados++;
        }
        else
        {
            total++;
        }
        aComparar = aComparar -> sig;
    }

    fallos = total - acertados;
    if(escribir == true)
    {
        printf("\nTOTAL: %0.0f, ACERTADOS: %0.0f, FALLOS: %0.0f\n",total,acertados,fallos);
    }
    porcentaje = (acertados / total) * 100;
    if(escribir == true)
    {
        printf("%f%% de acierto\n", porcentaje);
    }
    return(porcentaje);
}

void compararKNNyAnadirANuevaLista(tipoLista* listaAdevolver,tipoLista *lista,int mejork) //Igual que el anterior salvo el final (comentado)
{
    celdaLista* aComparar;
    celdaLista* recorrido;

    aComparar = lista -> ini;
    int alcoholMinimo, alcoholAComparar;
    float distancia2, total, acertados;
    total = 0;
    acertados = 0;

    tipoMaxMonticulo mon;
    tipoElementoMaxMonticulo tupla;
    nuevoMaxMonticulo(&mon,mejork);


    while (aComparar != lista -> fin)
    {
        tupla.distancia = MAX;
        tupla.alcohol = MAX;
        while (!esVacio(mon))
        {
            eliminarElemento(&mon);
        }
        while (!estaLleno(mon)) //Llenamos el monticulo de distancias maximas
        {
            insertarMaxMonticulo(&mon,tupla);

        }

        alcoholAComparar = aComparar -> elem.alcoholFinde;
        recorrido = lista -> ini;

        while(recorrido != lista -> fin)
        {
            if(recorrido != aComparar)
            {
                distancia2 = calcularDistancia(recorrido -> elem, aComparar);


                if(devolverRaiz(mon).distancia > distancia2)
                {
                    eliminarElemento(&mon);
                    tupla.distancia = distancia2;
                    tupla.alcohol = recorrido->elem.alcoholFinde;
                    insertarMaxMonticulo(&mon, tupla);
                }
            }
            recorrido = recorrido -> sig;
        }
        compFinal cantidades[5];
        cantidades[0].cant = 0;
        cantidades[0].distMin = MAX;
        cantidades[1].cant = 0;
        cantidades[1].distMin = MAX;
        cantidades[2].cant = 0;
        cantidades[2].distMin = MAX;
        cantidades[3].cant = 0;
        cantidades[3].distMin = MAX;
        cantidades[4].cant = 0;
        cantidades[4].distMin = MAX;

        int i;
        for(i = 0; i < mon.pos; i++)
        {
            if (mon.array[i].alcohol == 1)
            {
                cantidades[0].cant++;
                if (mon.array[i].distancia < cantidades[0].distMin)
                {
                    cantidades[0].distMin = mon.array[i].distancia;
                }
            }
            else if (mon.array[i].alcohol == 2)
            {
                cantidades[1].cant++;
                if (mon.array[i].distancia < cantidades[1].distMin)
                {
                    cantidades[1].distMin = mon.array[i].distancia;
                }
            }
            else if (mon.array[i].alcohol == 3)
            {
                cantidades[2].cant++;
                if (mon.array[i].distancia < cantidades[2].distMin)
                {
                    cantidades[2].distMin = mon.array[i].distancia;
                }
            }
            else if (mon.array[i].alcohol == 4)
            {
                cantidades[3].cant++;
                if (mon.array[i].distancia < cantidades[3].distMin)
                {
                    cantidades[3].distMin = mon.array[i].distancia;
                }
            }
            else if (mon.array[i].alcohol == 5)
            {
                cantidades[4].cant++;
                if (mon.array[i].distancia < cantidades[4].distMin)
                {
                    cantidades[4].distMin = mon.array[i].distancia;
                }
            }
        }
        alcoholMinimo = 0;
        for(i = 1; i < 5; i++)
        {
            if (cantidades[alcoholMinimo].cant < cantidades[i].cant)
            {
                alcoholMinimo = i;
            }
            else if (cantidades[alcoholMinimo].cant == cantidades[i].cant)
            {
                if (cantidades[alcoholMinimo].distMin > cantidades[i].distMin)
                {
                    alcoholMinimo = i;
                }
            }
        }

        alcoholMinimo++;
        if(alcoholMinimo == alcoholAComparar)
        {
            total++;
            acertados++;
            insertar(listaAdevolver,aComparar -> elem); //El unico cambio es que insertamos en una nueva lista los valores que acierta
        }
        else
        {
            total++;
        }
        aComparar = aComparar -> sig;
    }

    printf("%0.0f\n",acertados);

}


tipoLista wilson(tipoLista* lista, int mejork)
{
    tipoLista listaAdevolver;
    compararKNNyAnadirANuevaLista(&listaAdevolver,lista,mejork);
    eliminarLista(lista);
    return(listaAdevolver);
}

int main (void)
{
    FILE* f;
    char buffer1[100];
    char **fg;
    int input, numMon;
    float porcentajeKNN;

    char cont;

    struct Datos datos;
    struct Datos dato;

    tipoLista lista;
    nuevaLista(&lista);
    normalizar(&dato);

    f = fopen("student-mat.csv", "r");
    fgets(buffer1, 100, f);

    fg = fragmenta(buffer1);

    meterDatosStruct(&datos, fg);

    normalizar(&datos);

    insertar(&lista, datos);

    borrarg(fg);

    while (fgets(buffer1, 100, f) != NULL)
    {
        fg = fragmenta(buffer1);

        meterDatosStruct(&datos, fg);

        normalizar(&datos);

        insertar(&lista, datos);

        borrarg(fg);
    }
    do
    {
        printf("¿Que quieres hacer? (1 para k=1, 2 para k=1 con todos y 3 para kNN, 4 para hacer wilson con la mejor k y 5 para el valor de k que quieras (wilson)): ");
        scanf("%d", &input);
        if (input == 2)
        {
            compararK1todos(&lista);
        }
        else if (input == 3)
        {
            printf("¿Con cuantos número quieres comparar?");
            scanf("%d", &numMon);
            porcentajeKNN = compararKNN(&lista, numMon,true);
        }
        else if(input == 4)
        {
            printf("Calculando el mejor K-vecinos\n");
            float mejorPorcentaje;
            int mejorK;
            porcentajeKNN = compararKNN(&lista, 1,false);
            mejorPorcentaje = porcentajeKNN;
            mejorK = 1;
            for(int i = 2; i < 98; i++) //A partir de 98 todos los porcentajes son costantes y no cambian, por tanto, no merece la pena compararlos
            {
                porcentajeKNN = compararKNN(&lista, i,false);
                if(mejorPorcentaje < porcentajeKNN)
                {
                    mejorPorcentaje = porcentajeKNN;
                    mejorK = i;
                }
            }
            printf("Porcentaje: %f%% Mejor-k vecinos: %i\n",mejorPorcentaje,mejorK);
            sleep(3);//para que se pueda leer
            printf("Procedemos a hacer Wilson\n");
            lista = wilson(&lista,mejorK);
            imprimirLista(lista);
        }
        else if(input == 5)
        {
            printf("¿Con cuantos número quieres comparar?");
            scanf("%d", &numMon);
            lista = wilson(&lista,numMon);
            imprimirLista(lista);
        }
        printf("Quiere continuar?(s/n)");
        scanf(" %c",&cont);
    }
    while(cont == 's');
}
