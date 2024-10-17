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
#include "libros.h"

void login (nodoListaUsuarios * lista);
nodoListaUsuarios * registrarse(nodoListaUsuarios * lista);
void setColor(int color);
void escribirConRetraso(const char *texto, int delay);
void menuUser();
void mostrarMenuUser();
void mostrarMenuLibros();
void menuLibros( nodoListaUsuarios * user);
void mostrarMenuAdmin();
void menuAdmin();
#endif // CONTROLADOR_H_INCLUDED
