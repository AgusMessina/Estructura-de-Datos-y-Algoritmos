#ifndef LVO_H_INCLUDED
#define LVO_H_INCLUDED

#include "padron.h"
#define infinito 999999999

typedef struct Nodo{
    Padron dato;
    struct Nodo *siguiente;
}Nodo;

typedef struct{
    Nodo *acc;
    Nodo *cur;
    Nodo *aux;
    Nodo *fin;
}Lvo;

void initLVO(Lvo *lista){
    lista->fin = (Nodo*)malloc(sizeof(Nodo));

    setPadronDNI(&(lista->fin->dato), infinito);
    lista->fin->siguiente = lista->fin; // Nodo terminacion apunta a si mismo, que es NULL (recursividad rara lol)


    lista->acc = lista->fin;
    lista->cur = lista->fin;
    lista->aux = lista->fin;
}

void resetLVO(Lvo *lista){
    lista->cur = lista->acc;
    lista->aux = lista->acc;
}

int isOosLVO(Lvo lista){
    if(lista.cur == lista.fin)
        return 1;
    else
        return 0;
}

int isEmptyLVO(Lvo lista){
    return(lista.acc == lista.fin);
}

int isFullLvo(Lvo lista){
    return(lista.acc != lista.cur && lista.cur == NULL);
}

void forwardsLvo(Lvo *lista){
    lista->aux = lista->cur;
    lista->cur = lista->cur->siguiente;
}

int padronIguales(Padron a, Padron b) {
    if (getPadronDNI(a) != getPadronDNI(b))
        return 0;
    if (strcasecmp(getPadronNombreApe(a), getPadronNombreApe(b)) != 0)
        return 0;
    if (strcasecmp(getPadronDomicilio(a), getPadronDomicilio(b)) != 0)
        return 0;
    if (getPadronCodPostal(a) != getPadronCodPostal(b))
        return 0;
    if (getPadronMesa(a) != getPadronMesa(b))
        return 0;
    if (getPadronCircuito(a) != getPadronCircuito(b))
        return 0;

    return 1;
}

int localizarLvo(Lvo *lista, int x, float *costo){
    resetLVO(lista);
    *costo = 0.0f;

    while(getPadronDNI((lista->cur->dato)) < x){     //Como la lista tiene de terminacion +infinito, nunca se pasa de largo ni chequea esta misma ("!=" Prohibido ya que si llega al lista->fin, este no seria igual)
            *costo += 1.0f;
            forwardsLvo(lista);
          }

    *costo += 1.0f;

    if(getPadronDNI((lista->cur->dato)) == x){
        return 1;
    }else{
        return 0;
    }
}

int altaLvo(Lvo *lista, Padron p, float *costo){
    *costo = 0.0f;
    float costoLoc = 0.0f;

    if(localizarLvo(lista, getPadronDNI(p), &costoLoc)){
        *costo += costoLoc;
        return 0; //EXISTE EL DATO
    }else{
        *costo += costoLoc;
        //NO EXISTE EL DNI, SE DA DE ALTA
        if(isFullLvo(*lista)) return 0;

        Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));
        if(nuevo == NULL){
            return 0; //NO HAY ESPACIO :(
        }else{  //INGRESAR

            nuevo->dato = p;

            if(lista->acc == lista->cur){
                nuevo->siguiente = lista->acc;
                lista->acc = nuevo;
            }else{
                nuevo->siguiente = lista->cur;
                lista->aux->siguiente = nuevo;
            }

            *costo += 1.0f;     //0.5 + 0.5
            return 1; //YEY
        }
    }
}

int bajaLvo(Lvo *lista, Padron p, float *costo){
    *costo = 0.0f;
    float costoLoc = 0.0f;

    if(localizarLvo(lista, getPadronDNI(p), &costoLoc)){
        *costo += costoLoc;
        if(padronIguales(lista->cur->dato, p)){             //Chequea la tupla

            if(lista->acc == lista->cur){       //Borra en caso de que este primero
                lista->acc = lista->cur->siguiente;
                free((void*)lista->cur);
                lista->cur = lista->acc;
                lista->aux = lista->cur;
            }else{                              //Borra en caso de que este en el medio o final
                lista->aux->siguiente = lista->cur->siguiente;
                free((void*)lista->cur);
                lista->cur = lista->aux->siguiente;
            }

            *costo += 0.5f;
            return 1;   //EXITO

        }else{
            return 0;   //FRACASO ; No es la tupla que queremos borrar
        }
    }else{
        *costo += costoLoc;
        return 0;       //FRACASO ; No existe el elemento en la lista
    }
}

int evocacionLvo(Lvo *lista, float *costo, int dni, Padron *p){
    *costo = 0.0f;
    float costoLoc = 0.0f;

    if(localizarLvo(lista, dni, &costoLoc)){
        *costo += costoLoc;
        *p = lista->cur->dato;
        return 1;

    }else{

        *costo += costoLoc;
        return 0;
    }
}

#endif // LVO_H_INCLUDED
