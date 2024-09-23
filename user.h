#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <strings.h>
#include <time.h>
#include <stdbool.h>

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

typedef struct{
    stUsuario usuario;
    struct nodoListaUsuarios * sig;
}nodoListaUsuarios;

//funcion de login
//verificacion mail
//verificacion user
//verificacion password
//verificacion que la password este bien contemplando las reglas
nodoListaUsuarios * inicLista();
nodoListaUsuarios * crearNodo(stUsuario usuario);
nodoListaUsuarios * agregarPrincipio(nodoListaUsuarios * lista, nodoListaUsuarios * nuevoNodo);
void muestraUnUsuario(stUsuario u);
void muestraNodoUser(nodoListaUsuarios * nodo);
void muestraLista(nodoListaUsuarios * lista);
nodoListaUsuarios* buscarUltimo(nodoListaUsuarios* lista);
nodoListaUsuarios* agregarAlFinal(nodoListaUsuarios* lista, nodoListaUsuarios* nuevo);
nodoListaUsuarios * agregarEnOrdenId(nodoListaUsuarios * lista, nodoListaUsuarios * nuevo);
int verificar(char userIngresado[],char claveIngresado[],nodoListaUsuarios * lista);
nodoListaUsuarios * buscarUsuario(char userIngresado[], nodoListaUsuarios * lista);
int verificarPassword(char claveIngresado[], nodoListaUsuarios * userAux);
int verificacionPasswordCondiciones(char password[]);
nodoListaUsuarios * crearNodoUser(nodoListaUsuarios * lista);
stUsuario cargaDatosUser();
stDomicilio cargaDomicilio();
stUsuario sumarId(stUsuario user, nodoListaUsuarios * lista);
bool validarEmail(char email[]);

#endif // USER_H_INCLUDED
