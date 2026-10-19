#ifndef RAC_H_INCLUDED
#define RAC_H_INCLUDED
#define M_RAC 2411     //(2000/0.83 = 2409.64 | Techo(2409.64) = 2410 | Primo(2410) = 2411)
#include "padron.h"

typedef struct{
    Padron dato;
    char estado;    //(* = VIRGEN | - = LIBRE | O = OCUPADO)
}celdaRAC;

typedef struct{
    celdaRAC rebalse[M_RAC];
    int cant;
}RAC;

void initRAC(RAC *r){
    int i;
    r->cant = 0;
    for(i = 0; i < M_RAC; i++){
        r->rebalse[i].estado = '*';
    }
}

int localizarRAC(RAC *r, int x, int *pos, int *costo){
    *costo = 0;

    int posAux = hashing(x, M_RAC);
    int k = 1;
    int i;
    int celdaLibre = -1;

    for(i = 0; i < M_RAC; i++){
        (*costo)++;

        if(r->rebalse[posAux].estado == '-' && celdaLibre == -1){
            celdaLibre = posAux;
        }

        if(r->rebalse[posAux].estado == '*'){       //VIRGEN
            if(celdaLibre != -1)
                *pos = celdaLibre;
            else
                *pos = posAux;

            return 0;
        }

        if(r->rebalse[posAux].estado == 'O' && r->rebalse[posAux].dato.dni == x){
            *pos = posAux;
            return 1;
        }

        posAux = (posAux + k) % M_RAC;
        k++;
    }
    *pos = celdaLibre;
    return 0;
}

int altaRAC(RAC *r, Padron p, int *costo){
    *costo = 0;

    int pos;

    if(localizarRAC(r, p.dni, &pos, costo)){
        return 0;
    }else{
        if (pos != -1) {
            r->rebalse[pos].dato = p;
            r->rebalse[pos].estado = 'O';
            r->cant++;
            return 1;
        }
    }

    return 0;
}

int bajaRAC(RAC *r, Padron p, int *costo){
    *costo = 0;

    int pos;

    if(!localizarRAC(r, p.dni, &pos, costo))
        return 0;
    else{
        if(padronIguales(r->rebalse[pos].dato, p)){
            r->rebalse[pos].estado = '-';
            r->cant--;
            return 1;
        }
    }
    return 0;
}

#endif // RAC_H_INCLUDED
