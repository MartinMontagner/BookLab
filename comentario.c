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


int buscarUltimoIdComentario (nodoComentario * lista)
{
    nodoComentario * ultimo= buscarUltimoComentario(lista);
    int id=ultimo->comentario.idComentario;
    return id;
}

nodoComentario * cargarComentarioEnLista(nodoComentario * lista, int idLibro, int idUsuario)
{
    stComentario comentario;
    if(lista)
    {

        comentario=cargaUnComentario();
        comentario.idComentario=buscarUltimoIdComentario(lista)+1;
        comentario.idLibro=idLibro;
        comentario.idUsuario=idUsuario;
        lista=insertarNodoPorId(lista,crearNodoComentario(comentario));
    }
    return lista;
}

///Contando valoraciones del libro.
float calculoValoraciones (nodoComentario * lista, int idLibro)
{
    float valoraciones=0;
    int contadorComentarios=0;
    float total=0;
    while(lista->comentario.idLibro==idLibro)
    {
        contadorComentarios++;
        valoraciones+=(float)lista->comentario.puntaje;
        lista=lista->ste;
    }
    total=valoraciones/contadorComentarios;
    return total;
}
///Funciones para cambiar el comentario
void cambioTitulo(char * titulo)
{
    printf("\nIngrese el titulo: \n");
    fflush(stdin);
    gets(titulo);
}

void cambioDescripcion(char * descripcion)
{
    printf("\nIngrese la descripcion: \n");
    fflush(stdin);
    gets(descripcion);
}

void cambioPuntaje (int * puntaje)
{

    printf("Ingrese el nuevo puntaje: \n");
    fflush(stdin);
    scanf("%d",puntaje);
}
void eliminarComentario(nodoComentario * lista)
{
    lista->comentario.eliminado=1;
}

///Para menu
nodoComentario * modificarComentario(nodoComentario * lista)
{
    int opcion;
    char resp;
    do
    {
        system("cls");
        printf("\nIngrese  desea cambiar\n");
        fflush(stdin);
        opcionesModificarComentario();
        scanf("%d",&opcion);
        switch(opcion)
        {
        case 1:
            cambioTitulo(lista->comentario.tituloComentario);
            break;
        case 2:
            cambioDescripcion(lista->comentario.descripcion);
            break;
        case 3:
            cambioPuntaje(lista->comentario.puntaje);
            break;
        case 4:
            printf("Estas seguro que deseas eliminar el comentario? s / n\n");
            fflush(stdin);
            scanf("%c",&resp);
            if(resp=='s')
            {
                eliminarComentario(lista);
            }
            system("cls");
            printf("\n--- Volviendo al menu ---\n");
            break;
        case 0:
            system("cls");
            printf("\n--- Volviendo al menu ---\n");
            break;
        }
    }
    while(opcion!=0);
    return lista;
}



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
    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        nodoComentario * ultimo = buscarUltimoComentario(lista);
        ultimo->ste = nuevoNodo;
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
    printf("Fecha:...................%s\n",a.fechaComentario);
    printf("Titulo:................%s\n",a.tituloComentario);
    printf("Descripcion:....................%s\n",a.descripcion);
    printf("Valoracion:................%s\n",a.puntaje);
}

void muestraNodoComentario(nodoComentario * nodo)
{
    muestraUnComentario(nodo->comentario);
}
void muestraListaComentarios(nodoComentario * lista)
{

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
        printf("Eliminado:................%d\n",lista->comentario.eliminado);
        lista=lista->ste;
    }
}

void opcionesModificarComentario()
{
    printf("\n   1. Titulo\n");
    printf("\n   2. Descripcion\n");
    printf("\n   3. Puntaje\n");
    printf("\n   4. Eliminar\n");
    printf("\n   0. Salir\n");
}



