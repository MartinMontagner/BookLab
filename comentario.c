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

int buscarUltimoIdComentario(nodoComentario * lista) {
    int id = 1;
    nodoComentario * actual = lista;
    while (actual != NULL) {
        if (actual->comentario.idComentario >= id) {
            id = actual->comentario.idComentario + 1;
        }
        actual = actual->ste;
    }
    return id;
}

int contarComentarios(nodoComentario * lista) {
    int count = 0;
    nodoComentario * aux = lista;
    while (aux) {
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
void cambioTitulo(nodoComentario * lista, int idComentario)
{
    int flag=0;
    while(lista && flag==0)
    {
        if(lista->comentario.idComentario==idComentario)
        {
            printf("\nIngrese el titulo: \n");
            fflush(stdin);
            gets(lista->comentario.tituloComentario);
            flag=1;
        }
        lista=lista->ste;
    }
}

void cambioDescripcion(nodoComentario * lista, int idComentario)
{
    int flag=0;
    while(lista && flag==0)
    {
        if(lista->comentario.idComentario==idComentario)
        {
            printf("\nIngrese la descripcion: \n");
            fflush(stdin);
            gets(lista->comentario.descripcion);
            flag=1;
        }
        lista=lista->ste;
    }
}

void cambioPuntaje (nodoComentario * lista, int idComentario)
{
    int flag=0;
    while(lista && flag==0)
    {
        if(lista->comentario.idComentario == idComentario)
        {
            printf("Ingrese el nuevo puntaje: \n");
            fflush(stdin);
            scanf("%d",lista->comentario.puntaje);
            flag=1;
        }
        lista=lista->ste;
    }
}
void eliminarComentario(nodoComentario * lista,int idComentario)
{
    int flag=0;
    while(lista && flag==0)
    {
        if(lista->comentario.idComentario==idComentario)
        {
            lista->comentario.eliminado=1;
            flag=1;
        }
        lista->ste;
    }
}

///Para menu
nodoComentario * modificarComentario(nodoComentario * lista, int idComentario)
{
    int opcion;
    char resp="";
    do
    {
        system("cls");
        system("pause");
        opcionesModificarComentario();
        printf("\nIngrese que desea cambiar\n");
        fflush(stdin);
        scanf("%d",&opcion);
        switch(opcion)
        {
        case 1:
            cambioTitulo(lista, idComentario);
            break;
        case 2:
            cambioDescripcion(lista, idComentario);
            break;
        case 3:
            cambioPuntaje(lista, idComentario);
            break;
        case 4:
            printf("Estas seguro que deseas eliminar el comentario? s / n\n");
            fflush(stdin);
            scanf("%c",&resp);
            if(resp=='s')
            {
                eliminarComentario(lista,idComentario);
            }
            break;
        case 0:
            system("cls");
            printf("\n--- Volviendo al menu ---\n");
            break;
        }
    }
    while(opcion!=0);
    agregarComentariosAlArchivo(lista,"comentarios.dat");
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
nodoComentario * agregarFinal(nodoComentario * lista, nodoComentario * nuevoNodo) {
    if (lista == NULL) {
        lista = nuevoNodo;
    } else {
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
    printf("Fecha:...................%s\n",a.fechaComentario);
    printf("Titulo:................%s\n",a.tituloComentario);
    printf("Descripcion:....................%s\n",a.descripcion);
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
void agregarComentariosAlArchivo(nodoComentario* lista,char nombreArchivo [])
{
    FILE *archivo = fopen(nombreArchivo, "wb");

    nodoComentario* actual = lista;
    if (archivo)
    {
        while (actual)
        {
            fwrite(&actual->comentario, sizeof(stComentario), 1, archivo);
            actual = actual->ste;
        }
    }

    fclose(archivo);
    printf("Error al abrir el archivo.\n");
}
