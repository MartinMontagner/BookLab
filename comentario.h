#ifndef COMENTARIO_H_INCLUDED
#define COMENTARIO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>


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


typedef struct{
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
///Funciones para mostrar
void muestraUnComentario (stComentario a);
void muestraNodoComentario(nodoComentario * nodo);
void muestraListaComentarios(nodoComentario * lista);
void muestraListaComentariosAdmin (nodoComentario * lista);

#endif // COMENTARIO_H_INCLUDED
