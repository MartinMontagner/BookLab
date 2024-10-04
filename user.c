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
nodoListaUsuarios * crearNodoUser(nodoListaUsuarios * lista)
{
    nodoListaUsuarios * aux;
    aux=inicLista();
    stUsuario userAux=cargaDatosUser();
    userAux.idUsuario=sumarId(userAux,lista);
    aux=crearNodo(userAux);
    return aux;
}
///Funciones para agregar
nodoListaUsuarios * agregarPrincipio(nodoListaUsuarios * lista, nodoListaUsuarios * nuevoNodo)
{
    nuevoNodo->sig = lista;
    return nuevoNodo;
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

///Funciones de busqueda
nodoListaUsuarios * buscarUsuario(char userIngresado[], nodoListaUsuarios * lista)
{
    nodoListaUsuarios * aux=NULL;
    int flag=0;
    if(lista && strcmp(lista->usuario.email,userIngresado)==0)
    {
        aux=lista;
    }
    else
    {
        nodoListaUsuarios * seg=lista->sig;
        while(seg!=NULL && flag==0)
        {
            if(strcmp(seg->usuario.email,userIngresado)==0)
            {
                aux=seg;
                flag=1;
            }
            else
            {
                seg=seg->sig;
            }
        }

    }
    return aux;

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

///Funciones para Mostrar

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


///Funciones de verificacion

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
            printf("\nClave incorrecta!\n");
        }
    }
    else
    {
        printf("\nUsuario inexistente\n");

    }
    return flag;
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
    if(flag==0)
    {
        printf("\nNo cumple con las condiciones, por favor agregar una mayuscula y una minuscula.\n");
    }


    return flag;
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



///Funciones de Carga
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
    }
    while(esValido==false);
    do
    {
        printf("\nLa password tiene que tener una mayuscula y una minuscula por lo menos\n");
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
int sumarId(stUsuario user, nodoListaUsuarios * lista)
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
    return user.idUsuario;
}


///Funciones para crear contenido random
int randomRangoUsuarios(int min, int max)
{
    return  min +  rand()% (max - min +1);
}
void setMailRandom(char email[])
{

    char arregloMail[][100] = {"juan.perez@hotmail.com", "maria.gomez@gmail.com", "carlos.lopez@gmail.com", "ana.fernandez@hotmail.com", "luis.martinez@gmail.com", "sofia.ramirez@gmail.com", "diego.torres@hotmail.com", "lucia.morales@gmail.com", "ricardo.sanchez@hotmail.com", "valeria.diaz@gmail.com",
                               "mariana.vazquez@hotmail.com", "pablo.rodriguez@gmail.com",
                               "julieta.castro@hotmail.com", "roberto.mendoza@hotmail.com", "veronica.fuentes@gmail.com", "alberto.rivas@hotmail.com",
                               "camila.arias@gmail.com", "sebastian.ortiz@gmail.com", "laura.garcia@gmail.com", "fernando.bustos@hotmail.com"
                              };
    int cantMail=(sizeof(arregloMail) / sizeof(arregloMail[0]));
    int indiceAleatorio = randomRangoUsuarios(0, cantMail - 1);
    strcpy(email, arregloMail[indiceAleatorio]);
}

void setPasswordRandom(char password[])
{
    char arregloPassword[][20] = {"Password123",
                                  "SecurePass1", "MySecret99", "AlphaBeta2024", "TigerEyes21",
                                  "OceanWave55", "SunnyDay77", "BlueSky88", "GreenForest44", "MoonLight22",
                                  "HappyHour12", "FastCar89", "WinterSnow56", "MagicLand78", "BrightStar33", "GoldenSun14",
                                  "CoolBreeze98", "DreamBig2023", "LuckyNumber7", "SilverMoon31"
                                 };
    int cantPassword=(sizeof(arregloPassword) / sizeof(arregloPassword[0]));
    int indiceAleatorio = randomRangoUsuarios(0, cantPassword - 1);
    strcpy(password, arregloPassword[indiceAleatorio]);
}
void setUsernameRandom(char username[])
{
    char arregloUsername[][20] = {"Juan", "Maria", "Carlos", "Sofia", "Luis", "Ana", "Fernando",
                                  "Lucia", "Roberto", "Valeria", "Pablo", "Camila", "Diego", "Julieta", "Martin", "Laura",
                                  "Sebastian", "Veronica", "Ricardo", "Paula"
                                 };
    int cantUsername=(sizeof(arregloUsername) / sizeof(arregloUsername[0]));
    int indiceAleatorio = randomRangoUsuarios(0, cantUsername - 1);
    strcpy(username, arregloUsername[indiceAleatorio]);
}
void setGeneroRandom(char genero[])
{
    char arregloGenero[][10] = {"F", "M"};
    int cantGenero=(sizeof(arregloGenero) / sizeof(arregloGenero[0]));
    int indiceAleatorio = randomRangoUsuarios(0, cantGenero - 1);
    strcpy(genero, arregloGenero[indiceAleatorio]);
}
void setFechaNacimientoRandom(char fechaNacimiento[])
{
    char arregloFechaNacimiento[][20] = {"7 de agosto 1996", "15 de enero 1985", "23 de marzo 1990",
                                         "10 de abril 1978", "5 de noviembre 2000", "30 de junio 1992", "18 de septiembre 1988",
                                         "25 de diciembre 1995", "9 de febrero 1983", "12 de octubre 1975", "3 de julio 2001", "27 de mayo 1997",
                                         "14 de agosto 1993", "21 de junio 1980", "6 de noviembre 1998", "19 de abril 1986", "28 de febrero 1994",
                                         "8 de marzo 1991", "11 de diciembre 1982", "4 de julio 1989"
                                        };
    int cantFechaNacimiento=(sizeof(arregloFechaNacimiento) / sizeof(arregloFechaNacimiento[0]));
    int indiceAleatorio = randomRangoUsuarios(0, cantFechaNacimiento - 1);
    strcpy(fechaNacimiento, arregloFechaNacimiento[indiceAleatorio]);
}
void setDniRandom(char dni[],int usados[], int *restantes)
{
    char arregloDni[][10] = {"30678923", "28765432", "39874567", "32984756", "41928374",
                             "56473829", "61283947", "23829156", "45673820", "50192834",
                             "34718294", "29183746", "64829371", "43482915", "58391024",
                             "69382047", "47283910", "52938471", "61829304", "78912345"
                            };
    int cantDni=(sizeof(arregloDni) / sizeof(arregloDni[0]));
    int indiceAleatorio=0;
    do
    {
        indiceAleatorio = randomRangoUsuarios(0, cantDni - 1);
    }
    while (usados[indiceAleatorio] == 1);

    strcpy(dni, arregloDni[indiceAleatorio]);
    usados[indiceAleatorio] = 1;

    (*restantes)--;
}
void setCalleRandom(char calle[])
{
    char arregloCalle[][20] = {"Avenida Brasil", "Calle Colon", "Calle Libertad", "Avenida 9 de Julio",
                               "Avenida Insurgentes", "Calle O'Higgins", "Avenida Bolivar",
                               "Calle San Martin", "Calle Sucre", "Avenida Los Andes",
                               "Calle Madero", "Avenida Belgrano", "Calle Alvear",
                               "Avenida Reforma", "Calle Montevideo", "Calle Esmeralda",
                               "Avenida Potosi", "Calle Salaverry", "Calle Balcarce",
                               "Avenida Cordoba"
                              };
    int cantCalle=(sizeof(arregloCalle) / sizeof(arregloCalle[0]));
    int indiceAleatorio = randomRangoUsuarios(0, cantCalle - 1);
    strcpy(calle, arregloCalle[indiceAleatorio]);
}
void setAlturaRandom(int altura)
{
    int arregloAltura[20] = {1236, 4561, 789, 1015, 234,
                             567, 890, 1120, 3456, 678,
                             910, 1355, 246, 357, 468,
                             579, 680, 791, 902, 103
                            };
    int cantAltura=(sizeof(arregloAltura) / sizeof(arregloAltura[0]));
    int indiceAleatorio = randomRangoUsuarios(0, cantAltura - 1);
    altura= arregloAltura[indiceAleatorio];
}
void setCpRandom(int cp)
{
    int arregloCp[10] = {1000, 7600, 11001, 1001, 15700, 1010, 8002, 2000, 22000, 5000,
                         11500, 12345, 77500, 57000, 76001, 1200, 17002, 4000, 8090, 1014
                        };
    int cantCp=(sizeof(arregloCp) / sizeof(arregloCp[0]));
    int indiceAleatorio = randomRangoUsuarios(0, cantCp - 1);
    cp= arregloCp[indiceAleatorio];
}
void setCiudadRandom(char ciudad[])
{
    char arregloCiudad[][100] = {"Bogota", "Buenos Aires", "Santiago", "Lima", "Montevideo",
                                 "Ciudad de Mexico", "Guayaquil", "Quito", "San Jose", "Rosario",
                                 "Mar del Plata", "Cancun", "Cordoba", "La Paz", "Asuncion",
                                 "Caracas", "San Salvador", "Santo Domingo", "Tegucigalpa", "Panama"

                                };
    int cantCiudad=(sizeof(arregloCiudad) / sizeof(arregloCiudad[0]));
    int indiceAleatorio = randomRangoUsuarios(0, cantCiudad - 1);
    strcpy(ciudad, arregloCiudad[indiceAleatorio]);
}
void setLocalidadRandom(char localidad[])
{
    char arregloLocalidad[][50] = {"Palermo", "Miraflores", "Recoleta", "Providencia", "San Telmo",
                                   "Condesa", "Punta Carretas", "La Candelaria", "Chapinero", "San Isidro",
                                   "Villa Urquiza", "Barranco", "La Boca", "Caballito", "Lince",
                                   "Las Condes", "Almagro", "Vitacura", "Belgrano", "Barrio Norte"
                                  };
    int cantLocalidad=(sizeof(arregloLocalidad) / sizeof(arregloLocalidad[0]));
    int indiceAleatorio = randomRangoUsuarios(0, cantLocalidad - 1);
    strcpy(localidad, arregloLocalidad[indiceAleatorio]);
}
void setPaisRandom(char pais[])
{
    char arregloPais[][100] = {"Argentina", "Brasil", "Chile", "Colombia", "Mexico",
                               "Peru", "Venezuela", "Ecuador", "Bolivia", "Paraguay",
                               "Uruguay", "Honduras", "Guatemala", "El Salvador", "Nicaragua",
                               "Cuba", "Republica Dominicana", "Panama", "Costa Rica", "Paraguay"
                              };
    int cantPais=(sizeof(arregloPais) / sizeof(arregloPais[0]));
    int indiceAleatorio = randomRangoUsuarios(0, cantPais - 1);
    strcpy(pais, arregloPais[indiceAleatorio]);
}






