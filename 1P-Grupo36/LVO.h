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

int isEmptyLVO(Lvo lista){
    return(lista.acc == lista.fin);
}

int isFullLvo(Lvo lista){
    return(lista.acc != lista.cur && lista.cur == lista.fin);
}

void forwardsLvo(Lvo *lista){
    lista->aux = lista->cur;
    lista->cur = lista->cur->siguiente;
}

int localizarLvo(Lvo *lista, int x){
    resetLVO(lista);

    while(getPadronDNI((lista->cur->dato)) < x){     //Como la lista tiene de terminacion +infinito, nunca se pasa de largo ni chequea esta misma ("!=" Prohibido ya que si llega al lista->fin, este no seria igual)
            forwardsLvo(lista);
          }

    if(getPadronDNI((lista->cur->dato)) == x){
        return 1;
    }else{
        return 0;
    }
}

int alta(Lvo *lista, Padron p){
    //FUNCION DE COSTOOO (hay q hacer xd)

    if(localizarLvo(lista, getPadronDNI(p))){
            //EL DNI YA EXISTE
        if(){
            //N-TUPLA REPETIDA
        }else{
            //SOLO SE REPITE EL DNI
        }
    }else{
        //NO EXISTE EL DNI, SE DA DE ALTA
        Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));
        if(isFullLvo(*lista) || nuevo == NULL){
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
            return 1; //YEY
        }
    }
}

#endif // LVO_H_INCLUDED
