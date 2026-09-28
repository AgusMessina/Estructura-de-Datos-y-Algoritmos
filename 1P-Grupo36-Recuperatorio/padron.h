#ifndef PADRON_H_INCLUDED
#define PADRON_H_INCLUDED


typedef struct{
    int dni;
    char nombreApellido[51];
    char domicilio[81];
    int codPostal;
    int mesa;
    int circuito;
} Padron;

/*

void setPadronDNI(Padron *p, int x){
    p->dni = x;
}
void setPadronPostal(Padron *p, int x){
    p->codPostal = x;
}
void setPadronMesa(Padron *p, int x){
    p->mesa = x;
}
void setPadronCircuito(Padron *p, int x){
    p->circuito = x;
}
void setPadronNombreApe(Padron *p, char x []){
    strcpy(p->nombreApellido, x);
}
void setPadronDomicilio(Padron *p, char x []){
    strcpy(p->domicilio, x);
}


int getPadronDNI(Padron p){
    return p.dni;
}
int getPadronMesa(Padron p){
    return p.mesa;
}
int getPadronCodPostal(Padron p){
    return p.codPostal;
}
int getPadronCircuito(Padron p){
    return p.circuito;
}
char* getPadronNombreApe(Padron p){
    char *aux = (char*)malloc(strlen(p.nombreApellido) + 1);
    strcpy(aux, p.nombreApellido);
    return aux;
}
char* getPadronDomicilio(Padron p){
    char *aux = (char*)malloc(strlen(p.domicilio) + 1);
    strcpy(aux, p.domicilio);
    return aux;
}

*/

int padronIguales(Padron a, Padron b) {
    if(a.dni != b.dni)
        return 0;
    if(strcasecmp(a.nombreApellido, b.nombreApellido) != 0)
        return 0;
    if(strcasecmp(a.domicilio, b.domicilio) != 0)
        return 0;
    if(a.codPostal != b.codPostal)
        return 0;
    if(a.mesa != b.mesa)
        return 0;
    if(a.circuito != b.circuito)
        return 0;

    return 1;
}

void mostrarPadron(Padron p) {
    printf("DNI: %d | %s | Domicilo: %s | Codigo Postal: %d | Mesa: %d | Circuito: %d\n",
           p.dni,
           p.nombreApellido,
           p.domicilio,
           p.codPostal,
           p.mesa,
           p.circuito);
}

#endif // PADRON_H_INCLUDED
