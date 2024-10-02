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
    do
    {
        //system("cls");
        mostrarMenuInicial();
        printf("\nSeleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion)
        {
        case 1:
            printf("\n--- Ingresando al sistema... ---\n");
            /// Logica de ingreso al sistema (login)
            mostrarSubmenuIngreso();
            break;

        case 2:
            printf("\n--- Registrarse en el sistema ---\n");
            /// Logica de registro de usuario
            mostrarSubmenuRegistro();
            break;

        case 0:
            printf("\n--- Saliendo del sistema ---\n");
            break;

        default:
            printf("\nOpcion no valida. Por favor, intenta nuevamente.\n");
            break;
        }
    }
    while(opcion != 0);
    return 0;
}


void setColor(int color)
{
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void escribirConRetraso(const char *texto, int delay)
{
    while (*texto)
    {
        putchar(*texto++); // Imprime un carácter
        fflush(stdout);    // Asegura que el carácter se imprima inmediatamente
        usleep(delay * 1000); // Retraso en milisegundos
    }
}

void mostrarMenuInicial()///menu inicial
{
    setColor(1);
    escribirConRetraso("\n====================================", 5);
    escribirConRetraso("\n    Sistema de Gestion de Libros", 5);
    escribirConRetraso("\n====================================", 5);
    escribirConRetraso("\n   1. Ingresar", 5);
    escribirConRetraso("\n   2. Registrarse", 5);
    escribirConRetraso("\n   0. Salir", 5);
    escribirConRetraso("\n====================================\n", 5);
    setColor(7);
}

void mostrarSubmenuIngreso()
{
    setColor(10);
    printf("\n====================================\n");
    printf("         Submenu de Ingreso\n");
    printf("====================================\n");
    printf("1. Iniciar sesion\n");
    printf("2. Recuperar contrasena\n");
    printf("3. Volver al menu principal\n");
    printf("====================================\n");
    setColor(7);
}

void mostrarSubmenuRegistro()
{
    setColor(12);
    printf("\n====================================\n");
    printf("        Submenu de Registro\n");
    printf("====================================\n");
    printf("1. Completar registro\n");
    printf("2. Ver terminos y condiciones\n");
    printf("3. Volver al menu principal\n");
    printf("====================================\n");
    setColor(7);
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
