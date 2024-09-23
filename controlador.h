#ifndef CONTROLADOR_H_INCLUDED
#define CONTROLADOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <strings.h>
#include <time.h>
#include "user.h"
#include <stdbool.h>


void login (nodoListaUsuarios * lista);
nodoListaUsuarios * registrarse(nodoListaUsuarios * lista);

#endif // CONTROLADOR_H_INCLUDED
