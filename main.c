#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <strings.h>
#include <time.h>

#include "user.h"
#include "libros.h"
#include "controlador.h"
#define ARCHIVO_LIBROS "libros.dat"
#define ARCHIVO_USER "users.dat"

void cargarLibrosArchivoRandom(char nombreArchivo[]);
nodoListaUsuarios *  archivoToLista(char nombrearchivo[], nodoListaUsuarios * lista);
nodo2Libros * archivoToLista2(char nombreArchivo[], nodo2Libros * listaDoble);
void listaToArchivo(char nombreArchivo[], nodoListaUsuarios * lista);

int main()
{
//    srand(time(NULL));
//    stLibro libro1;
//    stUsuario user;
//    stDomicilio domicilio;
      nodoListaUsuarios* listauser=inicLista();
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
//    listauser=archivoToLista(ARCHIVO_USER,listauser);
    //listauser=crearNodoUser(listauser);
  //  listaToArchivo(ARCHIVO_USER,listauser);

//    muestraLista(listauser);
    registrarse(&listauser);
    registrarse(&listauser);
    login(&listauser);
    muestraLista(listauser);
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




//nodoListaUsuarios *  archivoToLista(char nombrearchivo[], nodoListaUsuarios * lista){
//
//    FILE * buffer = fopen(nombrearchivo, "rb");
//    stUsuario aux;
//
//
//    if(buffer){
//        while(fread(&aux, sizeof(stUsuario), 1, buffer) > 0){
//            lista = agregarEnOrdenId(lista,crearNodo(aux));
//        }
//        fclose(buffer);
//    }
//
//    return lista;
//
//}
//void listaToArchivo(char nombreArchivo[], nodoListaUsuarios * lista)
//{
//    FILE * buffer = fopen(nombreArchivo,"wb");
//
//    if(buffer)
//    {
//        while(lista)
//        {
//            fwrite(&(lista)->usuario,sizeof(stUsuario),1,buffer);
//            lista=lista->sig;
//        }
//        fclose(buffer);
//    }
//}
