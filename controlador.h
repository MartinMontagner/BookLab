#ifndef CONTROLADOR_H_INCLUDED
#define CONTROLADOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <strings.h>
#include <time.h>
#include "user.h"
#include <stdbool.h>
#include <windows.h>


void login (nodoListaUsuarios * lista);
nodoListaUsuarios * registrarse(nodoListaUsuarios * lista);
void menuPrincipal(char archivoUser[], nodoListaUsuarios * listaUser);
void setColor(int color);
void escribirConRetraso(const char *texto, int delay);
void mostrarMenuInicial();
void mostrarMenuUser();
void menuUser();
#endif // CONTROLADOR_H_INCLUDED
