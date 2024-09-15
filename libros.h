#ifndef LIBROS_H_INCLUDED
#define LIBROS_H_INCLUDED

 typedef struct{
 int idLibro; /// único, autoincremental
 char titulo[100];
 char editorial[50];
 char autor[50];
 char categoria[50];
 float valoracion;
 int eliminado; /// 0 si está activo- 1 si está eliminado
 }stLibro;

 typedef struct{
    stLibro dato;
    struct nodo2Libros * ste;
    struct nodo2Libros * ante;
}nodo2Libros;
///Carga de libros
stLibro cargaRandomLibro();
stLibro cargaUnLibro(nodo2Libros * listaDoble);
void * cargarLibroEnLista(nodo2Libros*lista);
///Funciones de listas que devuelven listas
nodo2Libros * inicListaDoble();
nodo2Libros * insertarNodoPorId (nodo2Libros * lista, nodo2Libros * nuevoNodo);
nodo2Libros * crearNodoDoble(stLibro libro);
nodo2Libros * agregarPrincipioLibro(nodo2Libros * listaDoble, nodo2Libros * nuevo);
nodo2Libros * agregarPrincipioLibroCopia(nodo2Libros *lista, nodo2Libros *nodoOriginal);
nodo2Libros * agregarAlFinalLibro(nodo2Libros * listaDoble, nodo2Libros* nuevo);
nodo2Libros * agregarAlFinalLibroCopia(nodo2Libros * listaDoble, nodo2Libros* nuevo);
nodo2Libros * borrarPrimerNodoListaLibros(nodo2Libros * lista);
//Funciones de busqueda
nodo2Libros * buscarUltimoLibro(nodo2Libros* listaDoble);
nodo2Libros * buscaLibrosPorCategoria (nodo2Libros * lista, char categoria[]);
nodo2Libros * buscaLibrosPorAutor (nodo2Libros * lista, char autor[]);
nodo2Libros * buscaLibrosPorTitulo (nodo2Libros * lista, char titulo[]);
///Busqueda de Id para seguir incrementando
int buscarUltimoId (nodo2Libros* listaDoble);
///Funciones para mostrar
void muestraUnLibro(stLibro a);
void muestraNodoDobleLibro(nodo2Libros * nodo);
void muestraListaLibros(nodo2Libros * lista);
void verLibrosPorTitulo (nodo2Libros* lista);
void verLibrosPorCategoria (nodo2Libros* lista);
void verLibrosPorAutor (nodo2Libros* lista);
///Funciones para crear contenido random
int randomRango(int min, int max);
void setTituloRandom(char titulo[]);
void setEditorialRandom(char editorial[]);
void setAutorRandom(char autor[]);

#endif // LIBROS_H_INCLUDED
