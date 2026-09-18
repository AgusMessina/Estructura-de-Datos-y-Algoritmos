#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <malloc.h>
#include "LVO.h"
#include "ABB.h"

void imprimirFilaCosto(char *nombre, float max, float total, int cant) {
    float media = (cant > 0) ? (total / cant) : 0.0f;
    printf("%-20s | Max: %6.2f | Media: %6.2f | Total: %7.2f | Cant: %3d\n",
           nombre, max, media, total, cant);
}

void mostrarLvoPaginado(Lvo *l) {
    while (getchar() != '\n'); //Consume un ENTER
    if(isEmptyLVO(*l)){
        printf("La lista esta vacia.\n");
        return;
    }

    resetLVO(l);
    int contador = 0;
    int pagina = 1;

    printf("\n--- (PAGINA %d) ---\n", pagina);

    //Recorre mientras no llegue al centinela
    while (!isOosLVO(*l)) {
        Padron p = l->cur->dato;

        //Imprime
        printf("[%d] DNI: %d | Nombre y Apellido: %s | Mesa: %d\n",
               contador + 1,
               getPadronDNI(p),
               getPadronNombreApe(p),
               getPadronMesa(p));

        contador++;
        forwardsLvo(l);

        //Muestra 20 Elementos
        if(contador % 20 == 0 && !isOosLVO(*l)){
            printf("\n-- Presione [ENTER] para ver los siguientes 20... --");
            while (getchar() != '\n'); //Consume un ENTER
            system("cls");
            pagina++;
            printf("\n--- PAGINA %d ---\n", pagina);
        }
    }

    printf("\nFin del listado. Total registros mostrados: %d\n", contador);
}

void lvoINICIAR(Lvo *l) {
    FILE *f = fopen("Operaciones_padronTEST.txt", "r");
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

    //ALTA
    float costoAltaAcum = 0.0f, costoAltaMax = 0.0f;
    int cantAlta = 0;

    //BAJA
    float costoBajaAcum = 0.0f, costoBajaMax = 0.0f;
    int cantBaja = 0;

    //EVOCACION (Exito y Fracaso)
    //Exito
    float costoLocE = 0.0f, costoLocEMax = 0.0f;
    int cantE = 0;

    //Fracaso
    float costoLocF = 0.0f, costoLocFMax = 0.0f;
    int cantF = 0;

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

                costoAltaAcum += costoOp;
                cantAlta++;
                if(costoOp > costoAltaMax)
                    costoAltaMax = costoOp;

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
                costoBajaAcum += costoOp;
                cantBaja++;
                if (costoOp > costoBajaMax)
                    costoBajaMax = costoOp;

                break;
            }

            case 3:{ // EVOCACION
                fscanf(f, "%d", &auxInt);

                if(evocacionLvo(l, &costoOp, auxInt, &pAux)){
                    costoLocE += costoOp;
                    cantE++;
                    if (costoOp > costoLocEMax) {
                        costoLocEMax = costoOp;
                    }
                }else{
                    costoLocF += costoOp;
                    cantF++;
                    if(costoOp > costoLocFMax){
                        costoLocFMax = costoOp;
                    }
                }
                break;
            }
        }
    }
    fclose(f);

    mostrarLvoPaginado(l);

    printf("\n-------------------- REPORTE DE COSTOS --------------------\n");
    imprimirFilaCosto("Alta",       costoAltaMax, costoAltaAcum, cantAlta);
    imprimirFilaCosto("Baja",       costoBajaMax, costoBajaAcum, cantBaja);
    imprimirFilaCosto("Evocacion (Exito)",  costoLocEMax,  costoLocE,      cantE);
    imprimirFilaCosto("Evocacion (Fracaso)",costoLocFMax,  costoLocF,      cantF);
    printf("-----------------------------------------------------------\n");
    printf("CANT AUX: %d", cantaux);

    printf("\n-- Presione [ENTER] para continuar --");
    while (getchar() != '\n'); //Consume un ENTER
    system("cls");
}





int main(){
    Lvo listaTEST;
    initLVO(&listaTEST);

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
                            lvoINICIAR(&listaTEST);
                            break;
                        }
                        case 2:{                        //LSB
                            system("cls");

                            break;
                        }
                        case 3:{                        //ABB
                            system("cls");

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

                break;
            }

            case 3:{
                system("cls");

                printf("\n----------- Saliendo del programa -----------\n");
            }
        }
    }while(opcion != 3);
}
