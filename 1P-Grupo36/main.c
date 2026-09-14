#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <malloc.h>
#include "LVO.h"

void imprimirFilaCosto(char *nombre, float max, float total, int cant) {
    float media = (cant > 0) ? (total / cant) : 0.0f;
    printf("%-20s | Max: %6.2f | Media: %6.2f | Total: %7.2f | Cant: %3d\n",
           nombre, max, media, total, cant);
}

void mostrarLvoPaginado(Lvo *l) {
    if (isEmptyLVO(*l)) {
        printf("La lista esta vacia.\n");
        return;
    }

    resetLVO(l);
    int contador = 0;
    int pagina = 1;

    printf("\n=== MOSTRANDO LISTA (PAGINA %d) ===\n", pagina);

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
        if (contador % 20 == 0 && !isOosLVO(*l)) {
            printf("\n-- Presione [ENTER] para ver los siguientes 20... --");
            while (getchar() != '\n'); //Consume un ENTER
            pagina++;
            printf("\n=== PAGINA %d ===\n", pagina);
        }
    }

    printf("\nFin del listado. Total registros mostrados: %d\n", contador);
}

void lvoINICIAR(Lvo *l) {
    FILE *f = fopen("Operaciones_padron.txt", "r");
    if (f == NULL) {
        printf("No existe el archivo...\n");
        return;
    }

    int cantaux = 0;

    int auxInt;
    char auxNombre[51];
    char auxDomicilo[81];
    int operacion = 0;

    // Costo individual de operacion
    float costoOp = 0.0f;

    // Metricas ALTA (Exito y Fracaso)
    float costoAltaEAcum = 0.0f, costoAltaEMax = 0.0f;
    int cantAltaE = 0;
    float costoAltaFAcum = 0.0f, costoAltaFMax = 0.0f;
    int cantAltaF = 0;

    // Metricas BAJA (Exito y Fracaso)
    float costoBajaEAcum = 0.0f, costoBajaEMax = 0.0f;
    int cantBajaE = 0;
    float costoBajaFAcum = 0.0f, costoBajaFMax = 0.0f;
    int cantBajaF = 0;

    // Metricas EVOCACION / LOCALIZAR (Exito y Fracaso)
    float costoLocE = 0.0f, costoLocEMax = 0.0f;
    int cantE = 0;
    float costoLocF = 0.0f, costoLocFMax = 0.0f;
    int cantF = 0;

    Padron pAux;

    while (fscanf(f, " %d", &operacion) == 1) {
        cantaux++;
        switch (operacion) {

            case 1: { // ALTA
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

                if (altaLvo(l, pAux, &costoOp)) {
                    costoAltaEAcum += costoOp;
                    cantAltaE++;
                    if (costoOp > costoAltaEMax) {
                        costoAltaEMax = costoOp;
                    }
                } else {
                    costoAltaFAcum += costoOp;
                    cantAltaF++;
                    if (costoOp > costoAltaFMax) {
                        costoAltaFMax = costoOp;
                    }
                }

                break;
            }

            case 2: { // BAJA
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

                if (bajaLvo(l, pAux, &costoOp)) {
                    costoBajaEAcum += costoOp;
                    cantBajaE++;
                    if (costoOp > costoBajaEMax) {
                        costoBajaEMax = costoOp;
                    }
                } else {
                    costoBajaFAcum += costoOp;
                    cantBajaF++;
                    if (costoOp > costoBajaFMax)
                        costoBajaFMax = costoOp;
                }
                break;
            }

            case 3: { // EVOCACION
                fscanf(f, "%d", &auxInt);

                if (evocacionLvo(l, &costoOp, auxInt, &pAux)) {
                    costoLocE += costoOp;
                    cantE++;
                    if (costoOp > costoLocEMax) {
                        costoLocEMax = costoOp;
                    }
                } else {
                    costoLocF += costoOp;
                    cantF++;
                    if (costoOp > costoLocFMax) {
                        costoLocFMax = costoOp;
                    }
                }
                break;
            }
        }
    }
    fclose(f);

    mostrarLvoPaginado(l);

    printf("\n==================== REPORTE DE COSTOS ====================\n");
    imprimirFilaCosto("Alta (Exito)",       costoAltaEMax, costoAltaEAcum, cantAltaE);
    imprimirFilaCosto("Alta (Fracaso)",     costoAltaFMax, costoAltaFAcum, cantAltaF);
    imprimirFilaCosto("Baja (Exito)",       costoBajaEMax, costoBajaEAcum, cantBajaE);
    imprimirFilaCosto("Baja (Fracaso)",     costoBajaFMax, costoBajaFAcum, cantBajaF);
    imprimirFilaCosto("Evocacion (Exito)",  costoLocEMax,  costoLocE,      cantE);
    imprimirFilaCosto("Evocacion (Fracaso)",costoLocFMax,  costoLocF,      cantF);
    printf("===========================================================\n");
    printf("CANT AUX: %d", cantaux);
}





int main(){
    Lvo listaTEST;
    initLVO(&listaTEST);
    lvoINICIAR(&listaTEST);
}
