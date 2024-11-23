#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>
#include <unistd.h>
#include "libros.h"


typedef struct{
    char calle[50];
    int altura;
    int cp;
    char ciudad[100];
    char localidad[50];
    char pais[100];
} stDomicilio;



typedef struct{
    int idUsuario;//
    char email[100];//
    char password[20];
    char username[20];//
    int esAdmin;  /// 1 = si  0 = no
    char genero;//
    char fechaNacimiento[20];  /// o se puede hacer con dia, mes, anio.
    int librosFavoritos[50]; /// se van a guardar los id de los libros favs.
    int validosLibrosFavs;
    char dni[10];
    stDomicilio domicilio;
    int eliminado; /// 0 si está activo - 1 si está eliminado
}stUsuario;

typedef struct nodoArbolUsuario{
    stUsuario usuario;
    struct nodoArbolUsuario * izq;
    struct nodoArbolUsuario * der;
}nodoArbolUsuario;


///Funciones arbol
nodoArbolUsuario * inicArbol();
nodoArbolUsuario * crearNodoArbol(stUsuario u);
nodoArbolUsuario * archivoToArbol(char nombreArchivo[],nodoArbolUsuario * arbol);
void arbolToArchivoAux(FILE *archi, nodoArbolUsuario *arbol);
void arbolToArchivo (char nombreArchivo[], nodoArbolUsuario * arbol);
nodoArbolUsuario * insertarNodoArbol(nodoArbolUsuario * arbol,nodoArbolUsuario * nuevo);
nodoArbolUsuario * crearNodoUser(nodoArbolUsuario * arbol);

///Funciones de busqueda
nodoArbolUsuario * buscarUsuario(char userIngresado[], nodoArbolUsuario * lista);
nodoArbolUsuario * buscarUsuarioXId(nodoArbolUsuario * arbol,int id);
///Funciones para mostrar
void muestraUnUsuario(stUsuario u);
void muestraNodoUser(nodoArbolUsuario * nodo);
void muestraArbol(nodoArbolUsuario * arbol);
void muestraArbolAdmin(nodoArbolUsuario * arbol);
void muestraNodoUserAdmin(nodoArbolUsuario * nodo);
void muestraUnUsuarioAdmin(stUsuario u);
///Funciones para verificar
int verificar(char userIngresado[],char claveIngresado[],nodoArbolUsuario * lista);
int verificarPassword(char claveIngresado[], nodoArbolUsuario * userAux);
int verificacionPasswordCondiciones(char password[]);
bool validarEmail(char email[]);
int verificarEmailEnArbol(char email[], nodoArbolUsuario * arbol);
///Funciones de carga
stUsuario crearUserAdmin();
nodoArbolUsuario * cargaUserAdmin(nodoArbolUsuario * arbol);
stUsuario cargaDatosUser(nodoArbolUsuario *  arbol);
stDomicilio cargaDomicilio();
stUsuario cargaDatosUserRandom();
stDomicilio cargaDomicilioRandom();
int sumarId(nodoArbolUsuario * arbol);
nodoArbolUsuario * nodoMasDerecho(nodoArbolUsuario * arbol);
void cargarUsuarioArchivoRandom(char nombreArchivo[], nodoArbolUsuario * arbol);

///Menu
nodoArbolUsuario * modificarDatos(nodoArbolUsuario * user,nodoArbolUsuario * arbol);
void opcionesModificarDatos();
void cambioUserName(char * userName);
stUsuario cambioPassword(stUsuario user);
void leerPassword(char *password, int maxLength);
void cambioGenero(char *genero);
void cambiarFechaNacimiento(char *fechaNacimiento);
void cambiarEmail(char *email,nodoArbolUsuario * arbol);
nodoArbolUsuario * darDeBajaUser(nodoArbolUsuario * user);
nodoArbolUsuario * darDeBajaUserAdmin(nodoArbolUsuario * arbol);
nodoArbolUsuario * darDeAltaUserAdmin(nodoArbolUsuario * arbol);
///Funciones de contenido Random (no las probe todavia)
int randomRangoUsuarios(int min, int max);
void setMailRandom(char email[]);
void setPasswordRandom(char password[]);
void setUsernameRandom(char username[]);
void setGeneroRandom(char genero[]);
void setFechaNacimientoRandom(char fechaNacimiento[]);
void setDniRandom(char dni[],int usados[], int *restantes);
void setCalleRandom(char calle[]);
void setAlturaRandom(int *altura);
void setCpRandom(int cp);
void setCiudadRandom(char ciudad[]);
void setLocalidadRandom(char localidad[]);
void setPaisRandom(char pais[]);

///Funciones de Favoritos
void agregarLibroAFavoritosUsuario(nodoArbolUsuario* nodoUsuario, nodo2Libros* listaLibros, int idLibro);
void mostrarLibrosFavoritos(nodoArbolUsuario* nodoUsuario, nodo2Libros* listaLibros);
void quitarLibroDeFavoritosUsuario(nodoArbolUsuario* nodoUsuario, int idLibro);
void opcionAgregarLibroAFavoritos(nodoArbolUsuario* usuario, nodo2Libros* libros);
void opcionQuitarLibroDeFavoritos(nodoArbolUsuario* usuario, nodo2Libros* libros);
#endif // USER_H_INCLUDED
