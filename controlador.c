#include "controlador.h"

void login (nodoListaUsuarios * lista)
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
        ret=verificar(email,password,lista);//crear funcion verificar
        if(ret==0)
        {
            system("pause");
            control=27;
        }
    }
    while (ret!=1 && control!=27);
    if(ret==1)
    {
        nodoListaUsuarios * aux=buscarUsuario(email,lista);
        if(aux->usuario.esAdmin==1)
        {
            menuAdmin(lista);// crear un menu para el administrador
        }
        else
        {
            if(aux->usuario.eliminado==0)//crear y modificar funcion
            {
                menuUser(aux);
            }
            else
            {
                printf("\n\n\tCuenta inactiva, para activarla comuniquese con el servicio al cliente.\n");
                system("pause");
            }

        }
    }

}
nodoListaUsuarios * registrarse(nodoListaUsuarios * lista)
{
    nodoListaUsuarios * user=NULL;
    user=crearNodoUser(lista);
    if(lista==NULL)
    {
        lista=agregarPrincipio(lista,user);
    }
    else
    {
        lista=agregarEnOrdenId(lista,user);
    }
    return lista;
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
void menuUser(nodoListaUsuarios * user)
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
            user=modificarDatos(user);
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
    listaToArchivo("usuarios.dat",user);
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
    escribirConRetraso("\n   0. Salir", 5);
    escribirConRetraso("\n====================================\n", 5);
    setColor(7);
}
void menuLibros( nodoListaUsuarios * user)
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
void menuAdmin(nodoListaUsuarios * listaUser)
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
            muestraListaAdmin(listaUser);
            system("pause");
            break;
        case 5:
            listaUser=darDeBajaUserAdmin(listaUser);
            system("pause");
            break;
        case 6:
            listaUser=darDeAltaUserAdmin(listaUser);
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
}
