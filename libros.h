#ifndef LIBROS_H_INCLUDED
#define LIBROS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>
#include "comentario.h"
 typedef struct {
 int idLibro; /// único, autoincremental
 char titulo[100];
 char editorial[50];
 char autor[50];
 char categoria[50];
 float valoracion;
 int eliminado; /// 0 si está activo- 1 si está eliminado
 }stLibro;

typedef struct nodo2Libros{
    stLibro dato;
    struct nodo2Libros * ste;
    struct nodo2Libros * ante;
    nodoComentario * lista;
}nodo2Libros;

///Carga de libros
stLibro cargaRandomLibro();
stLibro cargaUnLibro();
nodo2Libros *  cargarLibroEnLista(nodo2Libros*lista);
void cargarLibrosArchivoRandom(char nombreArchivo[]);
///Funciones de listas dobles
nodo2Libros * inicListaDoble();
nodo2Libros * crearNodoDoble(stLibro libro);
nodo2Libros * archivoToLista2(char nombreArchivo[], nodo2Libros * listaDoble);
///Funciones de agregar
nodo2Libros * insertarNodoPorId (nodo2Libros * lista, nodo2Libros * nuevoNodo);
nodo2Libros * agregarPrincipioLibro(nodo2Libros * listaDoble, nodo2Libros * nuevo);
nodo2Libros * agregarAlFinalLibro(nodo2Libros * listaDoble, nodo2Libros* nuevo);
nodo2Libros * alta (nodo2Libros *listaLibros, nodoComentario * nuevoComentario, int idLibro);
///Funciones de busqueda
nodo2Libros * buscarUltimoLibro(nodo2Libros* listaDoble);
void buscaLibrosPorAutor (nodo2Libros* lista);
void buscaLibrosPorCategoria (nodo2Libros* lista);
void buscaLibrosPorTitulo (nodo2Libros* lista);
nodo2Libros* buscarLibroPorId(nodo2Libros* lista, int id);
///Busqueda de Id para seguir incrementando
int buscarUltimoId (nodo2Libros* listaDoble);
///Dar de baja (eliminado=1)
void darDeBajaLogica (nodo2Libros* lista);
///Funciones para mostrar
void muestraUnLibro(stLibro a);
void muestraNodoDobleLibro(nodo2Libros * nodo);
void muestraListaLibros(nodo2Libros * lista);
void muestraListaLibrosAdmin (nodo2Libros * lista);
void verLibrosPorCategoria (nodo2Libros * lista, char categoria[]);
void verLibrosPorAutor (nodo2Libros * lista, char autor[]);
void verLibrosPorTitulo (nodo2Libros * lista, char titulo[]);
///Menu

///Funciones para crear contenido random
int randomRango(int min, int max);
void setTituloRandom(char titulo[]);
void setEditorialRandom(char editorial[]);
void setAutorRandom(char autor[]);
///Funcion de guardar en archivo
void agregarLibrosAlArchivo(nodo2Libros* lista,char nombreArchivo []);

#endif // LIBROS_H_INCLUDED
