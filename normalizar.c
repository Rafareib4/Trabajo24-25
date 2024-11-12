#include "normalizar.h"

//Acción para encontrar los valores mínimos y máximos para la glucosa, bmi y edad
void calcularMaxYMin(Datos caballos[], MaxYMin* maximos_minimos, int num_caballos){

    maximos_minimos->minTemperaturaRectal = caballos[0].temperaturaRectal, maximos_minimos->maxTemperaturaRectal = caballos[0].temperaturaRectal;
    maximos_minimos->minPulso = caballos[0].pulso, maximos_minimos->maxPulso = caballos[0].pulso;
    maximos_minimos->minFrecuenciaResp = caballos[0].frecuenciaRespiracion, maximos_minimos->maxFrecuenciaResp = caballos[0].frecuenciaRespiracion;
    maximos_minimos->minVolumenCelulas = caballos[0].volumenCelulas, maximos_minimos->maxVolumenCelulas = caballos[0].volumenCelulas;
    maximos_minimos->minProteina = caballos[0].proteina, maximos_minimos->maxProteina = caballos[0].proteina;

    for (int i = 0; i < num_caballos; i++){
        if (caballos[i].temperaturaRectal < maximos_minimos->minTemperaturaRectal){
            maximos_minimos->minTemperaturaRectal = caballos[i].temperaturaRectal;
        }
        if (caballos[i].temperaturaRectal > maximos_minimos->maxTemperaturaRectal){
            maximos_minimos->maxTemperaturaRectal = caballos[i].temperaturaRectal;`
        }
        if (caballos[i].pulso < maximos_minimos->minPulso){
            maximos_minimos->minPulso = caballos[i].pulso;
        }
        if (caballos[i].pulso > maximos_minimos->maxPulso){
            maximos_minimos->maxPulso = caballos[i].pulso;
        }
        if (caballos[i].frecuenciaRespiracion < maximos_minimos->minFrecuenciaResp){
            maximos_minimos->minFrecuenciaResp = caballos[i].frecuenciaRespiracion;
        }
        if (caballos[i].frecuenciaRespiracion > maximos_minimos->maxFrecuenciaResp){
            maximos_minimos->maxFrecuenciaResp = caballos[i].frecuenciaRespiracion;
        }
        if (caballos[i].volumenCelulas < maximos_minimos->minVolumenCelulas){
            maximos_minimos->minVolumenCelulas = caballos[i].volumenCelulas;
        }
        if (caballos[i].volumenCelulas > maximos_minimos->maxVolumenCelulas){
            maximos_minimos->maxVolumenCelulas = caballos[i].volumenCelulas;
        }
        if (caballos[i].proteina < maximos_minimos->minProteina){
            maximos_minimos->minProteina = caballos[i].proteina;
        }
        if (caballos[i].proteina > maximos_minimos->maxProteina){
            maximos_minimos->maxProteina = caballos[i].proteina;
        }
    }
}

//Acción para normalizar los datos
void normalizeData(Datos caballos[], int num_caballos) {

    MaxYMin maximos_minimos;
    calcularMaxYMin(caballos, &maximos_minimos, num_caballos);
    for (int i = 0; i < num_caballos; i++) {
        caballos[i].temperaturaRectal = (caballos[i].temperaturaRectal - maximos_minimos.minTemperaturaRectal) / (maximos_minimos.maxTemperaturaRectal - maximos_minimos.minTemperaturaRectal);
        caballos[i].pulso = (caballos[i].pulso - maximos_minimos.minPulso) / (maximos_minimos.maxPulso - maximos_minimos.minPulso);
        caballos[i].frecuenciaRespiracion = (caballos[i].frecuenciaRespiracion - maximos_minimos.minFrecuenciaResp) / (maximos_minimos.maxFrecuenciaResp - maximos_minimos.minFrecuenciaResp);
        caballos[i].volumenCelulas = (caballos[i].volumenCelulas - maximos_minimos.minVolumenCelulas) / (maximos_minimos.maxVolmmenCelulas-maximos_minimos.minVolumenCelulas);
        caballos[i].proteina = (caballos[i].proteina - maximos_minimos.minProteina) / (maximos_minimos.maxProteina-maximos_minimos.minProteina);
    }
}
