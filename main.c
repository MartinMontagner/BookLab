#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <strings.h>
#include <time.h>

#include "user.h"
#include "libros.h"
#define AR_ARCHIVO "libros.dat"

void cargarLibrosArchivoRandom(char nombreArchivo[]);
nodoListaUsuarios * archivoToLista(char nombreArchivo[], nodoListaUsuarios * lista);
nodo2Libros * archivoToLista2(char nombreArchivo[], nodo2Libros * listaDoble);

int main()
{
    srand(time(NULL));
    stLibro libro1;
    stUsuario user;
    stDomicilio domicilio;
    nodoListaUsuarios* listauser=inicLista();
    nodo2Libros* lista=inicListaDoble();
    lista = archivoToLista2(AR_ARCHIVO,lista);
    lista=cargarLibroEnLista(lista);
    muestraListaLibros(lista);
//    listauser=crearUser(listauser);
//    printf("\nACA NO ES\n");
//    muestraLista(listauser);

    printf("Hello world!\n");
    system("pause");
    return 0;
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




/*nodolistausuarios *  archivotolista(char nombrearchivo[], nodolistausuarios * lista){

    file * buffer = fopen(nombrearchivo, "rb");
    stusuario aux;


    if(buffer){
        while(fread(&aux, sizeof(stusuario), 1, buffer) > 0){
            lista = agregarenordenid(lista,crearnodousuario(aux));
        }
        fclose(buffer);
    }

    return lista;

}*/
