#include "user.h"
#include <ctype.h>

nodoListaUsuarios * inicLista()
{
    return NULL;
}

nodoListaUsuarios * crearNodo(stUsuario usuario)
{
    nodoListaUsuarios * nuevo = (nodoListaUsuarios * )malloc(sizeof(nodoListaUsuarios));
    nuevo->usuario = usuario;
    nuevo->sig = NULL;
    return nuevo;
}
nodoListaUsuarios * agregarPrincipio(nodoListaUsuarios * lista, nodoListaUsuarios * nuevoNodo)
{
    nuevoNodo->sig = lista;
    return nuevoNodo;
}
void muestraUnUsuario(stUsuario u)
{

    printf("\n-----------------------\n");
    printf("Nombre: ..............%s\n",u.username);
    printf("Direccion: ..............%s %s %s\n",u.domicilio.calle, "  ", u.domicilio.altura);
    printf("DNI: ..............%s\n",u.dni);
    printf("Email: ................%s\n",u.email);
    printf("Id: ................%i\n",u.idUsuario);
    printf("\n-----------------------\n");
}

void muestraNodoUser(nodoListaUsuarios * nodo)
{
    muestraUnUsuario(nodo->usuario);

}
void muestraLista(nodoListaUsuarios * lista)
{
    while(lista)
    {
        muestraNodoUser(lista);
        lista = lista->sig;
    }

}
nodoListaUsuarios* buscarUltimo(nodoListaUsuarios* lista)
{
    nodoListaUsuarios * seg = lista;
    while(seg->sig != NULL)
    {
        seg = seg->sig;
    }
    return seg;
}

nodoListaUsuarios* agregarAlFinal(nodoListaUsuarios* lista, nodoListaUsuarios* nuevo)
{
    if(!lista)
    {
        lista = nuevo;
    }
    else
    {
        nodoListaUsuarios* ultimo = buscarUltimo(lista);
        ultimo->sig = nuevo;
    }

    return lista;
}
nodoListaUsuarios * agregarEnOrdenId(nodoListaUsuarios * lista, nodoListaUsuarios * nuevo)
{

    if(!lista)
    {
        lista = nuevo;
    }
    else
    {
        nodoListaUsuarios * aux = lista; // ante
        if(atoi(aux->usuario.idUsuario) >  atoi(nuevo->usuario.idUsuario))
                lista = agregarPrincipio(aux,nuevo);
                else
        {
            nodoListaUsuarios * seg = lista;
            while(seg && atoi(aux->usuario.idUsuario) < atoi(nuevo->usuario.idUsuario))
                {
                    aux = seg;
                    seg = seg->sig;
                }
                aux->sig = nuevo;
                nuevo->sig = seg;
            }
    }

    return lista;


}


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
        if(verificacionPasswordCondiciones(userAux)==1)
        {
            //agregar verificacion de password con mayusculas La contraseña debe contener por lo menos 1 mayúscula y 1 minúscula.
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
     //char password[]=user->usuario.password;
    if(user)
    {
        while(*password)
        {
            if(isupper(user->usuario.password))
            {
                tieneMayuscula=1;
            }
            else if(islower(user->usuario.password))
            {
                tieneMinuscula=1;
            }
            if(tieneMayuscula=1 && tieneMinuscula=1)
            {
                flag=1;
            }
            password++;
        }
    }
    return flag;
}
