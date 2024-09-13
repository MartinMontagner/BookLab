#include "libros.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
stLibro cargaUnLibro()
{

    stLibro aux;
    idLibro
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
    scanf("%d", &aux.categoria);

    /*printf("Ingrese la valoracion: \n");
    fflush(stdin);
    scanf("%f", &aux.valoracion);*/
    aux.eliminado=0;

    return aux;
}
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

int randomRango(int min, int max)
{
    return  min +  rand()% (max - min +1);
}
void setTituloRandom(char titulo[])
{

    char arreglosTitulos[][100] = {"Cien años de soledad", "Don Quijote de la Mancha", "El gran Gatsby", "Moby Dick", "Guerra y paz", "Orgullo y prejuicio", "Matar a un ruiseñor", "El guardian entre el centeno", "La Odisea", "La Divina Comedia", "Crimen y castigo", "Los hermanos Karamazov",
                                   "Un mundo feliz", "La Iliada", "1984", "El Señor de los Anillos", "Ana Karenina", "Ulises", "El ruido y la furia", "Cumbres borrascosas", "Los miserables", "El retrato de Dorian Gray", "Jane Eyre", "Fahrenheit 451", "Frankenstein", "Dracula", "El corazon de las tinieblas", "Grandes esperanzas",
                                   "Las aventuras de Huckleberry Finn", "Alicia en el pais de las maravillas", "El Hobbit", "Las uvas de la ira", "El extranjero", "El proceso", "Madame Bovary", "El viejo y el mar", "La metamorfosis", "El conde de Montecristo", "La letra escarlata", "La campana de cristal", "Beloved",
                                   "El cuento de la criada", "La carretera", "El hombre invisible", "Historia de dos ciudades", "Matadero cinco", "Lolita", "En el camino", "Cometas en el cielo", "Trampa 22", "El resplandor"
                                  };

    strcpy(titulo,arreglosTitulos[randomRango(0,sizeof(arreglosTitulos)/100)]);
}

void setEditorialRandom(char editorial[])
{
    char arregloEditorial[][50] = {" Sudamericana", "Francisco de Robles", "Lumen", "Alfaguara",
                                   "Penguin Books", "Anagrama", "Alianza ", "Tusquets Editores", "Planeta", "Random House", "Salamandra",
                                   "Siruela", "Destino", "Plaza & Janes", "Ediciones B", "Seix Barral", "Edhasa", "Akal", "Turner", "Acantilado",
                                   "RBA", "Debolsillo", " Gredos", " Crítica", "Nordica Libros", "Impedimenta", "Galaxia Gutenberg", "Minotauro", "Circulo de Lectores", "Alianza Literaria", "Austral", "Ediciones Catedra", "Biblioteca Castro", "Sexto Piso", "Siglo XXI",
                                   "Ediciones Siruela", "Pre-Textos", "Atalanta", "Errata Naturae", "Blackie Books", "Valdemar", "Nube de Tinta",
                                   "Oceano", "Libros del Asteroide", "Periférica", "Páginas de Espuma", " Renacimiento", " Trotta",
                                   "Espasa", "Kailas", "Arte y Literatura", "Funambulista"
                                  };

    strcpy(editorial, arregloEditorial[randomRango(0,sizeof(arregloEditorial)/50)]);
}
void setAutorRandom(char autor[])
{
    char arregloAutores[][50] = {"Gabriel Garcia Marquez", "Miguel de Cervantes", "F. Scott Fitzgerald", "Herman Melville", "Leon Tolstoi", "Jane Austen", "Harper Lee", "J.D. Salinger", "Homero", "Dante Alighieri", "Fiodor Dostoievski", "Aldous Huxley",
                                 "George Orwell", "J.R.R. Tolkien", "Lev Tolstoi", "James Joyce", "William Faulkner",
                                 "Emily Bronte", "Victor Hugo", "Oscar Wilde", "Charlotte Bronte", "Ray Bradbury", "Mary Shelley",
                                 "Bram Stoker", "Joseph Conrad", "Charles Dickens", "Mark Twain", "Lewis Carroll", "John Steinbeck", "Albert Camus", "Franz Kafka", "Gustave Flaubert", "Ernest Hemingway", "Franz Kafka", "Alejandro Dumas", "Nathaniel Hawthorne", "Sylvia Plath", "Toni Morrison", "Margaret Atwood",
                                 "Cormac McCarthy", "Ralph Ellison", "Kurt Vonnegut", "Vladimir Nabokov", "Jack Kerouac", "Khaled Hosseini", "Stephen King", "Ken Kesey", "Henry James", "Jorge Luis Borges", "Virginia Woolf", "H.G. Wells", "George R.R. Martin"
                                };

    strcpy(autor, arregloAutor[randomRango(0,sizeof(arregloAutores)/50)]);
}
stAlumno cargaRandomLibro()
{

    stLibro libro;

    char apellidoAux[30];

    setTituloRandom(libro.titulo);

    /*strcat(alumno.nombre, " ");
    setApellidoRandom(apellidoAux);
    strcat(alumno.nombre, apellidoAux);*/

    setDni(alumno.dni);
    alumno.genero = getGenero();
    alumno.nota = randomRango(1,10);


    return alumno;

}

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


nodo2Libros *  archivoToLista2(char nombreArchivo[], nodo2Libros * listaDoble)
{

    FILE * buffer = fopen(nombreArchivo, "rb");
    stLibro aux;


    if(buffer)
    {
        while(fread(&aux, sizeof(stLibro), 1, buffer) > 0)
        {
            lista = agregarEnOrdenDNI(listaDoble,crearNodoDoble(aux));//agregarEnOrden ?
        }
        fclose(buffer);
    }

    return lista;

}

nodoDoble* borrarNodoPorDni (nodoDoble * lista, char dniBusca[])
{
    nodoDoble*actual= NULL;
    nodoDoble*aux=NULL;
    nodoDoble*seg=NULL;
    int flag=0;
    if(lista )
    {
        if( strcmp(lista->dato.dni,dniBusca)==0)
        {
            actual=lista;
            lista=lista->sig;
            if(lista)
            {
                lista->ante=NULL;
            }
            free(actual);
        }
        else
        {
            seg=lista;
            while(seg && strcmp(seg->dato.dni,dniBusca)!=0)
            {
                {
                    ante=seg;
                    seg=seg->sig;
                }
                if(seg)
                {
                    ante->sig=seg->sig;
                    seg->ante=ante;
                    free(seg);
                }
            }
        }
    }
    return lista;
}
nodo2Libros * agregarEnOrdenId(nodo2Libros * lista, nodo2Libros * nuevo)
{

    if(!lista)
    {
        lista = nuevo;
    }
    else
    {
        nodo2Libros* aux = lista; // ante
        if(atoi(aux->dato.id) > atoi(nuevo->dato.dni))
        {
            lista = agregarPrincipio(aux,nuevo);
        }
        else
        {
            nodoSimple * seg = lista;

            while(seg && atoi(aux->dato.dni) < atoi(nuevo->dato.dni))
            {
                aux = seg;
                seg = seg->sig;
            }

            aux->sig = nuevo;
            nuevo->sig = seg;


        }

    }

    return lista;


}
