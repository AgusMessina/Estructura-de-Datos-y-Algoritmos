#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED

#include "padron.h"

typedef struct NodoAbb{
    Padron dato;
    struct NodoAbb *izq;
    struct NodoAbb *der;
}NodoAbb;

typedef struct{
    NodoAbb *padre;     //Un aux
    NodoAbb *pos;       //Un cur
    NodoAbb *raiz;      //Un acc
}Abb;

void initABB(Abb *arbol){
    arbol->raiz = NULL;
    arbol->padre = NULL;
    arbol->pos = NULL;
}

int isEmptyABB(Abb arbol){
    return(arbol.raiz == NULL);
}

void resetABB(Abb *arbol){
    arbol->pos = arbol->raiz;
    arbol->padre = NULL;
}

int isOosABB(Abb arbol){
    return arbol.pos == NULL;
}

NodoAbb *nuevoNodoAbb(Padron p){
    NodoAbb *aux = (NodoAbb*)malloc(sizeof(NodoAbb));

    if(aux != NULL){
        aux->dato = p;
        aux->der = NULL;
        aux->izq = NULL;
    }
    return aux;
}

int localizarAbb(Abb *arbol, int x, float *costo){
    resetABB(arbol);
    *costo = 0.0f;

    while(!isOosABB(*arbol)){                           //Mientras no este vacio el arbol empieza a buscar
        *costo += 1.0f;

        if(getPadronDNI(arbol->pos->dato) == x){
            return 1;
        }else{

            arbol->padre = arbol->pos;
            if(getPadronDNI(arbol->pos->dato) < x)
                arbol->pos = arbol->padre->der;         //Si es menor va hacia la der
            else
                arbol->pos = arbol->padre->izq;         //Si es mayor va hacia la izq
        }
    }
    return 0;       //Fracaso
}

int altaAbb(Abb *arbol, Padron p, float *costo){
    *costo = 0.0f;
    float costoLoc = 0.0f;

    if(localizarAbb(arbol, getPadronDNI(p), &costoLoc)){
        *costo += costoLoc;
        return 0;               //Ya existe
    }else{
        *costo += costoLoc;
        NodoAbb *aux = nuevoNodoAbb(p);

        if(aux == NULL){
            return 0;       //No hay espacio
        }else{

            if(isEmptyABB(*arbol)){                                         //Primer nodo en ser dado de alta
                arbol->raiz = aux;
                *costo += 0.5f;
                return 1;
            }else{
                if(getPadronDNI(arbol->padre->dato) < getPadronDNI(p)){
                        arbol->padre->der = aux;         //Si es menor se da de alta a la derecha
                    }else{
                        arbol->padre->izq = aux;         //Si es menor se da de alta a la izquierda
                }

                *costo += 0.5f;
                return 1;
            }
        }
    }
}

int bajaAbb(Abb *arbol, Padron p, float *costo){
    *costo = 0.0f;
    float costoLoc = 0.0f;

    if(!localizarAbb(arbol, getPadronDNI(p), &costoLoc)){
        *costo += costoLoc;
        return 0;                                       //No se encontro
    }else{
        if(!padronIguales(arbol->pos->dato, p)){
            return 0;                                   //No es la misma tupla
        }else{

            //Caso hoja (No tiene hijos)
            if(arbol->pos->der == NULL && arbol->pos->izq == NULL){

                //En caso de que sea la raiz
                if(arbol->padre == NULL){

                }
            }
        }
    }

}

int evocacionAbb(Abb *arbol, float *costo, int x, Padron *p){
    *costo = 0.0f;
    float costoLoc = 0.0f;

    if(localizarAbb(arbol, x, &costoLoc)){
        *costo += costoLoc;
        *p = arbol->pos->dato;
        return 1;
    }else{
        *costo += costoLoc;
        return 0;
    }
}

#endif // ABB_H_INCLUDED
