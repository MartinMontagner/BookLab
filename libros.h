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

stLibro cargaUnLibro();
nodo2Libros * inicListaDoble();
nodo2Libros *insertarNodoPorId (nodo2Libros * lista, nodo2Libros * nuevoNodo);
nodo2Libros * crearNodoDoble(stLibro libro);
nodo2Libros *  archivoToLista2(char nombreArchivo[], nodo2Libros * listaDoble);
void muestraUnLibro(stLibro a);
int randomRango(int min, int max);
void setTituloRandom(char titulo[]);
void setEditorialRandom(char editorial[]);
void setAutorRandom(char autor[]);

#endif // LIBROS_H_INCLUDED
