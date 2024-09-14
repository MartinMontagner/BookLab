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
        if((aux->usuario.idUsuario) >  (nuevo->usuario.idUsuario))
                lista = agregarPrincipio(aux,nuevo);
                else
        {
            nodoListaUsuarios * seg = lista;
            while(seg && (aux->usuario.idUsuario) < (nuevo->usuario.idUsuario))
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
    if(lista && strcmp(lista->usuario.email,userIngresado)==0)
    {
        aux=lista;
    }
    else if(lista)
    {
        ante=lista;
        seg=lista->sig;
        while(seg && flag==0)
        {
            if(strcmp(seg->usuario.email,userIngresado)==0)
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
//int verificacionPasswordCondiciones(nodoListaUsuarios * user)//funcion para cuando se registran personas
//{
//    int tieneMayuscula = 0;
//    int tieneMinuscula = 0;
//    int flag = 0;
//    char password[50];
//    strcpy(password,user->usuario.password);
//    if(user)
//    {
//
//        while (*password)  // Mientras no lleguemos al final de la cadena
//        {
//
//            if (isupper((unsigned char)*password))  // Verifica si el carácter actual es mayúscula
//            {
//                tieneMayuscula = 1;
//            }
//            else if (islower((unsigned char)*password))  // Verifica si el carácter actual es minúscula
//            {
//                tieneMinuscula = 1;
//            }
//
//            // Si ya se encontró al menos una mayúscula y una minúscula
//            if (tieneMayuscula && tieneMinuscula)
//            {
//                flag = 1;
//                break;  // Salimos del bucle porque ya encontramos lo que necesitamos
//            }
//
//            password++;  // Avanzamos al siguiente carácter
//        }
//    }
//    return flag;
//}
//
