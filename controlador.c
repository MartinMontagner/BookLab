#include "controlador.h"
void login (nodoListaUsuarios * lista)
{
    char email[100];
    char password[20];
    int ret,control=0;

    do
    {
        puts("\n\t\t------------------------------Ingrese sus datos para iniciar----------------------------------\n");
        printf("Email: \n");
        fflush(stdin);
        gets(email);
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
        ret=verificar(userIngresado,claveIngresado,lista);//crear funcion verificar
        if(ret==0)
        {
            system("pause");
            control=27;
        }
    }
    while (ret!=1 && control!=27);
    if(ret==1)
    {
        nodoListaUsuarios * aux=buscarUsuario(userIngresado,lista);// modificar linea y crear funcion necesaria para la busqueda
        if(aux->usuario.esAdmin==1)
        {
            adminMenu();// crear un menu para el administrador
        }
        else
        {
            if(verificarEstado(idUsuario,lista)==1)//crear y modificar funcion
            {
                clienteMenu();// crear un menu para el cliente
            }
            else
            {
                printf("\n\n\tCuenta inactiva, para activarla comuniquese con el servicio al cliente.\n");
                system("pause");
            }

        }
    }
}
void registrarse(nodoListaUsuarios * lista)
{
    nodoListaUsuarios * user;
//    user=crearUser();
    if(!lista)
    {
        user=lista;
    }else
    {
        lista=agregarEnOrdenId(lista,user);
    }
}

