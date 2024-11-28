#include "comentario.h"


///FUNCIONES DE CARGA
stComentario cargaUnComentario()
{

    stComentario aux;;

    printf("Ingrese la fecha de hoy: \n");
    fflush(stdin);
    gets(aux.fechaComentario);

    printf("Ingrese el titulo del comentario: \n");
    fflush(stdin);
    gets(aux.tituloComentario);

    printf("Ingrese la descripcion: \n");
    fflush(stdin);
    gets(aux.descripcion);

    printf("Ingrese cuantas estrellas le da (0 a 5): \n");
    fflush(stdin);
    scanf("%d",&aux.puntaje);


    aux.eliminado=0;

    return aux;
}

nodoComentario * inicListaComentario()
{
    return NULL;
}

nodoComentario * crearNodoComentario(stComentario coment)
{

    nodoComentario * nuevo = (nodoComentario *)malloc(sizeof(nodoComentario));
    nuevo->comentario = coment;
    nuevo->ste = NULL;
    nuevo->ante = NULL;
    return nuevo;
}



nodoComentario * buscarUltimoComentario (nodoComentario * lista)
{
    nodoComentario * seg = lista;
    while(seg->ste != NULL)
    {
        seg = seg->ste;
    }
    return seg;
}

int buscarUltimoIdComentario(nodoComentario * lista)
{
    int id = 1;
    nodoComentario * actual = lista;
    while (actual != NULL)
    {
        if (actual->comentario.idComentario >= id)
        {
            id = actual->comentario.idComentario + 1;
        }
        actual = actual->ste;
    }
    return id;
}

int contarComentarios(nodoComentario * lista)
{
    int count = 0;
    nodoComentario * aux = lista;
    while (aux)
    {
        count++;
        aux = aux->ste;
    }
    return count;
}


nodoComentario * cargarComentarioEnLista(nodoComentario * lista, int idLibro, int idUsuario)
{
    stComentario comentario;
    comentario=cargaUnComentario();
    comentario.idComentario=buscarUltimoIdComentario(lista);
    comentario.idLibro=idLibro;
    comentario.idUsuario=idUsuario;
    lista = agregarFinal(lista, crearNodoComentario(comentario));
    return lista;
}

///Contando valoraciones del libro.
float calculoValoraciones (nodoComentario * lista, int idLibro)
{
    float valoraciones=0;
    int contadorComentarios=0;
    float total=0;
    while(lista)
    {
        if(lista->comentario.idLibro==idLibro)
        {
            contadorComentarios++;
            valoraciones+=lista->comentario.puntaje;
        }
        lista=lista->ste;
    }
    if(contadorComentarios!=0)
    {
        total=(float)valoraciones/contadorComentarios;
    }

    return total;
}
///Funciones para cambiar el comentario

void cambioTitulo(nodoComentario * lista)
{
    printf("\nIngrese el titulo: \n");
    fflush(stdin);
    gets(lista->comentario.tituloComentario);
}
void cambioDescripcion(nodoComentario * lista)
{
    printf("\nIngrese la descripcion: \n");
    fflush(stdin);
    gets(lista->comentario.descripcion);
}


void cambioPuntaje (nodoComentario * lista)
{
    printf("Ingrese el nuevo puntaje: \n");
    fflush(stdin);
    scanf(" %d",&lista->comentario.puntaje);
}
void eliminarComentario(nodoComentario * lista)
{
    lista->comentario.eliminado=1;
}

///Para menu


nodoComentario *  archivoToListaComentario(char nombreArchivo[], nodoComentario * listaDoble)
{

    FILE * buffer = fopen(nombreArchivo, "rb");
    stComentario aux;


    if(buffer)
    {
        while(fread(&aux, sizeof(stComentario), 1, buffer) > 0)
        {
            listaDoble = insertarNodoPorIdComentario(listaDoble,crearNodoComentario(aux));
        }
        fclose(buffer);
    }

    return listaDoble;
}

///agregar al final
nodoComentario * agregarFinal(nodoComentario * lista, nodoComentario * nuevoNodo)
{
    if (lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        nodoComentario * ultimo = buscarUltimoComentario(lista);
        ultimo->ste = nuevoNodo;
        nuevoNodo->ante = ultimo;
    }
    return lista;
}

nodoComentario * agregarPrincipioComentario(nodoComentario * lista, nodoComentario * nuevo)
{
    nuevo->ste = lista;
    if(lista)
    {
        lista->ante = nuevo;
    }
    return nuevo;
}

nodoComentario * insertarNodoPorIdComentario (nodoComentario * lista, nodoComentario * nuevoNodo)
{
    if(lista==NULL)
    {
        lista=nuevoNodo;
    }
    else if (nuevoNodo->comentario.idComentario < lista->comentario.idComentario)
    {
        lista=agregarPrincipioComentario(lista,nuevoNodo);
    }
    else
    {
        nodoComentario * anterior=lista;
        nodoComentario * seg=lista->ste;

        while (seg!=NULL && seg->comentario.idComentario < nuevoNodo->comentario.idComentario)
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




///Funciones para mostrar
void muestraUnComentario (stComentario a)
{

    printf("\n------------------------------\n");
    printf("Fecha:.....................%s\n",a.fechaComentario);
    printf("Titulo:....................%s\n",a.tituloComentario);
    printf("Descripcion:...............%s\n",a.descripcion);
    printf("Valoracion:................%d\n",a.puntaje);
    printf("Id:........................%d\n",a.idComentario);
}

void muestraNodoComentario(nodoComentario * nodo)
{
    muestraUnComentario(nodo->comentario);
}
void muestraListaComentarios(nodoComentario * lista)
{
    printf("COMENTARIOS \n");
    while(lista)
    {
        if(lista->comentario.eliminado==0)
        {
            muestraNodoComentario(lista);
        }
        lista = lista->ste;
    }
}
void muestraListaComentariosAdmin (nodoComentario * lista)
{
    while(lista)
    {
        muestraNodoComentario(lista);
        printf("IdLibro:..................%d\n",lista->comentario.idLibro);
        printf("IdUsuario:................%d\n",lista->comentario.idUsuario);
        printf("Eliminado:................%d\n",lista->comentario.eliminado);
        lista=lista->ste;
    }
}

void opcionesModificarComentario()
{
    setColor(1);
    escribirConRetraso("\n====================================", 5);
    escribirConRetraso("\n    Sistema de Gestion de Libros", 5);
    escribirConRetraso("\n====================================", 5);
    escribirConRetraso("\n   1. Titulo", 5);
    escribirConRetraso("\n   2. Descripcion", 5);
    escribirConRetraso("\n   3. Puntaje", 5);
    escribirConRetraso("\n   4. Eliminar", 5);
    escribirConRetraso("\n   0. Salir", 5);
    escribirConRetraso("\n====================================\n", 5);
    setColor(7);
}

nodoComentario * buscarComentarioPorId(nodoComentario * lista, int id)
{
    nodoComentario* actual = lista;
    while (actual != NULL)
    {
        if (actual->comentario.idComentario == id)
        {
            return actual;
        }
        actual = actual->ste;
    }
    return NULL;
}


///Funciones para crear contenido random

void setTituloComentarioRandom(char tituloComentario[])
{
    char arregloTitulos[][100] =
    {
        "Excelente lectura", "Decepcionante", "Una joya literaria", "Lectura fascinante",
        "Una experiencia regular",
        "Demasiado complejo",
        "Una obra sencilla pero efectiva",
        "Impactante y emotivo",
        "Una perdida de tiempo",
        "Lo recomiendo ampliamente",
        "Personajes increibles",
        "Historia predecible",
        "Una maravilla literaria",
        "Nada memorable",
        "Lectura obligatoria",
        "Demasiado largo para mi gusto",
        "Llena de sorpresas",
        "Faltaron emociones",
        "Increiblemente atrapante",
        "Un clasico moderno",
        "No cumplio mis expectativas",
        "Profundo y reflexivo",
        "Ideal para una tarde tranquila",
        "Exceso de detalles innecesarios",
        "Un final inesperado",
        "Trama llena de giros",
        "Lectura para toda la familia",
        "Tedioso pero interesante",
        "Un libro que deja huella",
        "Demasiado simplista",
        "Una narrativa vibrante",
        "Perfecto para los amantes de la accion",
        "Con potencial, pero mediocre",
        "Un viaje extraordinario",
        "Inconsistente en su desarrollo",
        "Magico y atrapante",
        "Un libro que inspira",
        "Un clasico infravalorado",
        "Me dejo con ganas de mas",
        "No logre conectar con la historia",
        "Un relato lleno de pasion",
        "Trama compleja pero gratificante",
        "Aburrido y monotono",
        "Perfecto para reflexionar",
        "Personajes poco convincentes",
    };
    int cantTitulos = sizeof(arregloTitulos) / sizeof(arregloTitulos[0]);
    int indiceAleatorio = rand() % cantTitulos;
    strcpy(tituloComentario, arregloTitulos[indiceAleatorio]);
}
void setDescripcionRandom(char descripcion[])
{
    char arregloDescripciones[][500] =
    {
        "Un libro que captura la esencia de la humanidad.",
        "No logro engancharme, esperaba mas.",
        "Es una lectura pesada pero gratificante.",
        "Muy basico, pero adecuado para principiantes.",
        "La narrativa es excelente y cautivadora.",
        "Demasiado largo y sin sentido.",
        "Los personajes estan muy bien construidos.",
        "La trama es predecible y aburrida.",
        "Me sorprendio gratamente, lo volveria a leer.",
        "Es uno de los mejores libros que he leido.",
        "Un libro que me hizo reflexionar profundamente.",
        "No cumplio con mis expectativas.",
        "La trama es interesante, pero los personajes son planos.",
        "Escrito de manera simple y clara, ideal para principiantes.",
        "Demasiadas paginas para tan poca historia.",
        "Una narrativa envolvente y llena de emociones.",
        "Es una lectura que deja huella en el lector.",
        "La historia es muy predecible y aburrida.",
        "Perfecto para los amantes de la ciencia ficcion.",
        "El libro me atrapo desde la primera pagina.",
        "Falto mas desarrollo en la historia principal.",
        "Es una obra que merece ser leida varias veces.",
        "La calidad de la escritura es simplemente brillante.",
        "Un viaje emocional a traves de sus paginas.",
        "Le falto profundidad a los temas tratados.",
        "Es una historia que no olvidare facilmente.",
        "No recomendaría este libro a nadie.",
        "Un clasico que siempre es un placer leer.",
        "La estructura de la historia es confusa.",
        "Me parecio una obra de arte en todos los sentidos."
    };
    int cantDescripciones = sizeof(arregloDescripciones) / sizeof(arregloDescripciones[0]);
    int indiceAleatorio = rand() % cantDescripciones;
    strcpy(descripcion, arregloDescripciones[indiceAleatorio]);
}
void setFechaComentarioRandom(char fechaComentario[])
{
    sprintf(fechaComentario, "%02d/%02d/%04d",
            1 + rand() % 30,       // Día
            1 + rand() % 12,       // Mes
            2000 + rand() % 24);   // Año (2000-2023)
}


stComentario cargaRandomComentario(int idComentario, int idLibro, int idUsuario)
{

    stComentario comentario;
    comentario.idComentario=idComentario;
    comentario.idLibro=idLibro;
    comentario.idUsuario=idUsuario;
    setTituloComentarioRandom(comentario.tituloComentario);
    setDescripcionRandom(comentario.descripcion);
    comentario.puntaje = rand() % 6;
    setFechaComentarioRandom(comentario.fechaComentario);
    comentario.eliminado = 0;

    return comentario;
}

void generarComentariosRandom(char nombreArchivo[], int cantidad)
{
    FILE *archivo = fopen(nombreArchivo, "wb");
    if (archivo)
    {
        for (int i = 0; i < cantidad; i++)
        {
            int idComentario = i + 1;
            int idLibro = 1 + rand() % 58;
            int idUsuario = 1 + rand() % 20;
            stComentario comentario = cargaRandomComentario(idComentario, idLibro, idUsuario);
            fwrite(&comentario, sizeof(stComentario), 1, archivo);
        }
        fclose(archivo);
        printf("Se generaron %d comentarios aleatorios.\n", cantidad);
    }
    else
    {
        printf("Error al abrir el archivo para guardar los comentarios.\n");
    }
}
