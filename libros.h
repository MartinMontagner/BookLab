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
    nodo2Libros * ste;
    nodo2Libros * ante;
}nodo2Libros;

stLibro cargaUnLibro();
nodo2Libros * inicListaDoble();

#endif // LIBROS_H_INCLUDED
