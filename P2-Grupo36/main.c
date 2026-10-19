#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <conio.h>

#include "Padron.h"
#include "RAL.h"
#include "RAC.h"
#include "RS.h"

//--------------- VARIABLES COSTO (SON GLOBALES) ---------------

// Rebalse Abierto Lineal
// ALTA
int costoAltaAcumRAL = 0;
int costoAltaMaxRAL = 0;
int cantAltaRAL = 0;
float costoAltaMedRAL = 0.0f;

// BAJA
int costoBajaAcumRAL = 0;
int costoBajaMaxRAL = 0;
int cantBajaRAL = 0;
float costoBajaMedRAL = 0.0f;

// EVOCACION (Exito y Fracaso)
// Exito
int costoLocERAL = 0;
int costoLocEMaxRAL = 0;
int cantERAL = 0;
float costoLocEMedRAL = 0.0f;

// Fracaso
int costoLocFRAL = 0;
int costoLocFMaxRAL = 0;
int cantFRAL = 0;
float costoLocFMedRAL = 0.0f;

// ---------------


// Rebalse Abierto Cuadratico
// ALTA
int costoAltaAcumRAC = 0;
int costoAltaMaxRAC = 0;
int cantAltaRAC = 0;
float costoAltaMedRAC = 0.0f;

// BAJA
int costoBajaAcumRAC = 0;
int costoBajaMaxRAC = 0;
int cantBajaRAC = 0;
float costoBajaMedRAC = 0.0f;

// EVOCACION (Exito y Fracaso)
// Exito
int costoLocERAC = 0;
int costoLocEMaxRAC = 0;
int cantERAC = 0;
float costoLocEMedRAC = 0.0f;

// Fracaso
int costoLocFRAC = 0;
int costoLocFMaxRAC = 0;
int cantFRAC = 0;
float costoLocFMedRAC = 0.0f;

// ---------------


// Rebalse Separado
// ALTA
int costoAltaAcumRS = 0;
int costoAltaMaxRS = 0;
int cantAltaRS = 0;
float costoAltaMedRS = 0.0f;

// BAJA
int costoBajaAcumRS = 0;
int costoBajaMaxRS = 0;
int cantBajaRS = 0;
float costoBajaMedRS = 0.0f;

// EVOCACION (Exito y Fracaso)
// Exito
int costoLocERS = 0;
int costoLocEMaxRS = 0;
int cantERS = 0;
float costoLocEMedRS = 0.0f;

// Fracaso
int costoLocFRS = 0;
int costoLocFMaxRS = 0;
int cantFRS = 0;
float costoLocFMedRS = 0.0f;

//--------------- FIN VARIABLES GLOBALES ---------------

//ESTRUCTURAS

//RAL

void mostrarRalPaginado(RAL *r) {
    while(getchar() != '\n'); // Consume un ENTER

    if(r->cant == 0){
        printf("La tabla RAL esta vacia.\n");
        return;
    }

    int contador = 0;
    int pagina = 1;
    int aux = 0;
    printf("\n--- PAGINA %d ---\n", pagina);

    for(int i = 0; i < M_RAL; i++) {

        if(r->rebalse[i].estado == 'O') {
            Padron p = r->rebalse[i].dato;

            // Imprime
            printf("[%d] (Celda %d) ", contador, i);
            mostrarPadron(p);
            printf("\n");

            contador++;

            if(contador % 20 == 0 && contador < r->cant) {
                printf("\nPresione [ESC] para volver al menu -- Presione [ENTER] para ver los siguientes 20... -- ");

                do {
                    aux = getch();
                    if(aux == 27)      // 27 = ESC
                        return;

                } while(aux != 13); // 13 = ENTER

                system("cls");
                pagina++;
                printf("\n--- PAGINA %d ---\n", pagina);
            }
        }
    }

    printf("\nFin de la tabla RAL. Total registros mostrados: %d\n", contador);
}

//RAC

void mostrarRacPaginado(RAC *r) {
    while(getchar() != '\n'); // Consume un ENTER

    if(r->cant == 0){
        printf("La tabla RAC esta vacia.\n");
        return;
    }

    int contador = 0;
    int pagina = 1;
    int aux = 0;
    printf("\n--- PAGINA %d ---\n", pagina);

    for(int i = 0; i < M_RAC; i++) {

        if(r->rebalse[i].estado == 'O') {
            Padron p = r->rebalse[i].dato;

            printf("[%d] (Celda %d) ", contador, i);
            mostrarPadron(p);
            printf("\n");

            contador++;

            // Muestra 20 Elementos
            if(contador % 20 == 0 && contador < r->cant) {
                printf("\nPresione [ESC] para volver al menu -- Presione [ENTER] para ver los siguientes 20... -- ");

                do {
                    aux = getch();
                    if(aux == 27)      // 27 = ESC
                        return;

                } while(aux != 13); // 13 = ENTER

                system("cls");
                pagina++;
                printf("\n--- PAGINA %d ---\n", pagina);
            }
        }
    }

    printf("\nFin de la tabla RAC. Total registros mostrados: %d\n", contador);
}

//RS

void mostrarRsPaginado(RS *r) {
    while(getchar() != '\n'); // Consume un ENTER

    if(r->cant == 0){
        printf("La tabla RS esta vacia.\n");
        return;
    }

    int contador = 0;
    int pagina = 1;
    int aux = 0;
    printf("\n--- PAGINA %d ---\n", pagina);

    for(int i = 0; i < M_RS; i++) {

        Nodo *actual = r->rebalse[i];

        while(actual != NULL) {
            Padron p = actual->dato;

            printf("[%d] (Cubeta %d) ", contador, i);
            mostrarPadron(p);
            printf("\n");

            contador++;
            if(contador % 20 == 0 && contador < r->cant) {
                printf("\nPresione [ESC] para volver al menu -- Presione [ENTER] para ver los siguientes 20... -- ");

                do {
                    aux = getch();
                    if(aux == 27)      // 27 = ESC
                        return;

                } while(aux != 13); // 13 = ENTER

                system("cls");
                pagina++;
                printf("\n--- PAGINA %d ---\n", pagina);
            }

            actual = actual->siguiente;
        }
    }

    printf("\nFin de la tabla RS. Total registros mostrados: %d\n", contador);
}

void cargaArchivo(RAL *ral, RAC *rac, RS *rs){
    //FILE *f = fopen("Operaciones.txt", "r");
    FILE *f = fopen("Operaciones_Padron.txt", "r");
    //FILE *f = fopen("Operaciones_PadronTEST.txt", "r");
    if(f == NULL){
        printf("No existe el archivo...\n");
        return;
    }

    int cantaux = 0;
    int auxInt;
    char auxNombre[51];
    char auxDomicilo[81];
    int operacion = 0;

    // Costo individual de la operacion (ahora en int)
    int costoOp = 0;

    // Variable auxiliar para el 'pos' que piden localizarRAL y localizarRAC
    int posAuxHash = 0;

    Padron pAux;

    while(fscanf(f, " %d", &operacion) == 1){
        cantaux++;
        switch(operacion){

            case 1:{ // ALTA
                fscanf(f, "%d", &auxInt);
                pAux.dni = auxInt;

                if(auxInt > 0){

                    fscanf(f, " %50[^\n]", auxNombre);
                    strcpy(pAux.nombreApellido, auxNombre);

                    fscanf(f, " %80[^\n]", auxDomicilo);
                    strcpy(pAux.domicilio, auxDomicilo);

                    fscanf(f, "%d", &auxInt);
                    pAux.codPostal = auxInt;

                    fscanf(f, "%d", &auxInt);
                    pAux.mesa = auxInt;

                    fscanf(f, "%d", &auxInt);
                    pAux.circuito = auxInt;

                    // Alta RAL
                    if(altaRAL(ral, pAux, &costoOp)){
                        costoAltaAcumRAL += costoOp;
                        cantAltaRAL++;
                        if(costoOp > costoAltaMaxRAL)
                            costoAltaMaxRAL = costoOp;

                        costoAltaMedRAL = (float)costoAltaAcumRAL/cantAltaRAL;
                    }
                    costoOp = 0;

                    // Alta RAC
                    if(altaRAC(rac, pAux, &costoOp)){
                        costoAltaAcumRAC += costoOp;
                        cantAltaRAC++;
                        if(costoOp > costoAltaMaxRAC)
                            costoAltaMaxRAC = costoOp;

                        costoAltaMedRAC = (float)costoAltaAcumRAC/cantAltaRAC;
                    }
                    costoOp = 0;

                    // Alta RS
                    if(altaRS(rs, pAux, &costoOp)){
                        costoAltaAcumRS += costoOp;
                        cantAltaRS++;
                        if(costoOp > costoAltaMaxRS)
                            costoAltaMaxRS = costoOp;

                        costoAltaMedRS = (float)costoAltaAcumRS/cantAltaRS;
                    }
                    costoOp = 0;
                }
                break;
            }

            case 2:{ // BAJA
                fscanf(f, "%d", &auxInt);
                pAux.dni = auxInt;

                if(auxInt > 0){
                    fscanf(f, " %50[^\n]", auxNombre);
                    strcpy(pAux.nombreApellido, auxNombre);

                    fscanf(f, " %80[^\n]", auxDomicilo);
                    strcpy(pAux.domicilio, auxDomicilo);

                    fscanf(f, "%d", &auxInt);
                    pAux.codPostal = auxInt;

                    fscanf(f, "%d", &auxInt);
                    pAux.mesa = auxInt;

                    fscanf(f, "%d", &auxInt);
                    pAux.circuito = auxInt;

                    // Baja RAL
                    if(bajaRAL(ral, pAux, &costoOp)){
                        costoBajaAcumRAL += costoOp;
                        cantBajaRAL++;
                        if(costoOp > costoBajaMaxRAL)
                            costoBajaMaxRAL = costoOp;

                        costoBajaMedRAL = (float)costoBajaAcumRAL/cantBajaRAL;
                    }
                    costoOp = 0;

                    // Baja RAC
                    if(bajaRAC(rac, pAux, &costoOp)){
                        costoBajaAcumRAC += costoOp;
                        cantBajaRAC++;
                        if(costoOp > costoBajaMaxRAC)
                            costoBajaMaxRAC = costoOp;

                        costoBajaMedRAC = (float)costoBajaAcumRAC/cantBajaRAC;
                    }
                    costoOp = 0;

                    // Baja RS
                    if(bajaRS(rs, pAux, &costoOp)){
                        costoBajaAcumRS += costoOp;
                        cantBajaRS++;
                        if(costoOp > costoBajaMaxRS)
                            costoBajaMaxRS = costoOp;

                        costoBajaMedRS = (float)costoBajaAcumRS/cantBajaRS;
                    }
                    costoOp = 0;
                }
                break;
            }

            case 3:{ // EVOCACION
                fscanf(f, "%d", &auxInt);

                if(auxInt > 0){

                    // Evocar RAL
                    if(localizarRAL(ral, auxInt, &posAuxHash, &costoOp)){       // Exito
                        costoLocERAL += costoOp;
                        cantERAL++;
                        if (costoOp > costoLocEMaxRAL) {
                            costoLocEMaxRAL = costoOp;
                        }
                        costoLocEMedRAL = (float)costoLocERAL/cantERAL;
                    }else{                                                      // Fracaso
                        costoLocFRAL += costoOp;
                        cantFRAL++;
                        if(costoOp > costoLocFMaxRAL){
                            costoLocFMaxRAL = costoOp;
                        }
                        costoLocFMedRAL = (float)costoLocFRAL/cantFRAL;
                    }
                    costoOp = 0;

                    // Evocar RAC
                    if(localizarRAC(rac, auxInt, &posAuxHash, &costoOp)){       // Exito
                        costoLocERAC += costoOp;
                        cantERAC++;
                        if (costoOp > costoLocEMaxRAC) {
                            costoLocEMaxRAC = costoOp;
                        }
                        costoLocEMedRAC = (float)costoLocERAC/cantERAC;
                    }else{                                                      // Fracaso
                        costoLocFRAC += costoOp;
                        cantFRAC++;
                        if(costoOp > costoLocFMaxRAC){
                            costoLocFMaxRAC = costoOp;
                        }
                        costoLocFMedRAC = (float)costoLocFRAC/cantFRAC;
                    }
                    costoOp = 0;

                    // Evocar RS
                    if(localizarRS(rs, auxInt, &costoOp)){                      // Exito
                        costoLocERS += costoOp;
                        cantERS++;
                        if (costoOp > costoLocEMaxRS) {
                            costoLocEMaxRS = costoOp;
                        }
                        costoLocEMedRS = (float)costoLocERS/cantERS;
                    }else{                                                      // Fracaso
                        costoLocFRS += costoOp;
                        cantFRS++;
                        if(costoOp > costoLocFMaxRS){
                            costoLocFMaxRS = costoOp;
                        }
                        costoLocFMedRS = (float)costoLocFRS/cantFRS;
                    }
                    costoOp = 0;
                }
                break;
            }
        }
    }
    fclose(f);
}

void liberarCostos(){
    //RAL
    costoAltaAcumRAL = 0; costoAltaMaxRAL = 0; cantAltaRAL = 0; costoAltaMedRAL = 0.0f;
    costoBajaAcumRAL = 0; costoBajaMaxRAL = 0; cantBajaRAL = 0; costoBajaMedRAL = 0.0f;
    costoLocERAL = 0; costoLocEMaxRAL = 0; cantERAL = 0; costoLocEMedRAL = 0.0f;
    costoLocFRAL = 0; costoLocFMaxRAL = 0; cantFRAL = 0; costoLocFMedRAL = 0.0f;

    //RAC
    costoAltaAcumRAC = 0; costoAltaMaxRAC = 0; cantAltaRAC = 0; costoAltaMedRAC = 0.0f;
    costoBajaAcumRAC = 0; costoBajaMaxRAC = 0; cantBajaRAC = 0; costoBajaMedRAC = 0.0f;
    costoLocERAC = 0; costoLocEMaxRAC = 0; cantERAC = 0; costoLocEMedRAC = 0.0f;
    costoLocFRAC = 0; costoLocFMaxRAC = 0; cantFRAC = 0; costoLocFMedRAC = 0.0f;

    //RS
    costoAltaAcumRS = 0; costoAltaMaxRS = 0; cantAltaRS = 0; costoAltaMedRS = 0.0f;
    costoBajaAcumRS = 0; costoBajaMaxRS = 0; cantBajaRS = 0; costoBajaMedRS = 0.0f;
    costoLocERS = 0; costoLocEMaxRS = 0; cantERS = 0; costoLocEMedRS = 0.0f;
    costoLocFRS = 0; costoLocFMaxRS = 0; cantFRS = 0; costoLocFMedRS = 0.0f;
}

//RAL

void liberarRAL(RAL *r){
    int i;
    r->cant = 0;

    for(i = 0; i < M_RAL; i++){
        r->rebalse[i].estado = '*';
    }
}

//RAC

void liberarRAC(RAC *r){
    int i;
    r->cant = 0;

    for(i = 0; i < M_RAC; i++){
        r->rebalse[i].estado = '*';
    }
}

//RS

void liberarRS(RS *r){
    int i;

    for(i = 0; i < M_RS; i++){
        Nodo *actual = r->rebalse[i];

        while(actual != NULL){
            Nodo *temp = actual;
            actual = actual->siguiente;
            free(temp);
        }

        r->rebalse[i] = NULL;
    }

    r->cant = 0;
}

void compararEstructuras(RAL *ral, RAC *rac, RS *rs){
    while(getchar() != '\n'); //Consume un ENTER

    // 1. Liberar las estructuras Hash
    liberarRAL(ral);
    liberarRAC(rac);
    liberarRS(rs);

    liberarCostos(); // Asegúrate de quitar de esta función también lo de ABB, LVO y LSO

    // 2. Inicializar las estructuras Hash
    initRAL(ral);
    initRAC(rac);
    initRS(rs);

    // 3. Cargar el archivo
    cargaArchivo(ral, rac, rs); // O cargaArchivo(), según cómo la hayas llamado

    system("cls");

    // =========================================================================================
    //                            CUADRO 1: EVOCACIÓN (ÉXITO Y FRACASO)
    // =========================================================================================
    printf("\n");
    printf("+-----+-----------------------------+-----------------------------+\n");
    printf("|     |        EVOCAR EXITO         |       EVOCAR FRACASO        |\n");
    printf("+-----+------+--------+------+------+------+--------+------+------+\n");
    printf("| Est | Cant |  Acum  |  Max |  Med | Cant |  Acum  |  Max |  Med |\n");
    printf("+-----+------+--------+------+------+------+--------+------+------+\n");

    printf("| RAL | %4d | %6d | %4d |%6.2f| %4d | %6d | %4d |%6.2f|\n",
           cantERAL,    costoLocERAL,     costoLocEMaxRAL, costoLocEMedRAL,
           cantFRAL,    costoLocFRAL,     costoLocFMaxRAL, costoLocFMedRAL);
    printf("+-----+------+--------+------+------+------+--------+------+------+\n");

    printf("| RAC | %4d | %6d | %4d |%6.2f| %4d | %6d | %4d |%6.2f|\n",
           cantERAC,    costoLocERAC,     costoLocEMaxRAC, costoLocEMedRAC,
           cantFRAC,    costoLocFRAC,     costoLocFMaxRAC, costoLocFMedRAC);
    printf("+-----+------+--------+------+------+------+--------+------+------+\n");

    printf("| RS  | %4d | %6d | %4d |%6.2f| %4d | %6d | %4d |%6.2f|\n",
           cantERS,     costoLocERS,      costoLocEMaxRS,  costoLocEMedRS,
           cantFRS,     costoLocFRS,      costoLocFMaxRS,  costoLocFMedRS);
    printf("+-----+------+--------+------+------+------+--------+------+------+\n");

    printf("\n\n");


    /*
    // =========================================================================================
    //                                 CUADRO 2: ALTAS Y BAJAS
    // =========================================================================================
    printf("+-----+-----------------------------+-----------------------------+\n");
    printf("|     |             ALTA            |             BAJA            |\n");
    printf("+-----+------+--------+------+------+------+--------+------+------+\n");
    printf("| Est | Cant |  Acum  |  Max |  Med | Cant |  Acum  |  Max |  Med |\n");
    printf("+-----+------+--------+------+------+------+--------+------+------+\n");

    printf("| RAL | %4d | %6d | %4d |%6.2f| %4d | %6d | %4d |%6.2f|\n",
           cantAltaRAL, costoAltaAcumRAL, costoAltaMaxRAL, costoAltaMedRAL,
           cantBajaRAL, costoBajaAcumRAL, costoBajaMaxRAL, costoBajaMedRAL);
    printf("+-----+------+--------+------+------+------+--------+------+------+\n");

    printf("| RAC | %4d | %6d | %4d |%6.2f| %4d | %6d | %4d |%6.2f|\n",
           cantAltaRAC, costoAltaAcumRAC, costoAltaMaxRAC, costoAltaMedRAC,
           cantBajaRAC, costoBajaAcumRAC, costoBajaMaxRAC, costoBajaMedRAC);
    printf("+-----+------+--------+------+------+------+--------+------+------+\n");

    printf("| RS  | %4d | %6d | %4d |%6.2f| %4d | %6d | %4d |%6.2f|\n",
           cantAltaRS,  costoAltaAcumRS,  costoAltaMaxRS,  costoAltaMedRS,
           cantBajaRS,  costoBajaAcumRS,  costoBajaMaxRS,  costoBajaMedRS);
    printf("+-----+------+--------+------+------+------+--------+------+------+\n");

    */

    printf("\n-- Presione [ENTER] para continuar --");
    while(getchar() != '\n'); //Consume un ENTER
    system("cls");
}

int main(){
    // Declaración de las estructuras Hash
    RAL ral;
    initRAL(&ral);

    RAC rac;
    initRAC(&rac);

    RS rs;
    initRS(&rs);

    int opcion, opcion2;
    int control = 0;

    do{
        printf("\n----------- MENU -----------\n");
        printf("<1> Mostrar estructura\n");
        printf("<2> Comparar estructuras\n");
        printf("<3> Salir\n> ");
        scanf(" %d", &opcion);

        switch(opcion){

            case 1:{                // MOSTRAR ESTRUCTURAS
                system("cls");
                if(control != 1){
                    printf("Primero hay que comparar (cargar los datos en las estructuras)\n");
                    break;
                }

                do{
                    printf("\n----------- Seleccione estructura -----------\n");
                    printf("<1> Rebalse Abierto Lineal (RAL)\n");
                    printf("<2> Rebalse Abierto Cuadratico (RAC)\n");
                    printf("<3> Rebalse Separado (RS)\n");
                    printf("<4> Volver\n> ");
                    scanf(" %d", &opcion2);

                    switch(opcion2){
                        case 1:{                        // RAL
                            system("cls");
                            mostrarRalPaginado(&ral);
                            break;
                        }
                        case 2:{                        // RAC
                            system("cls");
                            mostrarRacPaginado(&rac);
                            break;
                        }
                        case 3:{                        // RS
                            system("cls");
                            mostrarRsPaginado(&rs);
                            break;
                        }
                        case 4:{                        // VOLVER
                            system("cls");
                            break;
                        }
                        default:{                       // DEFAULT
                            system("cls");
                            printf("\n----------- Error, opcion incorrecta -----------\n");
                            break;
                        }
                    }
                }while(opcion2 != 4);                   // SALIR DEL "MOSTRAR ESTRUCTURAS"
            }break;                                     // FIN CASE 1

            case 2:{            // COMPARAR ESTRUCTURAS
                system("cls");
                compararEstructuras(&ral, &rac, &rs);
                control = 1;
                break;
            }

            case 3:{            // SALIR
                system("cls");
                printf("\n----------- Saliendo del programa -----------\n");
                // Es buena práctica liberar la memoria dinámica antes de salir
                liberarRS(&rs);
                break;
            }

            default:{           // OPCION INVALIDA
                system("cls");
                printf("\n----------- Error, opcion incorrecta -----------\n");
                break;
            }
        }
    }while(opcion != 3);

    return 0;
}
