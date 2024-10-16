#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <strings.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>
//#include "user.h"
#include "controlador.h"
#define ARCHIVO_LIBROS "libros.dat"
#define ARCHIVO_USER "usuarios.dat"

void menuPrincipal(char archivoUser[], nodoListaUsuarios * listaUser);
void mostrarMenuInicial();

int main()
{
    srand(time(NULL));

    nodoListaUsuarios* listauser=inicLista();

    listauser=archivoToLista(ARCHIVO_USER,listauser);

    menuPrincipal(ARCHIVO_USER,listauser);
    return 0;
}

void menuPrincipal(char archivoUser[], nodoListaUsuarios *listaUser)
{
    int opcion;

    do
    {
        system("pause");
        system("cls");
        mostrarMenuInicial();
        printf("\nSeleccione una opcion: ");
        fflush(stdin);
        scanf("%d",&opcion);

        switch(opcion)
        {
        case 1:
            system("cls");
            login(listaUser);
            break;

        case 2:
            printf("\n--- Registrarse en el sistema ---\n");
            /// Logica de registro de usuario
            listaUser= registrarse(listaUser);
            listaToArchivo(archivoUser,listaUser);
            break;

        case 0:
            system("cls");
            printf("\n--- Saliendo del sistema ---\n");
            break;

        default:
            printf("\nOpcion no valida. Por favor, intenta nuevamente.\n");
            break;
        }
    }
    while(opcion != 0);
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
