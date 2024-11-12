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
    while(lista->comentario.idLibro==idLibro)
    {
        valoraciones+=(float)lista->comentario.puntaje;
        lista=lista->ste;
    }
    return valoraciones;
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

