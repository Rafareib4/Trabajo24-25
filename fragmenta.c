#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char ** fragmenta(const char * cadena){
    char ** arg, *copia, *token;
    int i=1;
    copia =(char *)malloc((strlen(cadena)+1)*sizeof(char));
    strcpy(copia, cadena);
    token = strtok(copia, ",");
    while(token != NULL){
        if (strlen(token) > 0){
            i++;
        }
        token = strtok(NULL, ",");
    }
    arg = (char**) malloc(i*sizeof(char*));
    token = strtok((char *)cadena, ",");
    i = 0;
    while(token != NULL){
        if (strlen(token) > 0){
            arg[i] = (char *)malloc((strlen(token)+1)*sizeof(char));
            strcpy(arg[i], token);
            i++;
        }
        token = strtok(NULL, ",");
    }
    return arg;
}
void borrarg(char **arg){
    int i = 0;
    while(arg[i] != NULL){
        free(arg[i]);
        i++;
    }
    free(arg);
}
