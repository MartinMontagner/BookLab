#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <strings.h>
#include <time.h>

#include "user.h"


nodoListaUsuarios * archivoToLista(char nombreArchivo[], nodoListaUsuarios * lista);

int main()
{
    printf("Hello world!\n");

    return 0;
}
nodoListaUsuarios *  archivoToLista(char nombreArchivo[], nodoListaUsuarios * lista){

    FILE * buffer = fopen(nombreArchivo, "rb");
    stUsuario aux;


    if(buffer){
        while(fread(&aux, sizeof(stUsuario), 1, buffer) > 0){
            lista = agregarEnOrdenDNI(lista,crearNodo(aux));
        }
        fclose(buffer);
    }

    return lista;

}
