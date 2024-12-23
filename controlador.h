#ifndef CONTROLADOR_H_INCLUDED
#define CONTROLADOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>
#include <unistd.h>

#include "user.h"


void login (nodoArbolUsuario * arbol);
nodoArbolUsuario * registrarse(nodoArbolUsuario * arbol);
void setColor(int color);
void escribirConRetraso(const char *texto, int delay);
nodoArbolUsuario * menuUser(nodoArbolUsuario * user,nodoArbolUsuario * arbol);
void mostrarMenuUser();
void mostrarMenuLibros();
void menuLibros( nodoArbolUsuario * user);
void mostrarMenuAdmin();
void menuAdmin(nodoArbolUsuario * arbol);
void mostrarMenuComentario();
nodo2Libros * menuComentario( nodoArbolUsuario * user, nodo2Libros * ldl);

#endif // CONTROLADOR_H_INCLUDED
