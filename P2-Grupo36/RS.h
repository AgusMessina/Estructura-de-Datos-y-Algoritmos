#ifndef RS_H_INCLUDED
#define RS_H_INCLUDED
#include <malloc.h>
#include "padron.h"
#define M_RS 1249  //(2000/1.61 = 1242.24 | Techo(1242.24) = 1243 | Primo(1243) = 1249)

typedef struct Nodo{
    Padron dato;
    struct Nodo *siguiente;
}Nodo;

/*
typedef struct{
    Nodo *acc;
    Nodo *cur;
    Nodo *aux;
}Lista;
*/

typedef struct{
    Nodo *rebalse[M_RS];
    int cant;
}RS;

void initRS(RS *r){
    int i;
    r->cant = 0;
    for(i = 0; i < M_RS; i++){
        r->rebalse[i] = NULL;
    }
}

int localizarRS(RS *r, int x, int *costo){
    *costo = 0;

    int posBase = hashing(x, M_RS);
    Nodo *pos = r->rebalse[posBase];

    (*costo)++;

    while(pos != NULL){
        if(pos->dato.dni == x)
            return 1;
        pos = pos->siguiente;

        if(pos != NULL)
            (*costo)++;
    }

    return 0;
}

int altaRS(RS *rs, Padron p, int *costo) {
    *costo = 0;

    // Delegamos la búsqueda de duplicados y la suma de costo a localizarRS
    if (localizarRS(rs, p.dni, costo)) {
        return 0; // El DNI ya existe, rechazamos el alta
    }

    // Si no existe, calculamos la posición y agregamos el nuevo nodo al inicio
    int pos = hashing(p.dni, M_RS);
    Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevo == NULL) return 0;

    nuevo->dato = p;
    nuevo->siguiente = rs->rebalse[pos];
    rs->rebalse[pos] = nuevo;

    rs->cant++;
    return 1;
}

int bajaRS(RS *r, Padron p, int *costo){
    *costo = 0;

    if(!localizarRS(r, p.dni, costo))
        return 0;
    else{
        int posBase = hashing(p.dni, M_RS);
        Nodo *actual = r->rebalse[posBase];
        Nodo *anterior = NULL;

        while(actual != NULL){
            if(actual->dato.dni == p.dni){
                if(padronIguales(actual->dato, p)){

                    if(anterior == NULL)
                        r->rebalse[posBase] = actual->siguiente;
                    else
                        anterior->siguiente = actual->siguiente;

                    free(actual);
                    r->cant--;
                    return 1;
                }else
                    return 0;
            }
            anterior = actual;
            actual = actual->siguiente;
        }
    }
    return 0;
}

#endif // RS_H_INCLUDED
