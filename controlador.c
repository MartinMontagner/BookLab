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
