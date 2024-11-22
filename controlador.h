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
//#include "libros.h"

void login (nodoArbolUsuario * arbol);
nodoArbolUsuario * registrarse(nodoArbolUsuario * arbol);
void setColor(int color);
void escribirConRetraso(const char *texto, int delay);
void menuUser(nodoArbolUsuario * user);
void mostrarMenuUser();
void mostrarMenuLibros();
void menuLibros( nodoArbolUsuario * user);
void mostrarMenuAdmin();
void menuAdmin(nodoArbolUsuario * arbol);
void mostrarMenuComentario();
#endif // CONTROLADOR_H_INCLUDED
