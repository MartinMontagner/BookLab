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
    int idUsuario;
    char email[100];
    char password[20];
    char username[20];
    int esAdmin;  /// 1 = si  0 = no
    char genero;
    char fechaNacimiento[20];  /// o se puede hacer con dia, mes, anio.
    int librosFavoritos[50]; /// se van a guardar los id de los libros favs.
    int validosLibrosFavs;
    char dni[10];
    stDomicilio domicilio;
    int eliminado; /// 0 si está activo - 1 si está eliminado
}stUsuario;

typedef struct nodoListaUsuarios {
    stUsuario usuario;
    struct nodoListaUsuarios * sig;
}nodoListaUsuarios;


nodoListaUsuarios * inicLista();
nodoListaUsuarios * crearNodo(stUsuario usuario);
nodoListaUsuarios * crearNodoUser(nodoListaUsuarios * lista);
nodoListaUsuarios *  archivoToLista(char nombrearchivo[], nodoListaUsuarios * lista);
void listaToArchivo(char nombreArchivo[], nodoListaUsuarios * lista);
///Funciones para agregar
nodoListaUsuarios * agregarPrincipio(nodoListaUsuarios * lista, nodoListaUsuarios * nuevoNodo);
nodoListaUsuarios* agregarAlFinal(nodoListaUsuarios* lista, nodoListaUsuarios* nuevo);
nodoListaUsuarios * agregarEnOrdenId(nodoListaUsuarios * lista, nodoListaUsuarios * nuevo);
///Funciones de busqueda
nodoListaUsuarios * buscarUsuario(char userIngresado[], nodoListaUsuarios * lista);
nodoListaUsuarios* buscarUltimo(nodoListaUsuarios* lista);
nodoListaUsuarios * buscarUsuarioXId(nodoListaUsuarios * lista,int id);
int buscarUltimoIdUsuario (nodoListaUsuarios * lista);
///Funciones para mostrar
void muestraUnUsuario(stUsuario u);
void muestraNodoUser(nodoListaUsuarios * nodo);
void muestraLista(nodoListaUsuarios * lista);
///Funciones para verificar
int verificar(char userIngresado[],char claveIngresado[],nodoListaUsuarios * lista);
int verificarPassword(char claveIngresado[], nodoListaUsuarios * userAux);
int verificacionPasswordCondiciones(char password[]);
bool validarEmail(char email[]);
///Funciones de carga
stUsuario crearUserAdmin();
nodoListaUsuarios * cargaUserAdmin(stUsuario admin, nodoListaUsuarios * listaUser);
stUsuario cargaDatosUser();
stDomicilio cargaDomicilio();
stUsuario cargaDatosUserRandom();
stDomicilio cargaDomicilioRandom();
void cargarUsuarioArchivoRandom(char nombreArchivo[], nodoListaUsuarios * lista);
int sumarId(stUsuario user, nodoListaUsuarios * lista);

///Menu
nodoListaUsuarios * modificarDatos(nodoListaUsuarios * user);
void opcionesModificarDatos();
stUsuario cambioUserName(stUsuario user);
stUsuario cambioPassword(stUsuario user);
void leerPassword(char *password, int maxLength);
void cambioGenero(char *genero);
void cambiarFechaNacimiento(char *fechaNacimiento);
void cambiarDNI(char *dni);
nodoListaUsuarios * darDeBajaUser(nodoListaUsuarios * user);
nodoListaUsuarios * darDeBajaUserAdmin(nodoListaUsuarios * lista);
///Funciones de contenido Random (no las probe todavia)
int randomRangoUsuarios(int min, int max);
void setMailRandom(char email[]);
void setPasswordRandom(char password[]);
void setUsernameRandom(char username[]);
void setGeneroRandom(char genero[]);
void setFechaNacimientoRandom(char fechaNacimiento[]);
void setDniRandom(char dni[],int usados[], int *restantes);
void setCalleRandom(char calle[]);
void setAlturaRandom(int altura);
void setCpRandom(int cp);
void setCiudadRandom(char ciudad[]);
void setLocalidadRandom(char localidad[]);
void setPaisRandom(char pais[]);

///Funciones de Favoritos
void agregarLibroAFavoritosUsuario(nodoListaUsuarios* nodoUsuario, nodo2Libros* listaLibros, int idLibro);
void mostrarLibrosFavoritos(nodoListaUsuarios* nodoUsuario, nodo2Libros* listaLibros);
void quitarLibroDeFavoritosUsuario(nodoListaUsuarios* nodoUsuario, int idLibro);
void opcionAgregarLibroAFavoritos(nodoListaUsuarios* usuario, nodo2Libros* libros);
void opcionQuitarLibroDeFavoritos(nodoListaUsuarios* usuario, nodo2Libros* libros);
#endif // USER_H_INCLUDED
