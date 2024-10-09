#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <strings.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>
//
//#include "user.h"
#include "controlador.h"
#define ARCHIVO_LIBROS "libros.dat"
#define ARCHIVO_USER "usuarios.dat"



nodoListaUsuarios *  archivoToLista(char nombrearchivo[], nodoListaUsuarios * lista);
void listaToArchivo(char nombreArchivo[], nodoListaUsuarios * lista);

int main()
{
    srand(time(NULL));
//    stLibro libro1;
//
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
//
    nodoListaUsuarios* listauser=inicLista();
    listauser=archivoToLista(ARCHIVO_USER,listauser);



    menuPrincipal(ARCHIVO_USER,listauser);
    return 0;
}




//void mostrarSubmenuIngreso()
//{
//    setColor(10);
//    printf("\n====================================\n");
//    printf("         Submenu de Ingreso\n");
//    printf("====================================\n");
//    printf("1. Iniciar sesion\n");
//    printf("2. Recuperar contrasena\n");
//    printf("3. Volver al menu principal\n");
//    printf("====================================\n");
//    setColor(7);
//}
//
//void mostrarSubmenuRegistro()
//{
//    setColor(12);
//    printf("\n====================================\n");
//    printf("        Submenu de Registro\n");
//    printf("====================================\n");
//    printf("1. Completar registro\n");
//    printf("2. Ver terminos y condiciones\n");
//    printf("3. Volver al menu principal\n");
//    printf("====================================\n");
//    setColor(7);
//}



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
