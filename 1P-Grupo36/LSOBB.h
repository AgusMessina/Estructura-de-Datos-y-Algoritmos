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
    return lso.cantidadElem >= MAX;     //si está llena devuelve 1 sino 0
}

int isEmptyLSO(listaSO lso){            //si está vacia devuelve 1 sino 0
    return lso.cantidadElem == 0;
}

void resetLSO(listaSO *lso){
    lso->cursor = 0;
}

void forwardsLSO(listaSO *lso){
    lso->cursor++;
}

void isOosLSO(listaSO lso){
    return lso.cursor >= lso.cantidadElem;
}

int localizarLSO(listaSO *lso, int dni, int *pos, float *costoCelda){
    resetLSO(lso);
    *costoCelda = 0.0f;

    int li = 0;
    int ls = lso->cantidadElem - 1;
    int m;

    while(li <= ls){
        m = (li + ls + 1)/ 2;   //biseccion creo

        if(lso->vectorM[m] == 0){      //si no fue consultada suma al costo
            *costoCelda += 1.0f;          //la consulta c/u cuesta 1
            lso->vectorM[m] = 1;
        }

        int dniAux = getPadronDNI(lso->datosLSO[m]);
        if(dniAux == dni){
            *pos = m;
            return 1;       //encontró el dni (exito)
        }

        if(dniAux < dni)
            li = m + 1;
        else
            ls = m - 1;
    }
    *pos = li;
    return 0;                    //fracaso :(
}

int altaLSO(listaSO *lso, Padron p, float *costoCelda){
    int i, pos;
    *costoCelda = 0.0f;
    float costoLoc = 0.0f;

    //CASO FRACASO
    if(isFullLSO(*lso))return 0;               //no hay espacio pue

    if(localizarLSO(lso, getPadronDNI(p), &pos, &costoLoc)){
        *costoCelda += costoLoc;
        return 0;                           //ya existe el dni asi que chau
    }else{
        //CASO EXITO
        for(i = lso->cantidadElem; i > pos; i--){
            lso->datosLSO[i] = lso->datosLSO[i-1];
            lso->vectorM[i] = lso->vectorM[i-1];
            *costoCelda += 1.0f;
        }                           //corrimiento derecha y suma el costo

        lso->datosLSO[pos] = p;     //se inserta el elemento nuevo en la posicion
        lso->vectorM[pos] = 0;      //se marca como no conmsultadp
        lso->cantidadElem++;        //y bueno suma xd
        resetLSO(lso);              //reinicia cursor

        *costoCelda += costoLoc;
        return 1;
    }

}


int bajaLSO(listaSO *lso, Padron p, float *costoCelda){
    int i, pos;
    *costoCelda = 0.0f;
    float costoLocLSO = 0.0f;

    if(localizarLSO(lso, getPadronDNI(p), &pos, &costoLocLSO)){
        if(padronIguales(lso->datosLSO[pos], p)){
            for(i = pos; i < (lso->cantidadElem - 1); i++){
                lso->datosLSO[i] = lso->datosLSO[i+1];
                lso->vectorM[i] = lso->vectorM[i+1];
                *costoCelda += 1.0f;
            }
            *costoCelda += costoLocLSO;         //corrimiento izq y suma costo

            lso->cantidadElem--;                //actualizo la cantidad de elementos que tengo
            resetLSO(lso);
            return 1;           //EXITO
        }else
            *costoCelda += costoLocLSO;
            return 0;           //FRACASO. no coincide, suma costo igual
    }else
        //*costoCelda += costoLocLSO;
        return 0;               //FRACASO. no encuentra dni, suma igual(?
}

int evocacionLSO(listaSO *lso, int dni, Padron *p, float *costoCelda){
    int pos;
    *costoCelda = 0.0f;
    float costoLocLSO = 0.0f;

    //CASO EXTIO (se busca y recupero datos de nupla)
    if(localizarLSO(lso, dni, &pos, &costoLocLSO)){
        *costoCelda += costoLocLSO;
        *p = lso->datosLSO[pos];
        return 1;
    }else{
        //CASO FRACASO (no existe la nupla)
        *costoCelda += costoLocLSO;
        return 0;}
}

#endif // LSOBB_H_INCLUDED
