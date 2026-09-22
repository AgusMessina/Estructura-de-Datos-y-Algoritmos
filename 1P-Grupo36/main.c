#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include <string.h>
#include <malloc.h>
#include "LVO.h"
#include "ABB.h"
//#include "LSOBB.h"


//--------------- VARIABLES COSTO (SON GLOBALES) ---------------


//ARBOL BINARIO
// ALTA
float costoAltaAcumABB = 0.0f;
float costoAltaMaxABB = 0.0f;
float cantAltaABB = 0.0f;
float costoAltaMedABB = 0.0f;

// BAJA
float costoBajaAcumABB = 0.0f;
float costoBajaMaxABB = 0.0f;
float cantBajaABB = 0.0f;
float costoBajaMedABB = 0.0f;

// EVOCACIÓN (Éxito y Fracaso)
// Éxito
float costoLocEABB = 0.0f;
float costoLocEMaxABB = 0.0f;
float cantEABB = 0.0f;
float costoLocEMedABB = 0.0f;

// Fracaso
float costoLocFABB = 0.0f;
float costoLocFMaxABB = 0.0f;
float cantFABB = 0.0f;
float costoLocFMedABB = 0.0f;

// ---------------


//LISTA SECUENCIAL ORDENADA
// ALTA
float costoAltaAcumLSO = 0.0f;
float costoAltaMaxLSO = 0.0f;
float cantAltaLSO = 0.0f;
float costoAltaMedLSO = 0.0f;

// BAJA
float costoBajaAcumLSO = 0.0f;
float costoBajaMaxLSO = 0.0f;
float cantBajaLSO = 0.0f;
float costoBajaMedLSO = 0.0f;

// EVOCACIÓN (Éxito y Fracaso)
// Éxito
float costoLocELSO = 0.0f;
float costoLocEMaxLSO = 0.0f;
float cantELSO = 0.0f;
float costoLocEMedLSO = 0.0f;

// Fracaso
float costoLocFLSO = 0.0f;
float costoLocFMaxLSO = 0.0f;
float cantFLSO = 0.0f;
float costoLocFMedLSO = 0.0f;

// ---------------


//LISTA VINCULADA ORDENADA
// ALTA
float costoAltaAcumLVO = 0.0f;
float costoAltaMaxLVO = 0.0f;
float cantAltaLVO = 0.0f;
float costoAltaMedLVO = 0.0f;

// BAJA
float costoBajaAcumLVO = 0.0f;
float costoBajaMaxLVO = 0.0f;
float cantBajaLVO = 0.0f;
float costoBajaMedLVO = 0.0f;

// EVOCACIÓN (Éxito y Fracaso)
// Éxito
float costoLocELVO = 0.0f;
float costoLocEMaxLVO = 0.0f;
float cantELVO = 0.0f;
float costoLocEMedLVO = 0.0f;

// Fracaso
float costoLocFLVO = 0.0f;
float costoLocFMaxLVO = 0.0f;
float cantFLVO = 0.0f;
float costoLocFMedLVO = 0.0f;


//--------------- FIN VARIABLES GLOBALES ---------------



//LISTA VINCULADA

void mostrarLvoPaginado(Lvo *l, int *aux) {
    while(getchar() != '\n'); //Consume un ENTER

    if(isEmptyLVO(*l)){
        printf("La lista esta vacia.\n");
        return;
    }

    resetLVO(l);
    int contador = 1;
    int pagina = 1;

    printf("\n--- PAGINA %d ---\n", pagina);

    //Recorre mientras no llegue al centinela
    while (!isOosLVO(*l)) {
        Padron p = l->cur->dato;

        //Imprime
        printf("[%d] ", contador); mostrarPadron(p); printf("\n");
        contador++;
        forwardsLvo(l);

        //Muestra 20 Elementos
        if(contador % 20 == 0 && !isOosLVO(*l)){
            printf("\nPresione [ESC] para volver al menu -- Presione [ENTER] para ver los siguientes 20... -- ");

            do{
                *aux = getch();
                if(*aux == 27)      //27 = ESC
                    return;

            }while(*aux != 13); //13 = ENTER

            system("cls");
            pagina++;
            printf("\n--- PAGINA %d ---\n", pagina);
        }
    }

    printf("\nFin de la Lista Vinculada Ordenada. Total registros mostrados: %d\n", contador);
}

void lvoINICIAR(Lvo *l, int controlImprimir){
    FILE *f = fopen("Operaciones_padron.txt", "r");
    if(f == NULL){
        printf("No existe el archivo...\n");
        return;
    }

    int cantaux = 0;

    int auxInt;
    char auxNombre[51];
    char auxDomicilo[81];
    int operacion = 0;

    //Costo individual de la operacion
    float costoOp = 0.0f;

    Padron pAux;

    while(fscanf(f, " %d", &operacion) == 1){
        cantaux++;
        switch(operacion){

            case 1:{ // ALTA
                fscanf(f, "%d", &auxInt);
                setPadronDNI(&pAux, auxInt);

                fscanf(f, " %50[^\n]", auxNombre);
                setPadronNombreApe(&pAux, auxNombre);

                fscanf(f, " %80[^\n]", auxDomicilo);
                setPadronDomicilio(&pAux, auxDomicilo);

                fscanf(f, "%d", &auxInt);
                setPadronPostal(&pAux, auxInt);

                fscanf(f, "%d", &auxInt);
                setPadronMesa(&pAux, auxInt);

                fscanf(f, "%d", &auxInt);
                setPadronCircuito(&pAux, auxInt);

                altaLvo(l, pAux, &costoOp);

                costoAltaAcumLVO += costoOp;
                cantAltaLVO++;
                if(costoOp > costoAltaMaxLVO)
                    costoAltaMaxLVO = costoOp;

                costoAltaMedLVO = costoAltaAcumLVO/cantAltaLVO;
                break;
            }

            case 2:{ // BAJA
                fscanf(f, "%d", &auxInt);
                setPadronDNI(&pAux, auxInt);

                fscanf(f, " %50[^\n]", auxNombre);
                setPadronNombreApe(&pAux, auxNombre);

                fscanf(f, " %80[^\n]", auxDomicilo);
                setPadronDomicilio(&pAux, auxDomicilo);

                fscanf(f, "%d", &auxInt);
                setPadronPostal(&pAux, auxInt);

                fscanf(f, "%d", &auxInt);
                setPadronMesa(&pAux, auxInt);

                fscanf(f, "%d", &auxInt);
                setPadronCircuito(&pAux, auxInt);

                bajaLvo(l, pAux, &costoOp);
                costoBajaAcumLVO += costoOp;
                cantBajaLVO++;
                if (costoOp > costoBajaMaxLVO)
                    costoBajaMaxLVO = costoOp;

                costoBajaMedLVO = costoBajaAcumLVO/cantBajaLVO;
                break;
            }

            case 3:{ // EVOCACION
                fscanf(f, "%d", &auxInt);

                if(evocacionLvo(l, &costoOp, auxInt, &pAux)){
                    costoLocELVO += costoOp;
                    cantELVO++;
                    if (costoOp > costoLocEMaxLVO) {
                        costoLocEMaxLVO = costoOp;
                    }

                    costoLocEMedLVO = costoLocELVO/cantELVO;
                }else{
                    costoLocFLVO += costoOp;
                    cantFLVO++;
                    if(costoOp > costoLocFMaxLVO){
                        costoLocFMaxLVO = costoOp;
                    }

                    costoLocFMedLVO = costoLocFLVO/cantFLVO;
                }

                break;
            }
        }
    }
    fclose(f);

    int aux;

    if(controlImprimir == 1){
            mostrarLvoPaginado(l, &aux);
    }


    if(aux == 27){
        system("cls");
        printf("\n----------- Se cancelo la muestra de la LVO -----------\n");
        return;
    }
}


//ARBOL BINARIO

//RECURSIVAA
void abbPreorden(NodoAbb *nodoActual, int *controlPagina, int *contador, int *pagina, int *aux){
    if(nodoActual != NULL){
        printf("[%d] ", *contador); mostrarPadron(nodoActual->dato);


        if(nodoActual->izq == NULL && nodoActual->der == NULL)
            printf("    |-- Hijos: Sin hijos");
        else{
            printf("    |-- Hijos: ");      //Imprimir hijos a continuacion

            if(nodoActual->izq != NULL)     //Imprimir hijo izquierdo (Si es q tiene)
                printf("[H.Izq DNI: %d] ", getPadronDNI(nodoActual->izq->dato));
            else
                printf("[H.Izq: Ninguno] ");

            if(nodoActual->der != NULL)     //Imprimir hijo derecho (Si es q tiene)
                printf("[H.Der DNI: %d] ", getPadronDNI(nodoActual->der->dato));
            else
                printf("[H.Der: Ninguno] ");
        }

        printf("\n\n");

        (*contador)++;
        (*controlPagina)++;


        if(*controlPagina == 20){
            printf("\nPresione [ESC] para volver al menu -- Presione [ENTER] para ver los siguientes 20... -- ");

            do{
                *aux = getch();
                if(*aux == 27)      //27 = ESC
                    return;

            }while(*aux != 13); //13 = ENTER

            system("cls");
            (*pagina)++;
            printf("\n--- PAGINA %d ---\n", *pagina);

            *controlPagina = 0;
        }

        //Recorre todo el subarbol izquierdo, cuando termina pasa a la siguiente linea
        abbPreorden(nodoActual->izq, controlPagina, contador, pagina, aux);

        //Recorre todo el subarbol derecho, cuando termina pasa a la siguiente linea
        abbPreorden(nodoActual->der, controlPagina, contador, pagina, aux);

        //la siguiente linea no es nada, no se sortea nada el chancho
    }
}

void mostrarAbbPaginado(Abb *a) {
    while(getchar() != '\n'); //Consume un ENTER
    if(isEmptyABB(*a)){
        printf("El arbol esta vacio\n");
        return;
    }

    int aux;
    int controlPagina = 0;
    int contador = 1;
    int pagina = 1;

    printf("\n--- PAGINA %d ---\n", pagina);

    abbPreorden(a->raiz, &controlPagina, &contador, &pagina, &aux);

    if(aux == 27){
        system("cls");
        printf("\n----------- Se cancelo la muestra del ABB -----------\n");
        return;
    }

    printf("\nFin del Arbol Binario. Total registros mostrados: %d\n", contador);
}


void abbINICIAR(Abb *a, int controlImprimir) {
    FILE *f = fopen("Operaciones_padron.txt", "r");
    if(f == NULL){
        printf("No existe el archivo...\n");
        return;
    }

    int cantaux = 0;
    float costoOp = 0;

    int auxInt;
    char auxNombre[51];
    char auxDomicilo[81];
    int operacion = 0;

    Padron pAux;

    while(fscanf(f, " %d", &operacion) == 1){
        cantaux++;
        switch(operacion){

            case 1:{ // ALTA
                fscanf(f, "%d", &auxInt);
                setPadronDNI(&pAux, auxInt);

                fscanf(f, " %50[^\n]", auxNombre);
                setPadronNombreApe(&pAux, auxNombre);

                fscanf(f, " %80[^\n]", auxDomicilo);
                setPadronDomicilio(&pAux, auxDomicilo);

                fscanf(f, "%d", &auxInt);
                setPadronPostal(&pAux, auxInt);

                fscanf(f, "%d", &auxInt);
                setPadronMesa(&pAux, auxInt);

                fscanf(f, "%d", &auxInt);
                setPadronCircuito(&pAux, auxInt);

                altaAbb(a, pAux, &costoOp);

                costoAltaAcumABB += costoOp;
                cantAltaABB++;
                if(costoOp > costoAltaMaxABB)
                    costoAltaMaxABB = costoOp;

                costoAltaMedABB = costoAltaAcumABB/cantAltaABB;
                break;
            }

            case 2:{ // BAJA
                fscanf(f, "%d", &auxInt);
                setPadronDNI(&pAux, auxInt);

                fscanf(f, " %50[^\n]", auxNombre);
                setPadronNombreApe(&pAux, auxNombre);

                fscanf(f, " %80[^\n]", auxDomicilo);
                setPadronDomicilio(&pAux, auxDomicilo);

                fscanf(f, "%d", &auxInt);
                setPadronPostal(&pAux, auxInt);

                fscanf(f, "%d", &auxInt);
                setPadronMesa(&pAux, auxInt);

                fscanf(f, "%d", &auxInt);
                setPadronCircuito(&pAux, auxInt);

                bajaAbb(a, pAux, &costoOp);
                costoBajaAcumABB += costoOp;
                cantBajaABB++;
                if (costoOp > costoBajaMaxABB)
                    costoBajaMaxABB = costoOp;

                costoBajaMedABB = costoBajaAcumABB/cantBajaABB;
                break;
            }

            case 3:{ // EVOCACION
                fscanf(f, "%d", &auxInt);

                if(evocacionAbb(a, &costoOp, auxInt, &pAux)){
                    costoLocEABB += costoOp;
                    cantEABB++;
                    if (costoOp > costoLocEMaxABB) {
                        costoLocEMaxABB = costoOp;
                    }

                    costoLocEMedABB = costoLocEABB/cantEABB;
                }else{
                    costoLocFABB += costoOp;
                    cantFABB++;
                    if(costoOp > costoLocFMaxABB){
                        costoLocFMaxABB = costoOp;
                    }

                    costoLocFMedABB = costoLocFABB/cantFABB;
                }
                break;
            }
        }
    }
    fclose(f);

    if(controlImprimir == 1){
        mostrarAbbPaginado(a);
    }
}

void liberarCostos(){
    // ABB
    costoAltaAcumABB = 0.0f; costoAltaMaxABB = 0.0f; cantAltaABB = 0.0f; costoAltaMedABB = 0.0f;
    costoBajaAcumABB = 0.0f; costoBajaMaxABB = 0.0f; cantBajaABB = 0.0f; costoBajaMedABB = 0.0f;
    costoLocEABB = 0.0f; costoLocEMaxABB = 0.0f; cantEABB = 0.0f; costoLocEMedABB = 0.0f;
    costoLocFABB = 0.0f; costoLocFMaxABB = 0.0f; cantFABB = 0.0f; costoLocFMedABB = 0.0f;

    // LVO
    costoAltaAcumLVO = 0.0f; costoAltaMaxLVO = 0.0f; cantAltaLVO = 0.0f; costoAltaMedLVO = 0.0f;
    costoBajaAcumLVO = 0.0f; costoBajaMaxLVO = 0.0f; cantBajaLVO = 0.0f; costoBajaMedLVO = 0.0f;
    costoLocELVO = 0.0f; costoLocEMaxLVO = 0.0f; cantELVO = 0.0f; costoLocEMedLVO = 0.0f;
    costoLocFLVO = 0.0f; costoLocFMaxLVO = 0.0f; cantFLVO = 0.0f; costoLocFMedLVO = 0.0f;

    // LSO
    costoAltaAcumLSO = 0.0f; costoAltaMaxLSO = 0.0f; cantAltaLSO = 0.0f; costoAltaMedLSO = 0.0f;
    costoBajaAcumLSO = 0.0f; costoBajaMaxLSO = 0.0f; cantBajaLSO = 0.0f; costoBajaMedLSO = 0.0f;
    costoLocELSO = 0.0f; costoLocEMaxLSO = 0.0f; cantELSO = 0.0f; costoLocEMedLSO = 0.0f;
    costoLocFLSO = 0.0f; costoLocFMaxLSO = 0.0f; cantFLSO = 0.0f; costoLocFMedLSO = 0.0f;
}

void liberarLvo(Lvo *l){
    resetLVO(l);

    while (!isOosLVO(*l)){
        NodoLvo *temp = l->cur;
        forwardsLvo(l);
        free(temp);
    }

    free(l->fin);
    l->acc = NULL;
    l->cur = NULL;
    l->aux = NULL;
    l->fin = NULL;
}

void liberarNodosAbb(NodoAbb *nodo){
    if (nodo != NULL){
        liberarNodosAbb(nodo->izq);
        liberarNodosAbb(nodo->der);
        free(nodo);
    }
}

void liberarAbb(Abb *a){
    liberarNodosAbb(a->raiz);
    a->raiz = NULL;
    a->pos = NULL;
    a->padre = NULL;
}



void compararEstructuras(Lvo *lvo, Abb *abb){       //AGREGAR LSO
    while(getchar() != '\n'); //Consume un ENTER

    liberarAbb(abb);
    liberarLvo(lvo);
    //liberarLso(lso);

    liberarCostos();

    initABB(abb);
    initLVO(lvo);
    //initLSO(lso);

    lvoINICIAR(lvo, 0);
    abbINICIAR(abb, 0);
    //lsoINICIAR(lso)

printf("**********************************************************************************************************************\n");
    printf("|---------|-------------------------||-------------------------||-------------------------||-------------------------|\n");
    printf("|         |          ALTA           ||          BAJA           ||        EVOCAR EX        ||       EVOCAR FRA        |\n");
    printf("|         |    Max     |    Med     ||    Max     |    Med     ||    Max     |    Med     ||    Max     |    Med     |\n");
    printf("|---------|------------|------------||------------|------------||------------|------------||------------|------------|\n");
    printf("| ABB     | %10.1f | %10.1f || %10.1f | %10.1f || %10.1f | %10.1f || %10.1f | %10.1f |\n",
        costoAltaMaxABB, costoAltaMedABB, costoBajaMaxABB, costoBajaMedABB, costoLocEMaxABB, costoLocEMedABB, costoLocFMaxABB, costoLocFMedABB);
    printf("|---------|------------|------------||------------|------------||------------|------------||------------|------------|\n");
    printf("| LSO     | %10.1f | %10.1f || %10.1f | %10.1f || %10.1f | %10.1f || %10.1f | %10.1f |\n",
           costoAltaMaxLSO, costoAltaMedLSO, costoBajaMaxLSO, costoBajaMedLSO, costoLocEMaxLSO, costoLocEMedLSO, costoLocFMaxLSO, costoLocFMedLSO);
    printf("|---------|------------|------------||------------|------------||------------|------------||------------|------------|\n");
    printf("| LVO     | %10.1f | %10.1f || %10.1f | %10.1f || %10.1f | %10.1f || %10.1f | %10.1f |\n",
           costoAltaMaxLVO, costoAltaMedLVO, costoBajaMaxLVO, costoBajaMedLVO, costoLocEMaxLVO, costoLocEMedLVO, costoLocFMaxLVO, costoLocFMedLVO);
    printf("|---------|------------|------------||------------|------------||------------|------------||------------|------------|\n");
    printf("**********************************************************************************************************************\n");
    printf("\n-- Presione [ENTER] para continuar --");
    while(getchar() != '\n'); //Consume un ENTER
    system("cls");
}


int main(){
    Lvo lista;
    initLVO(&lista);
    Abb arbol;
    initABB(&arbol);

    int opcion, opcion2;

    do{
        printf("\n----------- MENU -----------\n");
        printf("<1> Mostrar estructura\n");
        printf("<2> Comparar estructuras\n");
        printf("<3> Salir\n> ");
        scanf(" %d", &opcion);

        switch(opcion){

            case 1:{                //MOSTRAR ESTRUCTURAS
                system("cls");
                do{
                    printf("\n----------- Seleccione estructura -----------\n");
                    printf("<1> Lista Vinculada Ordenada con terminacion dada por contenido (LVO)\n");
                    printf("<2> Lista Secuencial Ordenada con busqueda binaria (LSOBB)\n");
                    printf("<3> Arbol Binario de Busqueda (ABB)\n");
                    printf("<4> Volver\n> ");
                    scanf(" %d", &opcion2);

                    switch(opcion2){
                        case 1:{                        //LVO
                            system("cls");
                            liberarLvo(&lista);
                            initLVO(&lista);
                            lvoINICIAR(&lista, 1);
                            break;
                        }
                        case 2:{                        //LSB
                            system("cls");

                            break;
                        }
                        case 3:{                        //ABB
                            system("cls");
                            liberarAbb(&arbol);
                            initABB(&arbol);
                            abbINICIAR(&arbol, 1);
                            break;
                        }
                        case 4:{                        //VOLVER
                            system("cls");
                            break;
                        }
                        default:{                       //DEFAULT
                            system("cls");
                            printf("\n----------- Error, opcion incorrecta -----------\n");
                            break;
                        }
                    }
                }while(opcion2 != 4);                   //SALIR DEL "MOSTRAR ESTRUCTURAS"

                break;
            }                                           //FIN CASE 1

            case 2:{            //COMPARAR ESTRUCTURAS (HACER)
                system("cls");
                compararEstructuras(&lista, &arbol);
                break;
            }

            case 3:{
                system("cls");

                printf("\n----------- Saliendo del programa -----------\n");
                break;
            }

            default:{
                system("cls");
                printf("\n----------- Error, opcion incorrecta -----------\n");
                break;
            }
        }
    }while(opcion != 3);
}
