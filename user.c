#include "user.h"
#include <ctype.h>
nodoArbolUsuario * inicArbol()
{
    return NULL;
}
nodoArbolUsuario * crearNodoArbol(stUsuario u)
{
    nodoArbolUsuario * aux=(nodoArbolUsuario *)malloc(sizeof(nodoArbolUsuario));
    aux->usuario=u;
    aux->izq=NULL;
    aux->der=NULL;
    return aux;
}
nodoArbolUsuario * archivoToArbol(char nombreArchivo[], nodoArbolUsuario * arbol)
{
    FILE * archi = fopen(nombreArchivo, "rb");
    stUsuario u;
    if (archi)
    {
        while (fread(&u, sizeof(stUsuario), 1, archi) > 0)
        {
            nodoArbolUsuario * nuevoNodo = crearNodoArbol(u);
            arbol = insertarNodoArbol(arbol, nuevoNodo);
        }
        fclose(archi);
    }
    return arbol;
}
void arbolToArchivoAux(FILE *archi, nodoArbolUsuario *arbol)
{
    if (arbol)
    {
        fwrite(&(arbol->usuario), sizeof(stUsuario), 1, archi);
        arbolToArchivoAux(archi, arbol->izq);
        arbolToArchivoAux(archi, arbol->der);
    }
}

void arbolToArchivo(char nombreArchivo[], nodoArbolUsuario *arbol)
{
    FILE *archi = fopen(nombreArchivo, "wb");
    if (archi)
    {
        arbolToArchivoAux(archi, arbol);
        fclose(archi);
    }
}

nodoArbolUsuario * insertarNodoArbol(nodoArbolUsuario * arbol,nodoArbolUsuario * nuevo)
{
    if(!arbol)
    {
        arbol=nuevo;
    }
    else
    {
        if(arbol->usuario.idUsuario!=nuevo->usuario.idUsuario)
        {
            if(arbol->usuario.idUsuario>nuevo->usuario.idUsuario)
            {
                arbol->izq=insertarNodoArbol(arbol->izq,nuevo);
            }
            else
            {
                arbol->der=insertarNodoArbol(arbol->der,nuevo);
            }
        }
    }
    return arbol;
}

nodoArbolUsuario * crearNodoUser(nodoArbolUsuario * arbol)
{
    stUsuario userAux = cargaDatosUser(arbol);
    nodoArbolUsuario * nuevoNodo = crearNodoArbol(userAux);
    return nuevoNodo;
}



///Funciones de busqueda
nodoArbolUsuario * buscarUsuario(char userIngresado[], nodoArbolUsuario * arbol)
{
    nodoArbolUsuario * aux=NULL;
    if(arbol!=NULL)
    {
        if(strcmp(arbol->usuario.email,userIngresado)==0)
        {
            aux=arbol;
        }
        else
        {
            aux=buscarUsuario(userIngresado,arbol->izq);
            if(aux==NULL)
            {
                aux=buscarUsuario(userIngresado,arbol->der);
            }
        }
    }
    return aux;
}


nodoArbolUsuario * buscarUsuarioXId(nodoArbolUsuario * arbol,int id)
{
    nodoArbolUsuario * aux=NULL;
    if(arbol!=NULL)
    {
        if(arbol->usuario.idUsuario==id)
        {
            aux=arbol;
        }
        else
        {
            if(arbol->usuario.idUsuario>id)
            {
                arbol->izq=buscarUsuarioXId(arbol->izq,id);
            }
            else
            {
                arbol->der=buscarUsuarioXId(arbol->der,id);
            }
        }
    }
    return aux;
}

///Funciones para Mostrar

void muestraUnUsuario(stUsuario u)
{

    printf("\n-----------------------------------\n");
    printf("Id: ................%i\n",u.idUsuario);
    printf("Nombre: ..............%s\n",u.username);
    printf("DNI: ..............%s\n",u.dni);
    printf("Direccion: ..............%s %s %d\n",u.domicilio.calle, "  ", u.domicilio.altura);
    printf("Localidad: ..............%s\n",u.domicilio.localidad);
    printf("Pais: ..............%s\n",u.domicilio.pais);
    printf("Email: ................%s\n",u.email);
    printf("Fecha de nacimiento: ................%s\n",u.fechaNacimiento);
    printf("Genero: ................%c\n",u.genero);
    printf("\n-----------------------------------\n");
}

void muestraNodoUser(nodoArbolUsuario * nodo)
{
    muestraUnUsuario(nodo->usuario);

}
void muestraArbol(nodoArbolUsuario * arbol)
{
    if(arbol)
    {
        muestraArbol(arbol->izq);
        muestraNodoUser(arbol);
        muestraArbol(arbol->der);
    }
}
void muestraArbolAdmin(nodoArbolUsuario * arbol)
{
    if(arbol)
    {
        muestraArbolAdmin(arbol->izq);
        muestraNodoUserAdmin(arbol);
        muestraArbolAdmin(arbol->der);
    }

}
void muestraNodoUserAdmin(nodoArbolUsuario * nodo)
{
    muestraUnUsuarioAdmin(nodo->usuario);

}
void muestraUnUsuarioAdmin(stUsuario u)
{

    printf("\n-----------------------------------\n");
    printf("Id: ................%i\n",u.idUsuario);
    printf("Nombre: ..............%s\n",u.username);
    printf("DNI: ..............%s\n",u.dni);
    printf("Direccion: ..............%s %s %d\n",u.domicilio.calle, "  ", u.domicilio.altura);
    printf("Localidad: ..............%s\n",u.domicilio.localidad);
    printf("Pais: ..............%s\n",u.domicilio.pais);
    printf("Email: ................%s\n",u.email);
    printf("Password: ................%s\n",u.password);
    printf("Fecha de nacimiento: ................%s\n",u.fechaNacimiento);
    printf("Genero: ................%c\n",u.genero);
    printf("Admin: ................%d\n",u.esAdmin);
    printf("Eliminado: ................%d\n",u.eliminado);
    printf("\n-----------------------------------\n");
}
///Funciones de verificacion

int verificar(char userIngresado[],char claveIngresado[],nodoArbolUsuario * arbol)
{
    int flag=0;
    nodoArbolUsuario * userAux;
    userAux=buscarUsuario(userIngresado,arbol);
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


int verificarPassword(char claveIngresado[], nodoArbolUsuario * userAux)
{
    int flag=0;
    if(strcmp(userAux->usuario.password,claveIngresado)==0)
    {
        flag=1;
    }
    return flag;
}
int verificacionPasswordCondiciones(char password[])  // Funci�n para cuando se registran personas
{
    int tieneMayuscula = 0;
    int tieneMinuscula = 0;
    int flag = 0;

    while (*password)
    {
        if (isupper((unsigned char)*password))
        {
            tieneMayuscula = 1;
        }
        else if (islower((unsigned char)*password))
        {
            tieneMinuscula = 1;
        }
        if (tieneMayuscula && tieneMinuscula)
        {
            flag = 1;
            break;
        }
        password++;
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

    for(i=0; i<longitud; i++)
    {
        if(email[i]=='@')
        {
            if(arrobaPos==-1)
            {
                arrobaPos=i;
            }
            else
            {
                esValido=false;
            }
        }

        if(email[i]=='.')
        {
            puntoPos=i;
        }
    }
    if(arrobaPos==-1 || puntoPos==-1 || puntoPos<=arrobaPos + 1 || puntoPos>=longitud - 1)
    {
        esValido=false;
    }
    return esValido;
}



///Funciones de Carga
stUsuario crearUserAdmin()
{
    stUsuario admin;
    admin.esAdmin=1;
    strcpy(admin.username,"Admin");
    admin.eliminado=0;
    admin.idUsuario=0;
    strcpy(admin.email,"admin@admin.com.ar");
    strcpy(admin.password,"Admin1");
    strcpy(admin.dni,"1111");
    strcpy(admin.domicilio.calle,"admin");
    admin.domicilio.altura=1111;
    admin.genero='M';
    strcpy(admin.domicilio.localidad,"Mdp");
    strcpy(admin.domicilio.pais,"Arg");
    strcpy(admin.fechaNacimiento,"01/01/2000");
    return admin;
}
nodoArbolUsuario * cargaUserAdmin(nodoArbolUsuario * arbol)
{
    stUsuario admin=crearUserAdmin();
    arbol=insertarNodoArbol(arbol,crearNodoArbol(admin));
    return arbol;
}

int verificarEmailEnArbol(char email[], nodoArbolUsuario *arbol)
{
    int flag = 1;

    if (arbol != NULL)
    {


        if (strcmp(arbol->usuario.email, email) == 0)
        {
            flag = 0;
            printf("Este email ya esta en uso: %s\n", email);
        }
        else
        {

            if (flag == 1)
            {
                flag = verificarEmailEnArbol(email, arbol->izq);
            }
            if (flag == 1)
            {
                flag = verificarEmailEnArbol(email, arbol->der);
            }
        }
    }

    return flag;
}


stUsuario cargaDatosUser(nodoArbolUsuario * arbol)
{
    char password[20];
    stUsuario user;
    bool esValido = false;
    int flag = 1;

    while (esValido==false || flag != 1)
    {
        printf("Ingrese su email: \n");
        fflush(stdin);
        gets(user.email);
        esValido = validarEmail(user.email);
        flag = verificarEmailEnArbol(user.email, arbol);
    }

    do
    {
        printf("\nLa password tiene que tener una mayuscula y una minuscula por lo menos\n");
        printf("Ingrese su password: \n");
        leerPassword(password, sizeof(password));
        strcpy(user.password, password);
    }
    while (!verificacionPasswordCondiciones(user.password));

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
    scanf(" %c", &user.genero);

    user.domicilio = cargaDomicilio();
    user.librosFavoritos[0] = 0;
    user.eliminado = 0;
    user.esAdmin = 0;
    user.idUsuario = sumarId(arbol);

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
nodoArbolUsuario * nodoMasDerecho(nodoArbolUsuario * arbol)
{
    while (arbol!=NULL && arbol->der!=NULL)
    {
        arbol = arbol->der;
    }
    return arbol;
}

int sumarId(nodoArbolUsuario * arbol)
{
    int id = 1;
    nodoArbolUsuario * ultimo = nodoMasDerecho(arbol);
    if (ultimo!=NULL)
    {
        id = ultimo->usuario.idUsuario + 1;
    }
    return id;
}


///Funciones de carga random
stUsuario cargaDatosUserRandom()
{
    stUsuario user;
    int usados[20] = {0};
    int restantes = 20;
    setMailRandom(user.email);
    setPasswordRandom(user.password);
    setUsernameRandom(user.username);;
    setGeneroRandom(&user.genero);
    setFechaNacimientoRandom(user.fechaNacimiento);
    setDniRandom(user.dni,usados,&restantes);
    user.domicilio=cargaDomicilioRandom();
    user.librosFavoritos[0]=0;
    user.eliminado=0;
    user.esAdmin=0;


    return user;

}
stDomicilio cargaDomicilioRandom()
{

    stDomicilio domicilio;
    setCalleRandom(domicilio.calle);
    setAlturaRandom(&domicilio.altura);
    setCiudadRandom(domicilio.ciudad);
    setLocalidadRandom(domicilio.localidad);
    setPaisRandom(domicilio.pais);
    setCpRandom(domicilio.cp);
    return domicilio;
}
void cargarUsuarioArchivoRandom(char nombreArchivo[], nodoArbolUsuario * arbol)
{

    FILE * buffer = fopen(nombreArchivo,"ab");
    stUsuario aux;
    char opcion = 0;
    int i = 0;

    nodoArbolUsuario * aux1= nodoMasDerecho(arbol);
    int ultimoIdUsuario;
    if(aux1==NULL)
    {
        ultimoIdUsuario=0;
    }
    else
    {
        ultimoIdUsuario=aux1->usuario.idUsuario;
    }
    if(buffer)
    {
        do
        {
            printf("Usuario %d\n", ultimoIdUsuario + 1);
            aux = cargaDatosUserRandom();
            aux.idUsuario= ultimoIdUsuario+1;
            fwrite(&aux,sizeof(stUsuario),1,buffer);
            ultimoIdUsuario++;
            i++;

            printf("Desea seguir cargando? Presione 'n' para salir \n");
            fflush(stdin);
            scanf("%c",&opcion);
        }
        while(opcion != 'n');
        fclose(buffer);

    }
}
///Menu
nodoArbolUsuario * modificarDatos(nodoArbolUsuario * user,nodoArbolUsuario * arbol)
{
    int opcion;
    do
    {
        system("cls");
        printf("\nQue dato desea cambiar\n");
        opcionesModificarDatos();
        fflush(stdin);
        scanf("%d",&opcion);
        switch(opcion)
        {
        case 1:
            ///cambiar email
            cambiarEmail(user->usuario.email,arbol);
            break;
        case 2:
            cambioUserName(user->usuario.username);
            break;
        case 3:
            user->usuario=cambioPassword(user->usuario);
            break;
        case 4:
            cambioGenero(&user->usuario.genero);
            break;
        case 5:
            cambiarFechaNacimiento(user->usuario.fechaNacimiento);
            break;
        case 6:
            user->usuario.domicilio=cargaDomicilio();
            break;
        case 0:
            system("cls");
            printf("\n--- Volviendo al menu ---\n");
            break;
        }
    }
    while(opcion!=0);
    return user;
}
void opcionesModificarDatos()
{
    printf("\n   1. Email\n");
    printf("\n   2. Nombre\n");
    printf("\n   3. Password\n");
    printf("\n   4. Genero\n");
    printf("\n   5. Fecha de nacimiento\n");
    printf("\n   6. Domicilio\n");
    printf("\n   0. Salir\n");
}
void cambiarEmail(char *email, nodoArbolUsuario *arbol)
{
    char nuevoEmail[100];
    bool esValido = false;
    int flag = 1;

    do
    {
        printf("Ingrese su nuevo email: \n");
        scanf("%s", nuevoEmail);
        esValido = validarEmail(nuevoEmail);

        if (esValido)
        {
            flag = verificarEmailEnArbol(nuevoEmail, arbol);
        }

    } while (!esValido || flag == 0);

    strcpy(email, nuevoEmail);
    printf("Email actualizado correctamente.\n");
    system("pause");
}




void cambioUserName(char * userName)
{
    printf("\nIngrese su nombre: \n");
    scanf("%s",userName);
}

stUsuario cambioPassword(stUsuario user)
{
    char password[20];
    printf("\nIngrese nueva password: \n");

    leerPassword(password, sizeof(password));

    strcpy(user.password, password);

    return user;
}
void leerPassword(char *password, int maxLength)
{
    int i = 0;
    char ch;

    while (i < maxLength - 1)
    {
        ch = getch();
        if (ch == 13)
        {
            password[i] = '\0';
            break;
        }
        else if (ch == 8)
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else
        {
            password[i] = ch;
            i++;
            printf("*");
        }
    }

    password[i] = '\0';
}
void cambioGenero(char *genero) {
    *genero = (*genero == 'M' || *genero == 'm') ? 'F' : 'M';
}
void cambiarFechaNacimiento(char *fechaNacimiento) {
    printf("\nIngrese su fecha de nacimiento (dd/mm/yyyy): \n");
    scanf("%s",fechaNacimiento);
}


nodoArbolUsuario * darDeBajaUser(nodoArbolUsuario *user) {
    int opcion;

    printf("\nSi ingresa 1 se dara de baja\n");
    printf("Si ingresa 0 vuelve al menu\n");
    scanf("%d", &opcion);

    if (opcion == 1) {
        user->usuario.eliminado = -1;
        printf("\nUsuario dado de baja.\n");
    } else if (opcion == 0) {
        printf("\n--- Volviendo al menu ---\n");
    } else {
        printf("\nOpcion no valida.\n");
    }
    return user;
}


nodoArbolUsuario * darDeBajaUserAdmin(nodoArbolUsuario * arbol)
{
    int opcion;
    nodoArbolUsuario * aux=inicArbol();
    printf("\nIngrese el ID del usuario que desea dar de baja: \n");
    fflush(stdin);
    scanf("%d",&opcion);
    aux=buscarUsuarioXId(arbol,opcion);
    if(aux==NULL)
    {
        printf("\nEl usuario con ID %d no existe.",opcion);
    }
    else
    {
        aux=darDeBajaUser(aux);
    }
    return arbol;
}
nodoArbolUsuario * darDeAltaUserAdmin(nodoArbolUsuario * arbol)
{
    int opcion;
    nodoArbolUsuario * aux=inicArbol();
    printf("\nIngrese el ID del usuario que desea dar de alta: \n");
    scanf("%d",&opcion);
    aux=buscarUsuarioXId(arbol,opcion);
    aux->usuario.eliminado=0;
    return arbol;
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
void setGeneroRandom(char* genero)
{
    char arregloGenero[] = {'F', 'M'};  // Define un array de caracteres
    int cantGenero = sizeof(arregloGenero) / sizeof(arregloGenero[0]);
    int indiceAleatorio = randomRangoUsuarios(0, cantGenero - 1);
    *genero = arregloGenero[indiceAleatorio];  // Asigna el car�cter directamente
}
void setFechaNacimientoRandom(char fechaNacimiento[])
{
    char arregloFechaNacimiento[][20] = {"7/08/1996", "15/01/1985", "23/03/1990",
                                         "10/04/1978", "5/11/2000", "30/06/1992", "18/09/1988",
                                         "25/12/1995", "9/02/1983", "12/10/1975", "3/07/2001", "27/5/1997",
                                         "14/08/1993", "21/06/1980", "6/11/1998", "19/04/1986", "28/02/1994",
                                         "8/01/1991", "11/12/1982", "4/07/1989"
                                        };
    int cantFechaNacimiento=(sizeof(arregloFechaNacimiento) / sizeof(arregloFechaNacimiento[0]));
    int indiceAleatorio = randomRangoUsuarios(0, cantFechaNacimiento - 1);
    strcpy(fechaNacimiento, arregloFechaNacimiento[indiceAleatorio]);
}
void setDniRandom(char dni[],int usados[], int *restantes)
{
    char arregloDni[][20] = {"30678923", "28765432", "39874567", "32984756", "41928374",
                             "56473829", "61283947", "23829156", "45673820", "50192834",
                             "34718294", "29183746", "64829371", "43482915", "58391024",
                             "69382047", "47283910", "52938471", "61829304", "78912345"
                            };
    int cantDni=sizeof(arregloDni) / sizeof(arregloDni[0]);
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
void setAlturaRandom(int *altura)
{
    int arregloAltura[20] = {1236, 4561, 789, 1015, 234,
                             567, 890, 1120, 3456, 678,
                             910, 1355, 246, 357, 468,
                             579, 680, 791, 902, 103
                            };
    int cantAltura=(sizeof(arregloAltura) / sizeof(arregloAltura[0]));
    int indiceAleatorio = randomRangoUsuarios(0, cantAltura - 1);
    *altura= arregloAltura[indiceAleatorio];
}
void setCpRandom(int cp)
{
    int arregloCp[20] = {1000, 7600, 11001, 1001, 15700, 1010, 8002, 2000, 22000, 5000,
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


///Funciones de favoritos
void agregarLibroAFavoritosUsuario(nodoArbolUsuario* nodoUsuario, nodo2Libros* listaLibros, int idLibro)
{
    stUsuario* usuario = &nodoUsuario->usuario;

    for (int i = 0; i < usuario->validosLibrosFavs; i++)
    {
        if (usuario->librosFavoritos[i] == idLibro)
        {
            printf("El libro con ID %d ya esta en la lista de favoritos.\n", idLibro);
            return;
        }
    }
    nodo2Libros* libro = buscarLibroPorId(listaLibros, idLibro);
    if (libro != NULL)
    {
        if (usuario->validosLibrosFavs < 50)    // Verificar si la lista no est� llena
        {
            usuario->librosFavoritos[usuario->validosLibrosFavs] = idLibro;
            usuario->validosLibrosFavs++;
            printf("El libro '%s' ha sido agregado a la lista de favoritos del usuario %s.\n", libro->dato.titulo, usuario->username);
        }
        else
        {
            printf("La lista de libros favoritos esta llena.\n");
        }
    }
    else
    {
        printf("Libro con ID %d no encontrado en la lista de libros.\n", idLibro);
    }
}

void mostrarLibrosFavoritos(nodoArbolUsuario* nodoUsuario, nodo2Libros* listaLibros)
{
    stUsuario* usuario = &nodoUsuario->usuario;

    if (usuario->validosLibrosFavs == 0)
    {
        printf("El usuario %s no tiene libros favoritos.\n", usuario->username);
    }
    else
    {
        //setColor(1);
        printf("Libros favoritos de %s:\n", usuario->username);
        //setColor(7);
        for (int i = 0; i < usuario->validosLibrosFavs; i++)
        {
            int idFavorito = usuario->librosFavoritos[i];
            nodo2Libros* libro = buscarLibroPorId(listaLibros, idFavorito);
            if (libro != NULL && libro->dato.eliminado == 0)
            {
                muestraUnLibro(libro->dato);
            }
            else
            {
                printf("Libro con ID %d no encontrado o est� eliminado.\n", idFavorito);
            }
        }
    }
}

void quitarLibroDeFavoritosUsuario(nodoArbolUsuario* nodoUsuario, int idLibro)
{

    stUsuario* usuario = &nodoUsuario->usuario;
    int encontrado = 0;

    for (int i = 0; i < usuario->validosLibrosFavs; i++)
    {
        if (usuario->librosFavoritos[i] == idLibro)
        {
            encontrado = 1;
            for (int j = i; j < usuario->validosLibrosFavs - 1; j++)
            {
                usuario->librosFavoritos[j] = usuario->librosFavoritos[j + 1];
            }
            usuario->validosLibrosFavs--;
            printf("El libro con ID %d ha sido eliminado de los favoritos del usuario %s.\n", idLibro+1, usuario->username);
            break;
        }
    }

    if (!encontrado)
    {
        printf("El libro con ID %d no est� en la lista de favoritos del usuario %s.\n", idLibro, usuario->username);
    }
}
void opcionAgregarLibroAFavoritos(nodoArbolUsuario * usuario, nodo2Libros* libros)
{

    int opcion;
    int idLibro;
    //setColor(1);
    printf("Conoces el ID del libro que quieres agregar a favoritos?\n");
    printf("1. Si\n");
    printf("2. No, mostrar lista de libros\n");
    printf("Elige una opci�n (1 o 2): ");
    scanf("%d", &opcion);

    switch (opcion)
    {
    case 1:
        // El usuario conoce el ID del libro
        printf("Ingresa el ID del libro que deseas agregar a favoritos: ");
        scanf("%d", &idLibro);
        idLibro=idLibro-1;
        agregarLibroAFavoritosUsuario(usuario, libros, idLibro);
        break;

    case 2:
        printf("Lista de libros disponibles:\n");
        muestraListaLibros(libros);
        printf("\nIngresa el ID del libro que deseas agregar a favoritos: ");
        scanf("%d", &idLibro);
        idLibro=idLibro-1;
        agregarLibroAFavoritosUsuario(usuario, libros, idLibro);
        break;

    default:
        printf("Opcion no valida.\n");
        break;
    }
    //setColor(7);
}
void opcionQuitarLibroDeFavoritos(nodoArbolUsuario* usuario, nodo2Libros* libros)
{
    stUsuario* user = &usuario->usuario;

    if (user->validosLibrosFavs == 0)
    {
        printf("La lista de favoritos est� vacia.\n");
        return;
    }

    int opcion;
    int idLibro;

    mostrarLibrosFavoritos(usuario, libros);
    //setColor(1);
    printf("\nDeseas quitar algun libro de favoritos?\n");
    printf("1. Si\n");
    printf("2. No\n");
    printf("Elige una opcion (1 o 2): ");
    scanf("%d", &opcion);

    if (opcion == 1)
    {
        printf("\nIngresa el ID del libro que deseas quitar de favoritos: ");
        scanf("%d", &idLibro);
        idLibro=idLibro-1;
        quitarLibroDeFavoritosUsuario(usuario, idLibro);
    }
    else if (opcion == 2)
    {
        printf("No se quitara ningun libro.\n");
    }
    else
    {
        printf("Opcion no valida.\n");
    }
    //setColor(7);
}




