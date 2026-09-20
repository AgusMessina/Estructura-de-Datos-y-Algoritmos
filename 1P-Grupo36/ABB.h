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
        return 0;               //Ya existe
    }else{
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
        return 0;                                       //No se encontro
    }else{
        if(!padronIguales(arbol->pos->dato, p)){
            return 0;                                   //No es la misma tupla
        }else{

            //Caso hoja (No tiene hijos)
            if(arbol->pos->der == NULL && arbol->pos->izq == NULL){

                //En caso de que sea la raiz
                if(arbol->padre != NULL){
                    if(arbol->padre->der == arbol->pos)
                        arbol->padre->der = NULL;
                    else
                        arbol->padre->izq = NULL;

                }else{
                    arbol->raiz = NULL;
                }

                *costo += 0.5f;
                free(arbol->pos);
                return 1;           //Exitoo
            }

            //Caso solo un hijo
            if(arbol->pos->der == NULL || arbol->pos->izq == NULL){
                NodoAbb *aux;

                if(arbol->pos->izq != NULL){
                    aux = arbol->pos->izq;     //Si tiene hijo a la izquierda, me quedo con ese
                }else{
                    aux = arbol->pos->der;     //Si no, el hijo que tiene es el derecho
                }

                if(arbol->padre == NULL){
                    arbol->raiz = aux;
                }else{
                    if(arbol->padre->der == arbol->pos)
                        arbol->padre->der = aux;
                    else
                        arbol->padre->izq = aux;
                }

                *costo += 0.5f;
                free(arbol->pos);
                return 1;           //EXITOOO
            }

            //Caso dos hijos (Se reemplaza por el menor de los maayores, por copia daatos

            NodoAbb *padreAux = arbol->pos;
            NodoAbb *menor = arbol->pos->der;          //Un pasito pa delante, pa delante

            while(menor->izq != NULL){                //Un pasito pa atra, pa atra
                padreAux = menor;
                menor = menor->izq;
            }

            arbol->pos->dato = menor->dato;
            *costo += 1.0f;

            if(padreAux == arbol->pos)
                padreAux->der = menor->der;
            else
                padreAux->izq = menor->der;

            *costo += 0.5f;
            free(menor);
            return 1;           //HAY QUE CERRAR EL ESTADIO
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
