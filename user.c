#include "user.h"
#include <ctype.h>

int verificar(char userIngresado[],char claveIngresado[],nodoListaUsuarios * lista)
{
    int flag=0;
    nodoListaUsuarios * userAux;
    userAux=buscarUsuario(userIngresado,lista);
    if(userAux!=NULL)
    {
        if(verificarPassword(claveIngresado,userAux)==1)
        {
            flag=1;
        }
        else
        {
            printf("Clave incorrecta!\n");
        }
    }
    else
    {
        printf("Usuario inexistente\n");

    }
    return flag;
}

nodoListaUsuarios * buscarUsuario(char userIngresado[], nodoListaUsuarios * lista)
{
    nodoListaUsuarios * ante=NULL;
    nodoListaUsuarios * aux=NULL;
    nodoListaUsuarios * seg=lista;
    int flag=0;
    if(lista && strcmp(lista->usuario.username,userIngresado)==0)
    {
        aux=lista;
    }
    else if(lista)
    {
        ante=lista;
        seg=lista->sig;
        while(seg && flag==0)
        {
            if(strcmp(seg->usuario.username,userIngresado)==0)
            {
                aux=seg;
            }
            else
            {
                ante=seg;
                seg=seg->sig;
            }
        }

    }
    return aux;

}
int verificarPassword(char claveIngresado[], nodoListaUsuarios * userAux)
{
    int flag=0;
    if(strcmp(userAux->usuario.password,claveIngresado)==0)
    {
        flag=1;
    }
    return flag;
}
int verificacionPasswordCondiciones(nodoListaUsuario * user)//funcion para cuando se registran personas
{
    int tieneMayuscula = 0;
    int tieneMinuscula = 0;
    int flag = 0;
    char password[50];
    strcpy(password,user->usuario.password);
    if(user)
    {

        while (*password)  // Mientras no lleguemos al final de la cadena
        {

            if (isupper((unsigned char)*password))  // Verifica si el carácter actual es mayúscula
            {
                tieneMayuscula = 1;
            }
            else if (islower((unsigned char)*password))  // Verifica si el carácter actual es minúscula
            {
                tieneMinuscula = 1;
            }

            // Si ya se encontró al menos una mayúscula y una minúscula
            if (tieneMayuscula && tieneMinuscula)
            {
                flag = 1;
                break;  // Salimos del bucle porque ya encontramos lo que necesitamos
            }

            password++;  // Avanzamos al siguiente carácter
        }
    }
    return flag;
}
/*int verificacionPasswordCondiciones(char password[])//nodoListaUsuarios * user)
{
    int tieneMayuscula=0;
    int tieneMinuscula=0;
    int flag=0;
    //char password[]=user->usuario.password;
    //if(user)
    //{
        while(*password)
        {
            printf("ingreso al while");
            if(isupper(password)==0)//user->usuario.password))
            {
                tieneMayuscula=1;
                printf("if que verifica mayuscula");
            }else
            if(islower(password)==0)//user->usuario.password))
            {
                tieneMinuscula=1;
                printf("if que verifica minuscula");
            }
            if(tieneMayuscula==1 && tieneMinuscula==1){
                flag=1;
                printf("if que verifica los dos");
            }
            password++;
        }
    //}
    return flag;
}*/
