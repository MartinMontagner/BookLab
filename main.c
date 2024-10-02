#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <strings.h>
#include <time.h>
#include <stdbool.h>

#include "user.h"
#include "libros.h"
#include "controlador.h"
#define ARCHIVO_LIBROS "libros.dat"
#define ARCHIVO_USER "usuarios.dat"

void cargarLibrosArchivoRandom(char nombreArchivo[]);
nodo2Libros * archivoToLista2(char nombreArchivo[], nodo2Libros * listaDoble);
nodoListaUsuarios *  archivoToLista(char nombrearchivo[], nodoListaUsuarios * lista);
void listaToArchivo(char nombreArchivo[], nodoListaUsuarios * lista);

int main()
{
//    srand(time(NULL));
//    stLibro libro1;

//    nodo2Libros* lista=inicListaDoble();
//    lista = archivoToLista2(ARCHIVO_LIBROS,lista);
//    lista=cargarLibroEnLista(lista);//
    // muestraListaLibros(lista);
    // darDeBajaLogica(lista);
    //printf("\nLIBROS SIN EL ELIMINADO\n");
//    muestraListaLibros(lista);
//    printf("\nLista de libros version ADMIN\n");
//    muestraListaLibrosAdmin(lista);
//    agregarLibrosAlArchivo(lista,ARCHIVO_LIBROS);

    nodoListaUsuarios* listauser=inicLista();
    listauser=archivoToLista(ARCHIVO_USER,listauser);

    listauser=registrarse(listauser);
    printf("despues del registro");
    //registrarse(listauser);
    login(listauser);

    muestraLista(listauser);
    listaToArchivo(ARCHIVO_USER,listauser);

    printf("Hello world!\n");
    system("pause");
    return 0;
}
void cargarLibrosArchivoRandom(char nombreArchivo[])
{

    FILE * buffer = fopen(nombreArchivo,"ab");
    stLibro aux;
    char opcion = 0;
    int i = 0;


    if(buffer)
    {
        do
        {
            printf("Libro %d\n", i);
            aux = cargaRandomLibro();
            fwrite(&aux,sizeof(stLibro),1,buffer);
            i++;

            printf("Desea seguir cargando? Presione 'n' para salir \n");
            fflush(stdin);
            scanf("%c",&opcion);
        }
        while(opcion != 'n');
        fclose(buffer);

    }
}
nodo2Libros *  archivoToLista2(char nombreArchivo[], nodo2Libros * listaDoble)
{

    FILE * buffer = fopen(nombreArchivo, "rb");
    stLibro aux;


    if(buffer)
    {
        while(fread(&aux, sizeof(stLibro), 1, buffer) > 0)
        {
            listaDoble = insertarNodoPorId(listaDoble,crearNodoDoble(aux));
        }
        fclose(buffer);
    }

    return listaDoble;
}


nodoListaUsuarios *  archivoToLista(char nombrearchivo[], nodoListaUsuarios * lista){

    FILE * buffer = fopen(nombrearchivo, "rb");
    stUsuario aux;


    if(buffer){
        while(fread(&aux, sizeof(stUsuario), 1, buffer) > 0){
            lista = agregarEnOrdenId(lista,crearNodo(aux));
        }
        fclose(buffer);
    }

    return lista;

}
void listaToArchivo(char nombreArchivo[], nodoListaUsuarios * lista)
{
    FILE * buffer = fopen(nombreArchivo,"wb");

    if(buffer)
    {
        nodoListaUsuarios* actual = lista;
        while(actual)
        {
            fwrite(&actual->usuario,sizeof(stUsuario),1,buffer);
            actual=actual->sig;
        }

        fclose(buffer);
    }
}
