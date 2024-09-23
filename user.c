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
    printf("Direccion: ..............%s %s %d\n",u.domicilio.calle, "  ", u.domicilio.altura);
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
    nodoListaUsuarios* seg = lista;
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

    if(lista==NULL)
    {
        lista = nuevo;
    }
    else
    {
        nodoListaUsuarios * aux = lista; // ante
        if((aux->usuario.idUsuario) >  (nuevo->usuario.idUsuario))
        {
            lista = agregarPrincipio(aux,nuevo);
        }
        else
        {
            nodoListaUsuarios * ante=NULL;
            nodoListaUsuarios * seg = lista;
            while(seg && (seg->usuario.idUsuario) < (nuevo->usuario.idUsuario))
            {
                ante = seg;
                seg = seg->sig;
            }
            ante->sig = nuevo;
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
    nodoListaUsuarios * aux=NULL;
    int flag=0;
    if(lista && strcmp(lista->usuario.email,userIngresado)==0)
    {
        aux=lista;
    }
    else if(lista)
    {
        nodoListaUsuarios * seg=lista;
        while(seg && flag==0)
        {
            if(strcmp(seg->usuario.email,userIngresado)==0)
            {
                aux=seg;
            }
            else
            {
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
int verificacionPasswordCondiciones(char password[])  // Función para cuando se registran personas
{
    int tieneMayuscula = 0;
    int tieneMinuscula = 0;
    int flag = 0;

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


    return flag;
}

nodoListaUsuarios * crearNodoUser(nodoListaUsuarios * lista)
{
    nodoListaUsuarios * aux;
    aux=inicLista();
    stUsuario userAux=cargaDatosUser();
    userAux=sumarId(userAux,lista);
    aux=crearNodo(userAux);
    return aux;
}
stUsuario cargaDatosUser()
{
    stUsuario user;
    bool esValido=false;
//funcion para verificar escritura email
    do
    {
        printf("Ingrese su email: \n");
        fflush(stdin);
        gets(user.email);
        esValido=validarEmail(user.email);
    }while(esValido==false);
    do
    {
        printf("Ingrese su password: \n");
        fflush(stdin);
        int i=-1;
        do
        {
            i++;
            fflush(stdin);
            user.password[i]=getch();
            if(user.password[i]==13)
            {
                user.password[i]='\0';
            }
            else
            {
                printf("*");
            }

        }
        while(user.password[i]!='\0');
    }
    while(verificacionPasswordCondiciones(user.password)==0 );
    printf("\n Ingrese su nombre: \n");
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
    scanf("%c",&user.genero);
    user.domicilio=cargaDomicilio();

    user.librosFavoritos[0]=0;
    user.eliminado=0;
    user.esAdmin=0;


    return user;

}
stDomicilio cargaDomicilio()
{

    stDomicilio domicilio;
    printf("Ingrese calle de su domicilio: \n");
    fflush(stdin);
    gets(domicilio.calle);

    printf("Ingrese altura de su domicilio: \n");
    fflush(stdin);
    scanf("%d",&domicilio.altura);

    printf("Ingrese ciudad donde vive: \n");
    fflush(stdin);
    gets(domicilio.ciudad);

    printf("Ingrese localidad: \n");
    fflush(stdin);
    gets(domicilio.localidad);


    printf("Ingrese pais de residencia: \n");
    fflush(stdin);
    gets(domicilio.pais);

    printf("Ingrese codigo postal: \n");
    fflush(stdin);
    scanf("%d",&domicilio.cp);

    return domicilio;
}
stUsuario sumarId(stUsuario user, nodoListaUsuarios * lista)
{
    nodoListaUsuarios * ultimo = lista;
    if(lista)
    {
        while(ultimo->sig!=NULL)
        {
            ultimo=ultimo->sig;
        }
        user.idUsuario=ultimo->usuario.idUsuario+1;
    }
    else
    {
        user.idUsuario=1;
    }
    return user;
}
bool validarEmail(char email[])
{
    int arrobaPos=-1, puntoPos=-1, longitud=strlen(email), i=0;
    bool esValido=true;

    /// Recorrer el string para buscar '@' y '.'
    for(i=0; i<longitud; i++)
    {
        if(email[i]=='@')
        {
            if(arrobaPos==-1)
            {
                arrobaPos=i;  /// Guardar la posición del primer '@'
            }
            else
            {
                esValido=false;  /// Si hay más de un '@', es inválido
            }
        }

        if(email[i]=='.')
        {
            puntoPos=i;  /// Guardar la posición del último '.'
        }
    }

    /// Verificar que no haya múltiples '@' y las posiciones de '@' y '.'
    if(arrobaPos==-1 || puntoPos==-1 || puntoPos<=arrobaPos + 1 || puntoPos>=longitud - 1)
    {
        esValido=false;
    }
    return esValido;
}



