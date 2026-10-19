#ifndef RAL_H_INCLUDED
#define RAL_H_INCLUDED
#define M_RAL 2539     //(2000/0.79 = 2531,64 | Techo(2531.64) = 2532 | Primo(2532) = 2539)
#include "padron.h"

typedef struct{
    Padron dato;
    char estado;    //(* = VIRGEN | - = LIBRE | O = OCUPADO)
}celdaRAL;

typedef struct{
    celdaRAL rebalse[M_RAL];
    int cant;
}RAL;

void initRAL(RAL *r){
    int i;
    r->cant = 0;
    for(i = 0; i < M_RAL; i++){
        r->rebalse[i].estado = '*';
    }
}

int localizarRAL(RAL *r, int x, int *pos, int *costo){
    *costo = 0;
    int posBase = hashing(x, M_RAL);
    int i;
    int celdaLibre = -1;

    for(i = 0; i < M_RAL; i++){
        int posAux = (posBase + i)%M_RAL;
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
    }

    *pos = celdaLibre;
    return 0;
}

int altaRAL(RAL *ral, Padron p, int *costo) {
    *costo = 0;
    int pos;

    if (localizarRAL(ral, p.dni, &pos, costo)) {
        return 0; //Ya existe
    } else {
        if (pos != -1) {
            ral->rebalse[pos].dato = p;
            ral->rebalse[pos].estado = 'O';
            ral->cant++;
            return 1;
        }
    }
    return 0;
}

int bajaRAL(RAL *r, Padron p, int *costo){
    *costo = 0;
    int pos;

    if(!localizarRAL(r, p.dni, &pos, costo))
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

#endif // RAL_H_INCLUDED
