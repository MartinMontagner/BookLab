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
        else{
            printf("Clave incorrecta!\n");
        }
    }else{
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
        if(verificacionPasswordCondiciones(userAux)==1)
        {//agregar verificacion de password con mayusculas La contraseña debe contener por lo menos 1 mayúscula y 1 minúscula.
        flag=1;
        }
    }
    return flag;
}
int verificacionPasswordCondiciones(nodoListaUsuarios * user)
{
    int tieneMayuscula=0;
    int tieneMinuscula=0;
    int flag=0;
    char password[]=user->usuario.password;
    if(user)
    {
        while(*password)
        {
            if(isupper(user->usuario.password))
            {
                tieneMayuscula=1;
            }else
            if(islower(user->usuario.password))
            {
                tieneMinuscula=1;
            }
            if(tieneMayuscula=1 && tieneMinuscula=1){
                flag=1;
            }
            password++;
        }
    }return flag;
}
