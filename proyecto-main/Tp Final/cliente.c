#include "generales.h"
#include "cliente.h"

///--------------------- Cargar un cliente ---------------------
//  Carga un cliente pasado por parametro.
void cargarUnCliente(stCliente *a, int id,FILE *archi){
    int validar = 0;

    printf("\tID....................: ");
    a->id = id;
    printf("%d", a->id);

    //  Verifico si ingresó un numero de cliente valido
    do{
        printf("\n\n\tNumero de Cliente.....: ");
        scanf("%d", &a->nroCliente);

        if(a->nroCliente < 0){
            printf("\n\tIngrese un Numero de Cliente valido.");
        }

    }while(a->nroCliente < 0);

    //  Verifico si ingresó un Nombre valido (Solo contenga letras).
    do{
        printf("\tNombre................: ");
        fflush(stdin);
        scanf("%s", a->nombre);

        validar = validarCadenaLetras(a->nombre);

        if(validar == 1){
            printf("\n\tIntroduce un nombre valido (solo letras).\n\n");
        }else{
            convertirNombreYApellido(a->nombre);
        }

    }while(validar == 1);

    //  Verifico si ingresó un Apellido valido (Solo conternga letras).
    do{
        printf("\tApellido..............: ");
        fflush(stdin);
        scanf("%s", a->apellido);

        validar = validarCadenaLetras(a->apellido);

        if(validar == 1){
            printf("\n\tIntroduce un apellido valido (solo letras).\n\n");
        }else{
            convertirNombreYApellido(a->apellido);
        }
    }while(validar == 1);

    //  Verifico si ingresó un Dni valido (Que no esté repetido y que solo contenga numeros).
    do{
        printf("\tDNI...................: ");
        fflush(stdin);
        scanf("%s", a->dni);

        validar = validarCadenaNumeros(a->dni);
        if(validar == 1){
            printf("\n\n\tDni no valiudo, ingrese uno nuevamente.\n\n");
        }else{
            validar = validarDni(archi,a->dni);
            if(validar == 1){
                printf("\n\n\tDni ya ingresado, inse uno nuevamente.\n\n");
            }
        }

    }while(validar == 1);

    //  Verifico si ingreso un Email valido (Que contenga un arroba).
    do{
        printf("\tDireccion de correo...: ");/// comprobar si esta escribiendo una direccion de correo
        fflush(stdin);
        scanf("%s", a->email);

        validar = validarEmail(a->email);

        if(validar == 0){
            printf("\n\n\tEmail incorrecto, vuelva aingresarlo.\n\n");
        }
    }while(validar == 0);

    printf("\tDomicilio.............: ");
    fflush(stdin);
    gets(a->domicilio);

    printf("\tMovil.................: ");
    fflush(stdin);
    scanf("%s", a->movil);

    printf("\tEstado................: ");
    a->baja = 0;
    printf("%d", a->baja);
}
///--------------------- Cargar un cliente ---------------------


///--------------------- Convertir a Minusculas ---------------------
//  Convierte la primera letra del string a Mayuscula y el resto a minuscula.
void convertirNombreYApellido(char cadena[]){
    int i = 0;
    int l = strlen(cadena);
    cadena[i] = toupper(cadena[i]);

    for(i = 1;i < l;i++){
        cadena[i] = tolower(cadena[i]);
    }
}
///--------------------- Convertir a Minusculas ---------------------


///--------------------- Valida el email ---------------------
//  Verifica si el email tiene un "@".
int validarEmail(char email[]){
    int l = strlen(email);
    int validar = 0;

    for(int i = 0; i < l && validar == 0;i++){
        if(email[i] == '@'){
            validar = 1;
        }
    }

    return validar;
}
///--------------------- Valida el email ---------------------


///--------------------- Validar DNI ----------------------
int validarDni(FILE *archi,char dni[]){
    int validar = 0;
    stCliente a;
    rewind(archi);

    while(fread(&a,sizeof(stCliente),1,archi)){
        if(strcmp(a.dni,dni) == 0 && a.baja == 0){
            validar = 1;
        }
    }
    return validar;
}
///--------------------- Validar DNI ----------------------



///--------------------- Da de baja a un cliente ---------------------
//  Busca en el archivo el id pasado por parametro, y cambia el campo "baja" por 1.
int eliminarCliente(const char archivo[], int id){
    stCliente a;
    int flag = 0;
    FILE *archi = fopen(archivo,"r+b");

    if(archi){
        while(flag == 0 && fread(&a,sizeof(stCliente),1,archi) > 0){
            if(id == a.id){
                fseek(archi,sizeof(stCliente) * -1, SEEK_CUR);
                a.baja = 1;
                fwrite(&a,sizeof(stCliente),1,archi);
                flag = 1;
            }
        }
        fclose(archi);
    }
    return flag;
}
///--------------------- Da de baja a un cliente ---------------------



///--------------------- Meunu de modificar cliente ---------------------
char menuModificar(){

    char opcion;

    do{
        printf("\n\n\t\t\tMenu de opciones a modificar: ");
        printf("\n\n\n\t1. Nuemero de cliente.");
        printf("\n\n\t2. Nombre.");
        printf("\n\n\t3. Apellido.");
        printf("\n\n\t4. DNI.");
        printf("\n\n\t5. Email.");
        printf("\n\n\t6. Domicilio.");
        printf("\n\n\t7. Movil.");
        printf("\n\n\t8. Todas");

        printf("\n\n\tElija una pcion: ");
        opcion = getch();

        system("cls");

    }while(opcion < 49 || opcion > 56);

    return opcion;
}
///--------------------- Meunu de modificar cliente ---------------------

///--------------------- Modificar cliente ---------------------
//  Modifica un campo a eleccion del cliente con el id pasado por parametro.
void modificarCliente(const char archivo[], int id){
    char opcion;
    int pos = id;
    int validar = 0;
    int y = 15;
    int posicionAnterior = 0;
    stCliente a;

    FILE *archi = fopen(archivo,"r+b");

    if(archi && pos >= 0 && pos < contarRegistros(archivo,sizeof(stCliente))){

        fseek(archi,sizeof(stCliente)*pos,SEEK_SET);
        fread(&a,sizeof(stCliente),1,archi);
        fseek(archi,sizeof(stCliente)*-1,SEEK_CUR);

        printf("\n\t\t\tRegistro viejo: \n");
        muestraUnCliente(a);

        opcion = menuModificar();

        printf("\n\t\t\tRegistro viejo: \n");
        muestraUnCliente(a);

        switch(opcion){
            case '1':
                do{
                    gotoxy(8,y);
                    printf("Numero de Cliente.....: ");
                    scanf("%d", &a.nroCliente);

                    if(a.nroCliente < 0){
                        printf("\n\tIngrese un Numero de Cliente valido.");
                        y+=4;
                    }

                }while(a.nroCliente < 0);

                break;
            case '2':
                do{
                    gotoxy(8,y);
                    printf("Nombre................: ");
                    fflush(stdin);
                    scanf("%s", a.nombre);

                    validar = validarCadenaLetras(a.nombre);

                    if(validar == 1){
                        printf("\n\tIntroduce un nombre valido (solo letras).\n\n");
                        y+=4;
                    }else{
                        convertirNombreYApellido(a.nombre);
                    }

                }while(validar == 1);
                break;
            case '3':
                do{
                    gotoxy(8,y);
                    printf("Apellido..............: ");
                    fflush(stdin);
                    scanf("%s", a.apellido);

                    validar = validarCadenaLetras(a.apellido);

                    if(validar == 1){
                        printf("\n\tIntroduce un apellido valido (solo letras).");
                        y+=5;
                    }else{
                        convertirNombreYApellido(a.apellido);
                    }
                }while(validar == 1);
                break;
            case '4':
                do{
                    gotoxy(8,y);
                    printf("DNI...................: ");
                    fflush(stdin);
                    scanf("%s", a.dni);

                    validar = validarCadenaNumeros(a.dni);

                    if(validar == 1){
                        printf("\n\tDni no valiudo, ingrese uno nuevamente.");
                        y+=4;
                    }else{
                        posicionAnterior = sizeof(stCliente) * a.id;
                        validar = validarDni(archi,a.dni);
                        if(validar == 1){
                            printf("\n\tDni ya ingresado, ingrese uno nuevamente.");
                            y+=4;
                        }
                        fseek(archi,posicionAnterior,SEEK_SET);
                    }

                }while(validar == 1);
                break;
            case '5':
                do{
                    gotoxy(8,y);
                    printf("Direccion de correo...: ");
                    fflush(stdin);
                    scanf("%s", a.email);

                    validar = validarEmail(a.email);

                    if(validar == 0){
                        printf("\n\n\tEmail incorrecto, vuelva aingresarlo.");
                        y+=5;
                    }
                }while(validar == 0);
                break;
            case '6':
                gotoxy(8,15);
                printf("Domicilio.............: ");
                fflush(stdin);
                gets(a.domicilio);
                break;
            case '7':
                gotoxy(8,15);
                printf("Movil.................: ");
                fflush(stdin);
                scanf("%s", a.movil);
                break;
            case '8':
                gotoxy(1,15);

                posicionAnterior = sizeof(stCliente)*a.id;

                cargarUnCliente(&a,id,archi);

                fseek(archi,posicionAnterior,SEEK_SET);
                break;
        }
        fwrite(&a,sizeof(stCliente),1,archi);

        printf("\n\t\t\tRegistro nuevo: \n");
        muestraUnCliente(a);

        fclose(archi);
    }else{
        printf("\nId no encontrado.");
    }
}
///--------------------- Modificar cliente ---------------------



///--------------------- Menu de consultar Cliente ---------------------
char menuConsulta(){
    char opcion;

    do{
        printf("\n\t\tMenu de Consulta\n\n");
        printf("\tConsultar por: ");
        printf("\n\n\t1. Id.");
        printf("\n\n\t2. Nro. Cliente.");
        printf("\n\n\t3. Nombre.");
        printf("\n\n\t4. Apellido.");
        printf("\n\n\t5. DNI.");
        printf("\n\n\t6. Direccion de correo.");
        printf("\n\n\t7. Domicilio.");
        printf("\n\n\t8. Movil.");

        printf("\n\n\tElija una opcion: ");

        opcion = getch();

        system("cls");

    }while(opcion < 49 || opcion > 56);

    return opcion;
}
///--------------------- Menu de consultar Cliente ---------------------

///--------------------- Consultar un Cliente ---------------------
//  Busca y muestra el cliente solicitado (Puede ser cualquier campo el que se utiliza para la busqueda).
void consultarUnCliente(const char archivo[], char opcion, char consulta[]){
    stCliente a;
    int flag = 0;

    int consultaEntero;

    FILE *archi = fopen(archivo,"rb");

    if(archi){
        switch(opcion){
            case '1':
                consultaEntero = atoi(consulta);

                while(fread(&a,sizeof(stCliente),1,archi) > 0 ){
                    if(a.id == consultaEntero && a.baja == 0){
                        muestraUnCliente(a);
                        printf("\n\n----------------------------------------------\n");
                        flag = 1;
                    }
                }
                break;
            case '2':
                consultaEntero = atoi(consulta);

                while(fread(&a,sizeof(stCliente),1,archi) > 0 ){
                    if(a.nroCliente == consultaEntero && a.baja == 0){
                        muestraUnCliente(a);
                        printf("\n\n----------------------------------------------\n");
                        flag = 1;
                    }
                }
                break;
            case '3':
                convertirNombreYApellido(consulta);
                while(fread(&a,sizeof(stCliente),1,archi) > 0 ){
                    if(strcmp(consulta,a.nombre) == 0 && a.baja == 0){
                        muestraUnCliente(a);
                        printf("\n\n----------------------------------------------\n");
                        flag = 1;
                    }
                }
                break;
            case '4':
                convertirNombreYApellido(consulta);
                while(fread(&a,sizeof(stCliente),1,archi) > 0 ){
                    if(strcmp(a.apellido,consulta) == 0 && a.baja == 0){
                        muestraUnCliente(a);
                        printf("\n\n----------------------------------------------\n");
                        flag = 1;
                    }
                }
                break;
            case '5':
                while(fread(&a,sizeof(stCliente),1,archi) > 0 ){
                    if(strcmp(a.dni,consulta) == 0 && a.baja == 0){
                        muestraUnCliente(a);
                        printf("\n\n----------------------------------------------\n");
                        flag = 1;
                    }
                }
                break;
            case '6':
                while(fread(&a,sizeof(stCliente),1,archi) > 0 ){
                    if(strcmp(a.email,consulta) == 0 && a.baja == 0){
                        muestraUnCliente(a);
                        printf("\n\n----------------------------------------------\n");
                        flag = 1;
                    }
                }
                break;
            case '7':
                while(fread(&a,sizeof(stCliente),1,archi) > 0 ){
                    if(strcmp(a.domicilio,consulta) == 0 && a.baja == 0){
                        muestraUnCliente(a);
                        printf("\n\n----------------------------------------------\n");
                        flag = 1;
                    }
                }
                break;
            case '8':
                while(fread(&a,sizeof(stCliente),1,archi) > 0 ){
                    if(strcmp(a.movil,consulta) == 0 && a.baja == 0){
                        muestraUnCliente(a);
                        printf("\n\n----------------------------------------------\n");
                        flag = 1;
                    }
                }
                break;
        }
        fclose(archi);
    }

    if(flag == 0){
        printf("\n\tCliente no encontrado.");
    }

}
///--------------------- Consultar un Cliente ---------------------



///--------------------- Muestra un Clientes---------------------
void muestraUnCliente(stCliente a){
    printf("\n\tID....................: %d", a.id);
    printf("\n\n\tNumero de Cliente.....: %d", a.nroCliente);
    printf("\n\tNombre................: %s", a.nombre);
    printf("\n\tApellido..............: %s", a.apellido);
    printf("\n\tDNI...................: %s", a.dni);
    printf("\n\tDireccion de correo...: %s", a.email);
    printf("\n\tDomicilio.............: %s", a.domicilio);
    printf("\n\tMovil.................: %s", a.movil);
    printf("\n\tEstado................: %d", a.baja);
}
///--------------------- Muestra un Clientes---------------------


///---------------------- Recorrer Archivo de clientes ----------------------
stCliente recorrerArchivoClientes(const char nombreArchivoClientes[],int idCliente){
    stCliente a;
    int flag = 0;

    FILE* archi = fopen(nombreArchivoClientes,"rb");

    if(archi){
        while(flag == 0 && fread(&a,sizeof(stCliente),1,archi)){
            if(a.id == idCliente){
                flag = 1;
            }
        }
        fclose(archi);
    }
    return a;
}
///---------------------- Recorrer Archivo de clientes ----------------------
