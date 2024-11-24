#include "controlador.h"

void login (nodoArbolUsuario * arbol)
{
    char email[100];
    char password[20];
    int ret,control=0;
    bool esValido=false;
    do
    {
        puts("\n\t\t------------------------------Ingrese sus datos para iniciar----------------------------------\n");
        do
        {
            printf("Email: \n");
            fflush(stdin);
            gets(email);
            esValido=validarEmail(email);
        }
        while(esValido==false);
        printf("Password: \n");
        leerPassword(password,sizeof(password));
        ret=verificar(email,password,arbol);
        if(ret==0)
        {
            system("pause");
            control=27;
        }
    }
    while (ret!=1 && control!=27);
    if(ret==1)
    {
        nodoArbolUsuario * aux=buscarUsuario(email,arbol);
        if(aux->usuario.esAdmin==1)
        {
            menuAdmin(arbol);
        }
        else
        {
            if(aux->usuario.eliminado==0)
            {
                aux=menuUser(aux,arbol);
            }
            else
            {
                printf("\n\n\tCuenta inactiva, para activarla comuniquese con el servicio al cliente.\n");
                system("pause");
            }

        }
    }arbolToArchivo("usuarios.dat",arbol);
}
nodoArbolUsuario * registrarse(nodoArbolUsuario * arbol)
{
    nodoArbolUsuario * user=crearNodoUser(arbol);
    arbol=insertarNodoArbol(arbol,user);
    return arbol;
}
void setColor(int color)
{
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void escribirConRetraso(const char *texto, int delay)
{
    while (*texto)
    {
        putchar(*texto++);
        fflush(stdout);
        usleep(delay * 1000);
    }
}
void mostrarMenuUser()
{
    setColor(1);
    escribirConRetraso("\n====================================", 5);
    escribirConRetraso("\n    Sistema de Gestion de Libros", 5);
    escribirConRetraso("\n====================================", 5);
    escribirConRetraso("\n   1. Datos personales", 5);
    escribirConRetraso("\n   2. Modificar datos", 5);
    escribirConRetraso("\n   3. Darme de baja", 5);
    escribirConRetraso("\n   4. Consultar libros", 5);
    escribirConRetraso("\n   0. Salir", 5);
    escribirConRetraso("\n====================================\n", 5);
    setColor(7);
}
nodoArbolUsuario * menuUser(nodoArbolUsuario * user,nodoArbolUsuario * arbol)
{
    int opcion;
    do
    {
        system("cls");
        mostrarMenuUser();
        printf("\nSeleccione una opcion: ");
        fflush(stdin);
        scanf("%d",&opcion);
        system("cls");
        switch(opcion)
        {
        case 1:
            muestraNodoUser(user);
            system("pause");
            break;

        case 2:
            user=modificarDatos(user,arbol);
            break;

        case 3:
            user=darDeBajaUser(user);
            break;

        case 4:
            menuLibros(user);
            break;

        case 0:
            printf("\n--- Volviendo al menu ---\n");
            break;

        default:
            printf("\nOpcion no valida. Por favor, intenta nuevamente.\n");
            break;
        }
    }
    while(opcion != 0);
    return user;
}
void mostrarMenuLibros()
{
    setColor(1);
    escribirConRetraso("\n====================================", 5);
    escribirConRetraso("\n    Sistema de Gestion de Libros", 5);
    escribirConRetraso("\n====================================", 5);
    escribirConRetraso("\n   1. Ver todos los libros", 5);
    escribirConRetraso("\n   2. Buscar por categoria", 5);
    escribirConRetraso("\n   3. Buscar por autor", 5);
    escribirConRetraso("\n   4. Buscar por titulo", 5);
    escribirConRetraso("\n   5. Agregar un libro a favoritos", 5);
    escribirConRetraso("\n   6. Agregar un libro al sistema", 5);
    escribirConRetraso("\n   7. Ver libros favoritos", 5);
    escribirConRetraso("\n   8. Ver comentarios", 5);
    escribirConRetraso("\n   0. Salir", 5);
    escribirConRetraso("\n====================================\n", 5);
    setColor(7);
}
void menuLibros( nodoArbolUsuario * user)
{
    nodo2Libros * libros=inicListaDoble();
    libros=archivoToLista2("libros.dat",libros);
    int opcion;
    do
    {
        system("pause");
        system("cls");
        mostrarMenuLibros();
        printf("\nSeleccione una opcion: ");
        fflush(stdin);
        scanf("%d",&opcion);

        switch(opcion)
        {
        case 1:
            system("cls");
            muestraListaLibros(libros);
            break;
        case 2:
            ///buscar por categoria
            buscaLibrosPorCategoria(libros);
            break;

        case 3:
            /// buscar por autor
            buscaLibrosPorAutor(libros);
            break;

        case 4:
            /// buscar por titulo
            buscaLibrosPorTitulo(libros);
            break;
        case 5:
            /// agregar un libro a favoritos
            opcionAgregarLibroAFavoritos(user,libros);
            break;
        case 6:
            /// agregar un libro
            libros=cargarLibroEnLista(libros);
            agregarLibrosAlArchivo(libros,"libros.dat");
            break;
        case 7:
            /// ver favoritos
            opcionQuitarLibroDeFavoritos(user,libros);
            break;
        case 8:
            /// ver comentarios
            menuComentario(user,libros);
            break;
        case 0:
            system("cls");

        default:
            printf("\nOpcion no valida. Por favor, intenta nuevamente.\n");
            break;
        }
    }
    while(opcion != 0);
}
void mostrarMenuAdmin()
{
    setColor(2);
    escribirConRetraso("\n====================================", 5);
    escribirConRetraso("\n    Sistema de Gestion de Libros", 5);
    escribirConRetraso("\n====================================", 5);
    escribirConRetraso("\n   1-Dar de baja un libro", 5);
    escribirConRetraso("\n   2-Agregar un libro", 5);
    escribirConRetraso("\n   3-Ver libros", 5);
    escribirConRetraso("\n   4-Ver usuarios", 5);
    escribirConRetraso("\n   5-Dar de baja usuario", 5);
    escribirConRetraso("\n   6-Dar de alta usuario", 5);
    escribirConRetraso("\n   0-Salir", 5);
    escribirConRetraso("\n====================================\n", 5);
    setColor(7);
}
void menuAdmin(nodoArbolUsuario * arbol)
{
    nodo2Libros * libros=inicListaDoble();
    libros=archivoToLista2("libros.dat",libros);
    int opcion;
    do
    {
        system("cls");
        mostrarMenuAdmin();
        printf("\nSeleccione una opcion: ");
        scanf("%d",&opcion);

        switch(opcion)
        {
        case 1:
            darDeBajaLogica(libros);
            system("pause");
            break;
        case 2:
            libros=cargarLibroEnLista(libros);
            agregarLibrosAlArchivo(libros,"libros.dat");
            system("pause");
            break;
        case 3:
            muestraListaLibrosAdmin(libros);
            system("pause");
            break;
        case 4:
            muestraArbolAdmin(arbol);
            system("pause");
            break;
        case 5:
            arbol=darDeBajaUserAdmin(arbol);
            system("pause");
            break;
        case 6:
            arbol=darDeAltaUserAdmin(arbol);
            system("pause");
            break;
        case 0:
            system("cls");
            printf("\n--- Volviendo al menu ---\n");
            break;
        default:
            printf("\nOpcion no valida. Por favor, intenta nuevamente.\n");
            break;
        }
    }
    while(opcion != 0);
    arbolToArchivo("usuarios.dat",arbol);
}

void menuComentario( nodoArbolUsuario * user, nodo2Libros * lista)
{
    nodoComentario * listaComentarios=inicListaComentario();
    listaComentarios= archivoToListaComentario("comentarios.dat",listaComentarios);
    int opcion;
    int idComentario;
    do
    {

        system("cls");
        mostrarMenuComentario();
        printf("\nSeleccione una opcion: ");
        fflush(stdin);
        scanf("%d",&opcion);

        switch(opcion)
        {
        case 1:
            system("cls");
            //Ver mis comentarios;
            mostrarComentariosUsuario(lista,user->usuario.idUsuario);
            break;
        case 2:
            //Agregar Comentario

            lista= ingresarLibros(lista,user->usuario.idUsuario);
            agregarComentariosAlArchivo(listaComentarios,"comentarios.dat");
            break;

        case 3:
            //Editar o eliminar comentario
            printf("Ingrese el id del comentario que desea cambiar: \n");
            fflush(stdin);
            scanf("%d",&idComentario);
            while (getchar() != '\n');
            modificarComentario(listaComentarios, idComentario);
            break;
        case 0:
            system("cls");
            break;
        default:
            printf("\nOpcion no valida. Por favor, intenta nuevamente.\n");
            break;
        }
    }
    while(opcion != 0);

}

void mostrarMenuComentario()
{
    setColor(1);
    escribirConRetraso("\n====================================", 5);
    escribirConRetraso("\n    Sistema de Gestion de Libros", 5);
    escribirConRetraso("\n====================================", 5);
    escribirConRetraso("\n   1. Ver mis comentarios", 5);
    escribirConRetraso("\n   2. Agregar comentarios", 5);
    escribirConRetraso("\n   3. Editar o eliminar comentarios", 5);
    escribirConRetraso("\n   0. Salir", 5);
    escribirConRetraso("\n====================================\n", 5);
    setColor(7);
}
