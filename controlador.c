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
        }while(esValido==false);
        printf("Password: \n");
        fflush(stdin);
        int i=-1;
        do
        {
            i++;
            fflush(stdin);
            password[i]=getch();
            if(password[i]==13)
            {
                password[i]='\0';
            }
            else
            {
                printf("*");
            }

        }
        while(password[i]!='\0');
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
            //adminMenu();// crear un menu para el administrador
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
void menuPrincipal(char archivoUser[], nodoListaUsuarios * listaUser)
{
    int opcion;


    do
    {
        system("pause");
        system("cls");
        mostrarMenuInicial();
        printf("\nSeleccione una opcion: ");
        fflush(stdin);
        scanf("%d",&opcion);

        switch(opcion)
        {
        case 1:
            system("cls");
            login(listaUser);
            break;

        case 2:
            printf("\n--- Registrarse en el sistema ---\n");
            /// Logica de registro de usuario
            listaUser= registrarse(listaUser);
            listaToArchivo(archivoUser,listaUser);
            break;

        case 0:
            system("cls");
            printf("\n--- Saliendo del sistema ---\n");
            break;

        default:
            printf("\nOpcion no valida. Por favor, intenta nuevamente.\n");
            break;
        }
    }
    while(opcion != 0);
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

void mostrarMenuInicial()///menu inicial
{
    setColor(1);
    escribirConRetraso("\n====================================", 5);
    escribirConRetraso("\n    Sistema de Gestion de Libros", 5);
    escribirConRetraso("\n====================================", 5);
    escribirConRetraso("\n   1. Ingresar", 5);
    escribirConRetraso("\n   2. Registrarse", 5);
    escribirConRetraso("\n   0. Salir", 5);
    escribirConRetraso("\n====================================\n", 5);
    setColor(7);
}
void mostrarMenuUser()///menu inicial
{
    setColor(1);
    escribirConRetraso("\n====================================", 5);
    escribirConRetraso("\n    Sistema de Gestion de Libros", 5);
    escribirConRetraso("\n====================================", 5);
    escribirConRetraso("\n   1. Datos personales", 5);
    escribirConRetraso("\n   2. Modificar datos", 5);
    escribirConRetraso("\n   3. Darme de baja", 5);
    escribirConRetraso("\n   4. Ver libros favoritos", 5);
    escribirConRetraso("\n   0. Salir", 5);
    escribirConRetraso("\n====================================\n", 5);
    setColor(7);
}
void menuUser(nodoListaUsuarios * user)
{
    int opcion;
    do
    {
        system("pause");
        system("cls");
        mostrarMenuUser();
        printf("\nSeleccione una opcion: ");
        fflush(stdin);
        scanf("%d",&opcion);

        switch(opcion)
        {
        case 1:
            system("cls");
            muestraNodoUser(user);
            break;

        case 2:
            ///funcion que modifique datos
            break;

        case 3:
            /// funcion que modifique estado del user a dado de baja

        case 4:
            /// funcion ver libros favoritos


        case 0:
            system("cls");
            printf("\n--- Saliendo del sistema ---\n");
            break;

        default:
            printf("\nOpcion no valida. Por favor, intenta nuevamente.\n");
            break;
        }
    }
    while(opcion != 0);
}
