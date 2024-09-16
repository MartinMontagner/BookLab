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
int verificacionPasswordCondiciones(nodoListaUsuarios * user)  // Funci�n para cuando se registran personas
{
    int tieneMayuscula = 0;
    int tieneMinuscula = 0;
    int flag = 0;

    // Verificamos que el usuario no sea NULL y que la contrase�a no sea NULL
    if(user && user->usuario.password)
    {
        char *password = user->usuario.password;  // Apuntamos directamente a la contrase�a del usuario

        while (*password)  // Mientras no lleguemos al final de la cadena
        {
            if (isupper((unsigned char)*password))  // Verifica si el car�cter actual es may�scula
            {
                tieneMayuscula = 1;
            }
            else if (islower((unsigned char)*password))  // Verifica si el car�cter actual es min�scula
            {
                tieneMinuscula = 1;
            }

            // Si ya se encontr� al menos una may�scula y una min�scula
            if (tieneMayuscula && tieneMinuscula)
            {
                flag = 1;
                break;  // Salimos del bucle porque ya encontramos lo que necesitamos
            }

            password++;  // Avanzamos al siguiente car�cter
        }
    }

    return flag;
}

nodoListaUsuarios * crearUser(nodoListaUsuarios * lista)
{
    nodoListaUsuarios * aux;
    aux=inicLista();
    stUsuario userAux=cargaDatosUser(lista);
    aux=crearNodo(userAux);
    return aux;
}
stUsuario cargaDatosUser(nodoListaUsuarios * lista)
{
    stUsuario user;

    printf("Ingrese su email: \n");
    fflush(stdin);
    gets(user.email);

    printf("Ingrese su password: \n");
    fflush(stdin);
    gets(user.password);

    printf("Ingrese su nombre: \n");
    fflush(stdin);
    gets(user.username);

    printf("Ingrese su DNI: \n");
    fflush(stdin);
    gets(user.dni);

    printf("Ingrese su fecha de nacimiento: \n");
    fflush(stdin);
    gets(user.fechaNacimiento);

    printf("Ingrese su genero: \n");
    fflush(stdin);
    gets(user.genero);

    user.domicilio=cargaDomicilio(user);

    user.librosFavoritos[0]=0;
    user.eliminado=0;
    user.esAdmin=0;
    nodoListaUsuarios * ultimo = buscarUltimo(lista);
    if (ultimo != NULL) {
        user.idUsuario = ultimo->usuario.idUsuario + 1;
    } else {
        user.idUsuario = 1;  // Primer usuario en la lista
    }

    return user;

}
stDomicilio cargaDomicilio(stUsuario user)
{
    printf("Ingrese calle de su domicilio: \n");
    fflush(stdin);
    gets(user.domicilio.calle);

    printf("Ingrese altura de su domicilio: \n");
    fflush(stdin);
    gets(user.domicilio.altura);

    printf("Ingrese ciudad donde vive: \n");
    fflush(stdin);
    gets(user.domicilio.ciudad);

    printf("Ingrese localidad: \n");
    fflush(stdin);
    gets(user.domicilio.localidad);


    printf("Ingrese pais de residencia: \n");
    fflush(stdin);
    gets(user.domicilio.pais);

    printf("Ingrese codigo postal: \n");
    fflush(stdin);
    gets(user.domicilio.cp);

    return user.domicilio;
}
