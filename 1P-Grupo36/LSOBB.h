#ifndef LSOBB_H_INCLUDED
#define LSOBB_H_INCLUDED

#include "padron.h"
#define MAX 2000

typedef struct{
    Padron datosLSO[MAX];
    int vectorM[MAX];  //marca si una celda ya fue consultada (1) o no (0) para el costo
    int cantidadElem;
    int cursor;
}listaSO;

void initLSO(listaSO *lso){
    lso->cantidadElem = 0;
    lso->cursor = 0;
    int i;
    for(i = 0; i < MAX; i++){       //inicia en 0 todo
        lso->vectorM[i] = 0;
    }
}

int isFullLSO(listaSO lso){
    return lso.cantidadElem >= MAX;     //si esta llena devuelve 1 sino 0
}

int isEmptyLSO(listaSO lso){            //si esta vacia devuelve 1 sino 0
    return lso.cantidadElem == 0;
}

void resetLSO(listaSO *lso){
    lso->cursor = 0;
}

void forwardsLSO(listaSO *lso){
    lso->cursor++;
}

int isOosLSO(listaSO lso){
    return lso.cursor >= lso.cantidadElem;
}


void limpiarMarcasLSO(listaSO *lso){
    int i;
    for(i = 0; i < lso->cantidadElem; i++) {
        lso->vectorM[i] = 0;
    }
}

int localizarLSO(listaSO *lso, int dni, float *costoCelda){
    *costoCelda = 0.0f;

    if(isEmptyLSO(*lso)){
        lso->cursor = 0;
        return 0;
    }

    int dniAux;
    int li = 0;
    int ls = lso->cantidadElem - 1;
    int m;

    limpiarMarcasLSO(lso);

    while(li < ls){
        m = (li + ls)/ 2;   //biseccion creo

        if(lso->vectorM[m] == 0){      //si no fue consultada suma al costo
            *costoCelda += 1.0f;          //la consulta c/u cuesta 1
            lso->vectorM[m] = 1;
        }

        dniAux = getPadronDNI(lso->datosLSO[m]);

        if(dniAux < dni)
            li = m + 1;
        else
            ls = m ;
    }

    if(lso->vectorM[li] == 0){          //(ls == li)
        *costoCelda += 1.0f;
        lso->vectorM[li] = 1;
    }

    //Vamos a chequear si el ultimo que quedo es igual al dni que estoy buscando
    dniAux = getPadronDNI(lso->datosLSO[li]);       //(ls == li)

    if (dniAux == dni){
        lso->cursor = li;
        return 1;       //Exito

    }else{

        //Mantengo el orden de la lista
        if (dni < dniAux){
            lso->cursor = li;
        }else{
            lso->cursor = li + 1;
        }
        return 0;           //fracaso :(
    }
}

int altaLSO(listaSO *lso, Padron p, float *costoCelda){
    int i;
    *costoCelda = 0.0f;
    float costoLocLSO = 0.0f;

    //CASO FRACASO

    if(isFullLSO(*lso))return 0;               //no hay espacio pue

    if(localizarLSO(lso, getPadronDNI(p), &costoLocLSO)){
        return 0;                           //ya existe el dni asi que chau
    }else{
        //CASO EXITO
        for(i = lso->cantidadElem; i > lso->cursor; i--){
            lso->datosLSO[i] = lso->datosLSO[i-1];
            //lso->vectorM[i] = lso->vectorM[i-1];
            *costoCelda += 1.0f;
        }                           //corrimiento derecha y suma el costo

        lso->datosLSO[lso->cursor] = p;     //se inserta el elemento nuevo en la posicion
        lso->vectorM[lso->cursor] = 0;      //se marca como no conmsultadp
        lso->cantidadElem++;        //y bueno suma xd

        return 1;
    }

}


int bajaLSO(listaSO *lso, Padron p, float *costoCelda){
    int i;
    *costoCelda = 0.0f;
    float costoLocLSO = 0.0f;


    if(localizarLSO(lso, getPadronDNI(p), &costoLocLSO)){
        if(padronIguales(lso->datosLSO[lso->cursor], p)){
            for(i = lso->cursor; i < (lso->cantidadElem - 1); i++){
                lso->datosLSO[i] = lso->datosLSO[i+1];
                //lso->vectorM[i] = lso->vectorM[i+1];
                *costoCelda += 1.0f;
            }
            //corrimiento izq y suma costo

            lso->cantidadElem--;                //actualizo la cantidad de elementos que tengo
            return 1;           //EXITO
        }else
            return 0;           //FRACASO. no coincide
    }else
        return 0;               //FRACASO. no encuentra dni
}

int evocacionLSO(listaSO *lso, int dni, Padron *p, float *costoCelda){
    *costoCelda = 0.0f;
    float costoLocLSO = 0.0f;

    //CASO EXTIO (se busca y recupero datos de nupla)
    if(localizarLSO(lso, dni, &costoLocLSO)){
        *costoCelda += costoLocLSO;
        *p = lso->datosLSO[lso->cursor];
        return 1;
    }else{
        //CASO FRACASO (no existe la nupla)
        *costoCelda += costoLocLSO;
        return 0;}
}

#endif // LSOBB_H_INCLUDED
