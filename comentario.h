#ifndef COMENTARIO_H_INCLUDED
#define COMENTARIO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>
#include <unistd.h>


typedef struct {
    int idComentario;  /// único, autoincremental
    int idLibro;
    int idUsuario;
    char tituloComentario[100];
    char descripcion[500];
    int puntaje; /// de 0 a 5 "estrellas"
    char fechaComentario[20]; /// o se puede hacer con dia, mes, anio.
    int eliminado; /// 0 si está activo - 1 si está eliminado
}stComentario;


typedef struct nodoComentario{
    stComentario comentario;
    struct nodoComentario * ste;
    struct nodoComentario * ante;
}nodoComentario;

stComentario cargaUnComentario();
nodoComentario * inicListaComentario();
nodoComentario * crearNodoComentario(stComentario coment);
nodoComentario * buscarUltimoComentario (nodoComentario * lista);
int buscarUltimoIdComentario (nodoComentario * lista);
nodoComentario * cargarComentarioEnLista(nodoComentario * lista, int idLibro, int idUsuario);
float calculoValoraciones (nodoComentario * lista, int idLibro);
nodoComentario * agregarFinal(nodoComentario * lista, nodoComentario * nuevoNodo);
nodoComentario * agregarPrincipioComentario(nodoComentario * lista, nodoComentario * nuevo);
nodoComentario * insertarNodoPorIdComentario (nodoComentario * lista, nodoComentario * nuevoNodo);
nodoComentario *  archivoToListaComentario(char nombreArchivo[], nodoComentario * listaDoble);
///Funciones para cambiar el comentario
nodoComentario * cambioTitulo(nodoComentario * lista);
nodoComentario * cambioDescripcion(nodoComentario * lista);
nodoComentario * cambioPuntaje (nodoComentario * lista);
nodoComentario * eliminarComentario(nodoComentario * lista);
//nodoComentario * modificarComentario(nodoComentario * lista);

///Funciones para mostrar
void muestraUnComentario (stComentario a);
void muestraNodoComentario(nodoComentario * nodo);
void muestraListaComentarios(nodoComentario * lista);
void muestraListaComentariosAdmin (nodoComentario * lista);
void opcionesModificarComentario();

///FALTA TERMINAR MENUS, FUNCION DE GUARDAR COMENTARIOS EN EL ARCHIVO. PENSAR DONDE PONER MENU COMENTARIO, Y DONDE PONER LA OPCION DE VER TODOS LOS COMENTARIOS.
void agregarComentariosAlArchivo(nodoComentario* lista,char nombreArchivo []);
nodoComentario * buscarComentarioPorId(nodoComentario* lista, int id);
#endif // COMENTARIO_H_INCLUDED
