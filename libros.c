#include "libros.h"



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
stLibro cargaUnLibro()
{

    stLibro aux;

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
nodo2Libros * cargarLibroEnLista(nodo2Libros * lista)
{
    stLibro libro1;
    char opcion='s';
    while(opcion=='s')
    {
        libro1=cargaUnLibro();
        libro1.idLibro=buscarUltimoId(lista)+1;
        lista=insertarNodoPorId(lista,crearNodoDoble(libro1));
        printf("\nDesea seguir agregando?s/n\n");
        opcion = getchar();
        while (getchar() != '\n');
    }
    return lista;
}
void cargarLibrosArchivoRandom(char nombreArchivo[])
{

    FILE * buffer = fopen(nombreArchivo,"ab");
    stLibro aux;
    char opcion = 0;
    int i = 0;


    if(buffer)
    {
        do
        {
            printf("Libro %d\n", i);
            aux = cargaRandomLibro();
            fwrite(&aux,sizeof(stLibro),1,buffer);
            i++;

            printf("Desea seguir cargando? Presione 'n' para salir \n");
            fflush(stdin);
            scanf("%c",&opcion);
        }
        while(opcion != 'n');
        fclose(buffer);

    }
}
///FUNCION ALTA
nodo2Libros * alta (nodo2Libros *listaLibros, nodoComentario * nuevoComentario, int idLibro)
{
    nodo2Libros * libroEncontrado = buscarLibroPorId(listaLibros,idLibro);
    if(libroEncontrado==NULL)
    {
        stLibro libro = cargaUnLibro();
        libro.idLibro=idLibro;
        libro.valoracion= calculoValoraciones(listaLibros->lista,listaLibros->dato.idLibro);
        nodo2Libros *nuevoLibro = crearNodoDoble(libro);
        listaLibros = insertarNodoPorId(listaLibros, nuevoLibro);
        listaLibros->lista = insertarNodoPorIdComentario(listaLibros->lista, nuevoComentario);
    }
    else
    {
        libroEncontrado->lista = insertarNodoPorIdComentario(libroEncontrado->lista, nuevoComentario);
        libroEncontrado->dato.valoracion= calculoValoraciones(libroEncontrado->lista,libroEncontrado->dato.idLibro);
    }
    return listaLibros;
}
nodo2Libros * ingresarLibros (nodo2Libros *lista, int idUsuario)
{
    char continuar='s';
    stComentario aux;
    int idLibro;

    while(continuar=='s')
    {
        aux=cargaUnComentario();
        printf("\nA que libro desea ingresar el comentario?: \n");
        fflush(stdin);
        scanf("%d", &aux.idLibro);
        aux.idUsuario=idUsuario;
        idLibro=aux.idLibro;
        nodoComentario * coment = crearNodoComentario(aux);
        lista = alta(lista,coment,idLibro);
        printf("\n\nDesea continuar presione s:  ");
        fflush(stdin);
        scanf("%c", &continuar);
        printf("\n\n");
    }
    return lista;
}


void mostrarComentariosUsuario(nodo2Libros * listaLibros, int idUsuario) {
    nodo2Libros * libroActual = listaLibros;
    int comentariosEncontrados = 0;

    printf("\nComentarios del usuario con ID %d:\n", idUsuario);

    while (libroActual != NULL) {
        nodoComentario * comentarioActual = libroActual->lista;

        // Recorrer todos los comentarios de cada libro
        while (comentarioActual != NULL) {
            if (comentarioActual->comentario.idUsuario == idUsuario) {
                // Mostrar comentario solo si pertenece al usuario
                comentariosEncontrados++;
                printf("\nLibro: %s (ID: %d)\n", libroActual->dato.titulo, libroActual->dato.idLibro);
                muestraNodoComentario(comentarioActual);
                printf("----------------------------------------------------\n");
            }
            comentarioActual = comentarioActual->ste;
        }
        libroActual = libroActual->ste;
    }

    if (comentariosEncontrados == 0) {
        printf("No se encontraron comentarios para este usuario.\n");
    }
}




nodo2Libros *  archivoToLista2(char nombreArchivo[], nodo2Libros * listaDoble)
{

    FILE * buffer = fopen(nombreArchivo, "rb");
    stLibro aux;


    if(buffer)
    {
        while(fread(&aux, sizeof(stLibro), 1, buffer) > 0)
        {
            listaDoble = insertarNodoPorId(listaDoble,crearNodoDoble(aux));
        }
        fclose(buffer);
    }

    return listaDoble;
}

///Busqueda de Id para seguir incrementando
int buscarUltimoId (nodo2Libros* listaDoble)
{
    nodo2Libros * ultimo= buscarUltimoLibro(listaDoble);
    int id=ultimo->dato.idLibro;
    return id;
}
///Funciones de listas
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
    nuevo->lista=NULL;
    return nuevo;
}
///Funciones para agregar
void agregarLibrosAlArchivo(nodo2Libros* lista,char nombreArchivo [])
{
    FILE *archivo = fopen(nombreArchivo, "wb");

    if (!archivo)
    {
        printf("Error al abrir el archivo.\n");
    }

    nodo2Libros* actual = lista;


    while (actual)
    {

        fwrite(&actual->dato, sizeof(stLibro), 1, archivo);
        actual = actual->ste;
    }

    fclose(archivo);
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

///Funciones de busqueda
nodo2Libros* buscarUltimoLibro(nodo2Libros* listaDoble)
{
    nodo2Libros * seg = listaDoble;
    while(seg->ste != NULL)
    {
        seg = seg->ste;
    }
    return seg;
}

void buscaLibrosPorAutor (nodo2Libros* lista)
{
    char autor[50];
    printf("\nIngrese el autor que desea buscar: \n");
    fflush(stdin);
    gets(autor);
    verLibrosPorAutor(lista,autor);
}
void buscaLibrosPorCategoria (nodo2Libros* lista)
{
    char categoria[50];
    printf("\nIngrese la categoria que desea buscar: \n");
    fflush(stdin);
    gets(categoria);
    verLibrosPorCategoria(lista,categoria);
}
void buscaLibrosPorTitulo (nodo2Libros* lista)
{
    char titulo[50];
    printf("\nIngrese el titulo que desea buscar: \n");
    fflush(stdin);
    gets(titulo);
    verLibrosPorTitulo(lista,titulo);
}
nodo2Libros* buscarLibroPorId(nodo2Libros* lista, int id)
{
    nodo2Libros* actual = lista;
    int flag=0;
    while (actual != NULL && flag==0)
    {
        if (actual->dato.idLibro == id)
        {
            flag=1;
        }
        actual = actual->ste;
    }
    return actual;
}

///Funciones para mostrar
void muestraUnLibro(stLibro a)
{

    printf("\n------------------------------\n");
    printf("Nombre:...................%s\n",a.titulo);
    printf("Editorial:................%s\n",a.editorial);
    printf("Autor:....................%s\n",a.autor);
    printf("Categoria:................%s\n",a.categoria);
    printf("Valoracion:...............%.2f estrellas\n",a.valoracion);
    printf("ID:.......................%d\n",a.idLibro);

}

void muestraNodoDobleLibro(nodo2Libros * nodo)
{
    muestraUnLibro(nodo->dato);
}
void muestraListaLibros(nodo2Libros * lista)
{

    while(lista)
    {
        if(lista->dato.eliminado==0)
        {
            muestraNodoDobleLibro(lista);
            muestraListaComentarios(lista->lista);
        }
        lista = lista->ste;
    }
}
void muestraListaLibrosAdmin (nodo2Libros * lista)
{
    while(lista)
    {
        muestraNodoDobleLibro(lista);
        printf("Eliminado:................%d\n",lista->dato.eliminado);
        lista=lista->ste;
    }
}
void verLibrosPorCategoria (nodo2Libros * lista, char categoria[])
{
    nodo2Libros * actual= lista;
    int flag=0;
    if(lista)
    {
        while (actual)
        {
            if(strcmpi(actual->dato.categoria,categoria)==0)
            {
                muestraNodoDobleLibro(actual);
                flag=1;
            }
            actual=actual->ste;
        }
    }
    if(flag==0)
    {
        printf("\nNo existen libros de esa categoria\n");
    }
}
void verLibrosPorAutor (nodo2Libros * lista, char autor[])
{
    nodo2Libros * actual= lista;
    int flag=0;
    if(lista)
    {
        while (actual)
        {
            if(strcmpi(actual->dato.autor,autor)==0)
            {
                muestraNodoDobleLibro(actual);
                flag=1;
            }
            actual=actual->ste;
        }
    }
    if(flag==0)
    {
        printf("\nNo encontramos libros de ese autor\n");
    }
}
void verLibrosPorTitulo (nodo2Libros * lista, char titulo[])
{
    nodo2Libros * actual= lista;
    int flag=0;
    if(lista)
    {
        while (actual)
        {
            if(strcmpi(actual->dato.titulo,titulo)==0)
            {
                muestraNodoDobleLibro(actual);
                flag=1;
            }
            actual=actual->ste;
        }
    }
    if(flag==0)
    {
        printf("\nNo encontramos libros con ese titulo\n");
    }
}
///Menu

///Funcion dar de baja libro
void darDeBajaLogica (nodo2Libros* lista)
{
    int id=0;
    printf("Ingrese id del libro a ocultar: \n");
    fflush(stdin);
    scanf("%d",&id);
    int flag=0;
    while(lista!=NULL && flag==0)
    {
        if(lista->dato.idLibro==id)
        {
            lista->dato.eliminado=1;
            flag=1;
        }
        lista=lista->ste;
    }
    if(flag==0)
    {
        printf("\nNo se encontro el libro\n");
    }
}
