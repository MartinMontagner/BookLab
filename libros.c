#include "libros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


///Funciones para crear contenido random
int randomRango(int min, int max)
{
    return  min +  rand()% (max - min +1);
}
void setTituloRandom(char titulo[])
{

    char arregloTitulos[][100] = {"Cien anios de soledad", "Don Quijote de la Mancha", "El gran Gatsby", "Moby Dick", "Guerra y paz", "Orgullo y prejuicio", "Matar a un ruisenior", "El guardian entre el centeno", "La Odisea", "La Divina Comedia", "Crimen y castigo", "Los hermanos Karamazov",
                                  "Un mundo feliz", "La Iliada", "1984", "El Señor de los Anillos", "Ana Karenina", "Ulises", "El ruido y la furia", "Cumbres borrascosas", "Los miserables", "El retrato de Dorian Gray", "Jane Eyre", "Fahrenheit 451", "Frankenstein", "Dracula", "El corazon de las tinieblas", "Grandes esperanzas",
                                  "Las aventuras de Huckleberry Finn", "Alicia en el pais de las maravillas", "El Hobbit", "Las uvas de la ira", "El extranjero", "El proceso", "Madame Bovary", "El viejo y el mar", "La metamorfosis", "El conde de Montecristo", "La letra escarlata", "La campana de cristal", "Beloved",
                                  "El cuento de la criada", "La carretera", "El hombre invisible", "Historia de dos ciudades", "Matadero cinco", "Lolita", "En el camino", "Cometas en el cielo", "Trampa 22", "El resplandor"
                                 };
    int cantTitulos=(sizeof(arregloTitulos) / sizeof(arregloTitulos[0]));
    int indiceAleatorio = randomRango(0, cantTitulos - 1);
    strcpy(titulo, arregloTitulos[indiceAleatorio]);
}

void setEditorialRandom(char editorial[])
{
    char arregloEditorial[][50] = {" Sudamericana", "Francisco de Robles", "Lumen", "Alfaguara",
                                   "Penguin Books", "Anagrama", "Alianza ", "Tusquets Editores", "Planeta", "Random House", "Salamandra",
                                   "Siruela", "Destino", "Plaza & Janes", "Ediciones B", "Seix Barral", "Edhasa", "Akal", "Turner", "Acantilado",
                                   "RBA", "Debolsillo", " Gredos", " Critica", "Nordica Libros", "Impedimenta", "Galaxia Gutenberg", "Minotauro", "Circulo de Lectores", "Alianza Literaria", "Austral", "Ediciones Catedra", "Biblioteca Castro", "Sexto Piso", "Siglo XXI",
                                   "Ediciones Siruela", "Pre-Textos", "Atalanta", "Errata Naturae", "Blackie Books", "Valdemar", "Nube de Tinta",
                                   "Oceano", "Libros del Asteroide", "Periferica", "Paginas de Espuma", " Renacimiento", " Trotta",
                                   "Espasa", "Kailas", "Arte y Literatura", "Funambulista"
                                  };
    int cantEditoriales=(sizeof(arregloEditorial) / sizeof(arregloEditorial[0]));
    int indiceAleatorio = randomRango(0, cantEditoriales - 1);
    strcpy(editorial, arregloEditorial[indiceAleatorio]);
}
void setAutorRandom(char autor[])
{
    char arregloAutores[][50] = {"Gabriel Garcia Marquez", "Miguel de Cervantes", "F. Scott Fitzgerald", "Herman Melville", "Leon Tolstoi", "Jane Austen", "Harper Lee", "J.D. Salinger", "Homero", "Dante Alighieri", "Fiodor Dostoievski", "Aldous Huxley",
                                 "George Orwell", "J.R.R. Tolkien", "Lev Tolstoi", "James Joyce", "William Faulkner",
                                 "Emily Bronte", "Victor Hugo", "Oscar Wilde", "Charlotte Bronte", "Ray Bradbury", "Mary Shelley",
                                 "Bram Stoker", "Joseph Conrad", "Charles Dickens", "Mark Twain", "Lewis Carroll", "John Steinbeck", "Albert Camus", "Franz Kafka", "Gustave Flaubert", "Ernest Hemingway", "Franz Kafka", "Alejandro Dumas", "Nathaniel Hawthorne", "Sylvia Plath", "Toni Morrison", "Margaret Atwood",
                                 "Cormac McCarthy", "Ralph Ellison", "Kurt Vonnegut", "Vladimir Nabokov", "Jack Kerouac", "Khaled Hosseini", "Stephen King", "Ken Kesey", "Henry James", "Jorge Luis Borges", "Virginia Woolf", "H.G. Wells", "George R.R. Martin"
                                };
    int cantAutores=(sizeof(arregloAutores) / sizeof(arregloAutores[0]));
    int indiceAleatorio = randomRango(0, cantAutores - 1);
    strcpy(autor, arregloAutores[indiceAleatorio]);
}
void setCategoria(char categoria[])
{
    char arregloCategoria[][50] = {"Novela", "Ciencia ficcion", "Fantasia", "Poesia", "Misterio", "Terror",
                                   "Romance", "Ficcion historica","Aventura", "Biografia"
                                  };
    int cantCategorias=(sizeof(arregloCategoria) / sizeof(arregloCategoria[0]));
    int indiceAleatorio = randomRango(0, cantCategorias - 1);
    strcpy(categoria, arregloCategoria[indiceAleatorio]);
}
///Carga de libros
stLibro cargaUnLibro(nodo2Libros * listaDoble)
{

    stLibro aux;
    int ultimo=buscarUltimoId(listaDoble);
    int id=ultimo;
    id++;
    aux.idLibro=id;
    /*idLibro*/
    printf("Ingrese el titulo del libro: \n");
    fflush(stdin);
    gets(aux.titulo);

    printf("Ingrese la editorial: \n");
    fflush(stdin);
    gets(aux.editorial);

    printf("Ingrese el autor: \n");
    fflush(stdin);
    gets(aux.autor);

    printf("Ingrese la categoria: \n");
    fflush(stdin);
    gets(aux.categoria);

    /*printf("Ingrese la valoracion: \n");
    fflush(stdin);
    scanf("%f", &aux.valoracion);*/
    aux.eliminado=0;

    return aux;
}

stLibro cargaRandomLibro()
{

    stLibro libro;
    static int id=0;
    id++;
    libro.idLibro=id;
    setTituloRandom(libro.titulo);
    setEditorialRandom(libro.editorial);
    setAutorRandom(libro.autor);
    setCategoria(libro.categoria);
    libro.eliminado=0;
    libro.valoracion=0;
    return libro;
}
///Busqueda de Id para seguir incrementando
int buscarUltimoId (nodo2Libros* listaDoble)
{
    nodo2Libros * ultimo= buscarUltimoLibro(listaDoble);
    int id=0;
    id=ultimo->dato.idLibro;
    return id;
}
///Funciones de listas que devuelven listas
nodo2Libros * inicListaDoble()
{
    return NULL;
}
nodo2Libros * crearNodoDoble(stLibro libro)
{

    nodo2Libros * nuevo = (nodo2Libros*)malloc(sizeof(nodo2Libros));
    nuevo->dato = libro;
    nuevo->ste = NULL;
    nuevo->ante = NULL;

    return nuevo;
}

nodo2Libros * agregarPrincipioLibro(nodo2Libros * listaDoble, nodo2Libros * nuevo)
{
    nuevo->ste = listaDoble;
    if(listaDoble)
    {
        listaDoble->ante = nuevo;
    }
    return nuevo;
}

nodo2Libros * agregarAlFinalLibro(nodo2Libros * listaDoble, nodo2Libros* nuevo)
{
    if(!listaDoble)
    {
        listaDoble = nuevo;
    }
    else
    {
        nodo2Libros* ultimo = buscarUltimoLibro(listaDoble);
        ultimo->ste = nuevo;
        nuevo->ante = ultimo;
    }

    return listaDoble;
}
nodo2Libros * agregarAlFinalLibroCopia(nodo2Libros * listaDoble, nodo2Libros* nuevo)
{
    nodo2Libros* nuevoNodo= crearNodoDoble(nuevo->dato);
    nuevoNodo->ante=listaDoble;
    nuevoNodo->ste=NULL;

    if(!listaDoble)
    {
        listaDoble = nuevoNodo;
    }
    else
    {
        nodo2Libros* ultimo = buscarUltimoLibro(listaDoble);
        ultimo->ste = nuevoNodo;
        nuevoNodo->ante = ultimo;
    }

    return listaDoble;
}
nodo2Libros *agregarPrincipioLibroCopia(nodo2Libros *lista, nodo2Libros *nodoOriginal)
{
    nodo2Libros* nuevoNodo= crearNodoDoble(nodoOriginal->dato);
    nuevoNodo->ste=lista;
    if (lista != NULL)
    {
        lista->ante = nuevoNodo;
    }

    return nuevoNodo;
}
//Funciones de busqueda
nodo2Libros* buscarUltimoLibro(nodo2Libros* listaDoble)
{
    nodo2Libros * seg = listaDoble;
    while(seg->ste != NULL)
    {
        seg = seg->ste;
    }
    return seg;
}
//preguntar si esta ok
nodo2Libros * buscaLibrosPorCategoria (nodo2Libros * lista, char categoria[])
{
    nodo2Libros * listaCategoria= NULL;
    nodo2Libros * actual= lista;
    if(lista)
    {
        while (actual)
        {
            if(strcmpi(actual->dato.categoria,categoria)==0)
            {
                listaCategoria=agregarAlFinalLibroCopia(listaCategoria,actual);
            }
            actual=actual->ste;
        }
    }
    if(!listaCategoria)
    {
        printf("\nNo existen libros de esa categoria\n");
    }
    return listaCategoria;
}
nodo2Libros * buscaLibrosPorAutor (nodo2Libros * lista, char autor[])
{
    nodo2Libros * listaAutor= NULL;
    nodo2Libros * actual= lista;
    if(lista)
    {
        while (actual)
        {
            if(strcmpi(actual->dato.autor,autor)==0)
            {
                listaAutor=agregarAlFinalLibroCopia(listaAutor,actual);
            }
            actual=actual->ste;
        }
    }
    if(!listaAutor)
    {
        printf("\nNo encontramos libros de ese autor\n");
    }
    return listaAutor;
}
nodo2Libros * buscaLibrosPorTitulo (nodo2Libros * lista, char titulo[])
{
    nodo2Libros * listaTitulo= NULL;
    nodo2Libros * actual= lista;
    if(lista)
    {
        while (actual)
        {
            if(strcmpi(actual->dato.titulo,titulo)==0)
            {
                listaTitulo=agregarAlFinalLibroCopia(listaTitulo,actual);
            }
            actual=actual->ste;
        }
    }
    if(!listaTitulo)
    {
        printf("\nNo encontramos libros con ese titulo\n");
    }
    return listaTitulo;
}

nodo2Libros *insertarNodoPorId (nodo2Libros * lista, nodo2Libros * nuevoNodo)
{
    if(lista==NULL)
    {
        lista=nuevoNodo;
    }
    else if (nuevoNodo->dato.idLibro < lista->dato.idLibro)
    {
        lista=agregarPrincipioLibro(lista,nuevoNodo);
    }
    else
    {
        nodo2Libros * anterior=lista;
        nodo2Libros * seg=lista->ste;

        while (seg!=NULL && seg->dato.idLibro < nuevoNodo->dato.idLibro)
        {
            anterior=seg;
            seg=seg->ste;
        }
        anterior->ste=nuevoNodo;
        nuevoNodo->ante=anterior;
        nuevoNodo->ste=seg;

        if(seg!=NULL)
        {
            seg->ante=nuevoNodo;
        }
    }
    return lista;
}
nodo2Libros * borrarPrimerNodoListaLibros(nodo2Libros * lista)
{
    nodo2Libros * aBorrar = NULL;

    if(lista)
    {
        aBorrar = lista;
        lista = lista->ste;
        if(lista)
        {
            lista->ante = NULL;
        }
        free(aBorrar);
    }
    return lista;
}
///Funciones para mostrar
void muestraUnLibro(stLibro a)
{

    printf("\n-----------------------\n");
    printf("Nombre: ..............%s\n",a.titulo);
    printf("Editorial: ..............%s\n",a.editorial);
    printf("Autor: ..............%s\n",a.autor);
    printf("Categoria: ................%s\n",a.categoria);
    printf("ID: ................%d\n",a.idLibro);
    printf("\n-----------------------\n");
}

void muestraNodoDobleLibro(nodo2Libros * nodo)
{
    muestraUnLibro(nodo->dato);
}
void muestraListaLibros(nodo2Libros * lista)
{

    while(lista)
    {
        muestraNodoDobleLibro(lista);
        lista = lista->ste;
    }
}
