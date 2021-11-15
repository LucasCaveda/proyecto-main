#include "generales.h"
#include "cliente.h"
#include "consumo.h"

///---------------------- Cargar un Consumo ----------------------
void cargarUnConsumo(stConsumos *a, int id,const  char nombreArchivoClientes[]){
    int validar;

    int anioHoy;
    int mesHoy;
    int diaHoy;

    devolverFechaHoy(&anioHoy,&mesHoy,&diaHoy);

    printf("\tId...............: ");
    a->id = id;
    printf("%d",a->id);

    //  Verifica si el idCLiente ingresado, existe en el archivo Clientes
    do{
        printf("\n\n\tIdCliente........: ");
        scanf("%d", &a->idCliente);

        validar = validarCliente(a->idCliente,nombreArchivoClientes);

        if(validar == 0){
            printf("\n\n\tId de cliente no valido, ingrese un IdCliente nuevamente.");
        }

    }while(validar == 0);

    //  Verifica si el año ingresado es valido (Si es menor o igual al año actual).
    do{
        printf("\n\tAnio...............: ");
        scanf("%d", &a->anio);

        if(a->anio > anioHoy){
            printf("\n\n\tAnio incorrecto, ingreselo de nuevo.\n");
        }

    }while(a->anio > anioHoy);

    //  Verifica si el mes ingresado es valido (Mayor a 1 y Menor a 12, y si es menor o igual al mes actual).
    do{
        printf("\n\tMes................: ");
        scanf("%d", &a->mes);

        if(a->mes < 1 || a->mes > 12){
            printf("\n\n\tMes iconrrecto, ingresalo de nuevo.\n");
        }else{
            if(a->anio == anioHoy){
                if(a->mes > mesHoy){
                    printf("\n\n\tEl mes que ingreso, supera al mes actual. Ingrese el mes nuevamente.\n");
                }
            }
        }
    }while((a->anio == anioHoy && a->mes > mesHoy) || a->mes < 1 || a->mes > 12);

    //  Verifica si el día ingresado es valido (Dependende del mes y el año ingresado).
    do{
        printf("\n\tDia................: ");
        scanf("%d", &a->dia);

        if(a->anio == anioHoy && a->mes == mesHoy && a->dia > diaHoy){
            validar = 0;
        }else{
            validar = validarDia(a->dia,a->mes,a->anio);
        }

        if(validar == 0){
            printf("\n\n\tEl dia que ingreso es incorrecto, ingreselo de nuevo.\n");
        }

    }while(validar == 0);

    //  Verifica si los datos consumidos son validos (Mayor a 0).
    do{
        printf("\n\tDatos consumidos...: ");
        scanf("%d", &a->datosConsumidos);

        if(a->datosConsumidos < 0){
            printf("\n\n\tValor incorrecto. Ingreselo de nuevo\n");
        }
    }while(a->datosConsumidos < 0);

    printf("\n\tEstado.............: ");
    a->baja = 0;
    printf("%d", a->baja);
}
///---------------------- Cargar un Consumo ----------------------

///---------------------- Validar IdCliente ----------------------
//  Verifica si el IdCLiente existe en el archivo Clientes.
int validarCliente(int idCliente,const char nombreArchivoClientes[]){
    stCliente a;
    int validar = 0;
    int flag = 0;

    FILE *archi = fopen(nombreArchivoClientes,"rb");

    if(archi){
        while(flag == 0 && fread(&a,sizeof(stCliente),1,archi) > 0){
            if(a.id == idCliente){
                if(a.baja == 0){
                    validar = 1;
                }
                flag = 1;
            }
        }
        fclose(archi);
    }
    return validar;
}
///---------------------- Validar IdCliente ----------------------


///---------------------- Validar dia ----------------------
//  Verifica si el dia ingresado es valido
int validarDia(int dia, int mes,int anio){
    int validar = 0;
    int febrero = 28;

    if(anio % 4 == 0){
        febrero = 29;
    }

    switch(mes){
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            if(dia <= 31 && dia >= 1){
                validar = 1;
            }
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            if(dia <= 30 && dia >= 1){
                validar = 1;
            }
            break;
        case 2:
            if(dia <= febrero && dia >= 1){
                validar = 1;
            }
            break;
    }

    return validar;
}
///---------------------- Validar dia ----------------------


///---------------------- Agrega los datos consumidos a otro consumo ----------------------
void agregarConsumoPorFecha(const char archivo[],int id,int datosConsumidos){
    stConsumos a;

    FILE *archi = fopen(archivo,"r+b");

    if(archi){
        fseek(archi,sizeof(stConsumos)*id,SEEK_SET);
        if(fread(&a,sizeof(stConsumos),1,archi) > 0){
            fseek(archi,sizeof(stConsumos)*-1,SEEK_CUR);
            a.datosConsumidos = a.datosConsumidos + datosConsumidos;
            fwrite(&a,sizeof(stConsumos),1,archi);
        }
        fclose(archi);
    }
}
///---------------------- Agrega los datos consumidos a otro consumo ----------------------



///---------------------- Da de baja un consumo ----------------------
//  Busca en el archivo el id pasado por parametro, y cambia el campo "baja" por 1.
int eliminarConsumo(const char archivo[], int id){
    stConsumos a;
    int flag = 0;
    FILE *archi = fopen(archivo,"r+b");

    if(archi){
        while(flag == 0 && fread(&a,sizeof(stConsumos),1,archi) > 0){
            if(id == a.id){
                fseek(archi,sizeof(stConsumos) * -1, SEEK_CUR);
                a.baja = 1;
                fwrite(&a,sizeof(stConsumos),1,archi);
                flag = 1;
            }
        }
        fclose(archi);
    }
    return flag;
}
///---------------------- Da de baja un consumo ----------------------



///---------------------- Menu modificar un consumo ----------------------
char menuModificarConsumo(){

    char opcion;

    do{
        printf("\n\n\t\t\tMenu de opciones a modificar: ");
        printf("\n\n\n\t1. IdCliente.");
        printf("\n\n\t2. Anio.");
        printf("\n\n\t3. Mes.");
        printf("\n\n\t4. Dia.");
        printf("\n\n\t5. Datos consumidos.");
        printf("\n\n\t6. Todas.");

        printf("\n\n\tElija una pcion: ");
        opcion = getch();

        system("cls");
    }while(opcion < 49 || opcion > 54);

    return opcion;
}
///---------------------- Menu modificar un consumo ----------------------


///---------------------- Modifica un Consumo ----------------------
void modificarConsumo(const char archivo[], int id,const char nombreArchivoClientes[]){
    char opcion;
    int pos = id;
    int validar = 0;
    int y = 15;

    int anioHoy;
    int mesHoy;
    int diaHoy;

    int cambioLaFecha = 0;

    devolverFechaHoy(&anioHoy,&mesHoy,&diaHoy);

    stConsumos a;
    stConsumos consumoFecha;

    FILE *archi = fopen(archivo,"r+b");

    if(archi && pos >= 0 && pos < contarRegistros(archivo,sizeof(stConsumos))){

        fseek(archi,sizeof(stConsumos)*pos,SEEK_SET);
        fread(&a,sizeof(stConsumos),1,archi);
        fseek(archi,sizeof(stConsumos)*-1,SEEK_CUR);

        printf("\n\t\t\tRegistro viejo: \n");
        muestraUnConsumo(a);

        opcion = menuModificarConsumo();

        printf("\n\t\t\tRegistro viejo: \n");
        muestraUnConsumo(a);

        switch(opcion){
            case '1':
                do{
                    printf("\n\n\tIdCliente........: ");
                    scanf("%d", &a.idCliente);

                    validar = validarCliente(a.idCliente,nombreArchivoClientes);

                    if(validar == 0){
                        printf("\n\n\tId de cliente no valido, ingrese un IdCliente nuevamente.");
                    }
                }while(validar == 0);
                break;
            case '2':
                do{
                    gotoxy(8,y);
                    printf("Anio................: ");
                    scanf("%d", &a.anio);

                    if(a.anio > anioHoy || (a.anio == anioHoy && a.mes > mesHoy)){
                        printf("\n\n\tAnio incorrecto, ingreselo de nuevo.\n");
                        y+=4;
                    }

                }while(a.anio > anioHoy || (a.anio == anioHoy && a.mes > mesHoy));

                cambioLaFecha = 1;

                break;
            case '3':
                do{
                    gotoxy(8,y);
                    printf("Mes...............: ");
                    scanf("%d", &a.mes);

                    if(a.mes < 1 || a.mes > 12){
                        printf("\n\n\tMes iconrrecto, ingresalo de nuevo.\n");
                        y+=4;
                    }else{
                        if(a.anio == anioHoy){
                            if(a.mes > mesHoy){
                                printf("\n\n\tEl mes que ingreso, supera al mes actual. Ingrese el mes nuevamente.\n");
                                y+=4;
                            }
                        }
                    }

                    validar = validarDia(a.dia,a.mes,a.dia);

                    if(validar == 0){
                        printf("El mes que ingreso, no corresponde con el dia del consumo, ingrese un mes valido.");
                        y+=4;
                    }

                }while((a.anio == anioHoy && a.mes > mesHoy) || a.mes < 1 || a.mes > 12 || validar == 0);

                cambioLaFecha = 1;

                break;
            case '4':
                do{
                    gotoxy(8,y);
                    printf("Dia...............: ");
                    scanf("%d", &a.dia);

                    if(a.anio == anioHoy && a.mes == mesHoy && a.dia > diaHoy){
                        validar = 0;
                    }else{
                        validar = validarDia(a.dia,a.mes,a.anio);
                    }

                    if(validar == 0){
                        printf("\n\n\tEl dia que ingreso es incorrecto, ingreselo de nuevo.\n");
                    }

                }while(validar == 0);

                cambioLaFecha = 1;

                break;
            case '5':
                do{
                    gotoxy(8,y);
                    printf("Datos consumidos....: ");
                    scanf("%d", &a.datosConsumidos);

                    if(a.datosConsumidos < 0){
                        printf("\n\n\tValor incorrecto. Ingreselo de nuevo\n");
                    }
                }while(a.datosConsumidos < 0);
                break;
            case '6':
                printf("\n\n");
                cargarUnConsumo(&a,id,nombreArchivoClientes);
                break;
        }

        if(cambioLaFecha == 1){
            consumoFecha = buscarConsumoFecha(archi,a.anio,a.mes,a.dia);

            if(consumoFecha.id != -1){
                agregarConsumoPorFecha(archivo,consumoFecha.id,a.datosConsumidos);
                printf("\n\n\tSe encontro otro consumo con la misma fecha\n\ty se sumaron los datos consumidos.");

                a.baja = 1;
            }
        }else{
            system("cls");
            printf("\n\t\t\tRegistro nuevo: \n");
            muestraUnConsumo(a);
        }

        fwrite(&a,sizeof(stConsumos),1,archi);

        fclose(archi);
    }else{
        printf("\nId no encontrado.");
    }
}
///---------------------- Modifica un Consumo ----------------------



///--------------------- Menu de consultar Consumo ---------------------
char menuConsultaConsumo(){
    char opcion;

    do{
        printf("\n\t\tMenu de Consulta\n\n");
        printf("\tConsultar por: ");
        printf("\n\n\t1. ID.");
        printf("\n\n\t2. ID de Cliente.");
        printf("\n\n\t3. A%co", 164);
        printf("\n\n\t4. Mes.");
        printf("\n\n\t5. Dia.");
        printf("\n\n\t6. Datos Consumidos.");

        printf("\n\n\tElija una opcion: ");

        opcion = getch();
    }while(opcion < 49 || opcion > 54);

    return opcion;
}
///--------------------- Menu de consultar Consumo ---------------------


///--------------------- Consultar Consumo ---------------------
void consultarUnConsumo(const char archivo[], char opcion, int consulta){
    stConsumos a;
    int flag = 0;

    //int consultaEntero;

    FILE *archi = fopen(archivo,"rb");

    if(archi){
        switch(opcion){
            case '1':
                while(fread(&a,sizeof(stConsumos),1,archi) > 0 ){
                    if(a.id == consulta){
                        muestraUnConsumo(a);
                        printf("\n\n----------------------------------------------\n");
                        flag = 1;
                    }
                }
                break;
            case '2':
                while(fread(&a,sizeof(stConsumos),1,archi) > 0 ){
                    if(a.idCliente == consulta){
                        muestraUnConsumo(a);
                        printf("\n\n----------------------------------------------\n");
                        flag = 1;
                    }
                }
                break;
            case '3':
                while(fread(&a,sizeof(stConsumos),1,archi) > 0 ){
                    if(a.anio == consulta){
                        muestraUnConsumo(a);
                        printf("\n\n----------------------------------------------\n");
                        flag = 1;
                    }
                }
                break;
            case '4':
                while(fread(&a,sizeof(stConsumos),1,archi) > 0 ){
                    if(a.mes == consulta){
                        muestraUnConsumo(a);
                        printf("\n\n----------------------------------------------\n");
                        flag = 1;
                    }
                }
                break;
            case '5':
                while(fread(&a,sizeof(stConsumos),1,archi) > 0 ){
                    if(a.dia == consulta){
                        muestraUnConsumo(a);
                        printf("\n\n----------------------------------------------\n");
                        flag = 1;
                    }
                }
                break;
            case '6':
                while(fread(&a,sizeof(stConsumos),1,archi) > 0 ){
                    if(a.datosConsumidos == consulta){
                        muestraUnConsumo(a);
                        printf("\n\n----------------------------------------------\n");
                        flag = 1;
                    }
                }
                break;
        }
        fclose(archi);
    }

    if(flag == 0){
        printf("\n\tConsumo no encontrado.");
    }

}
///--------------------- Consultar Consumo ---------------------


///--------------------- Menu de Buscar consumo por fecha ---------------------
stConsumos menuBuscarConsumoFecha(const char archivo[]){
    stConsumos consumo;
    int anio;
    int mes;
    int dia;

    FILE *archi = fopen(archivo,"rb");

    if(archi){
        printf("\n\t\tBuscar consumo por fecha");

        printf("\n\n\tIngresar anio: ");
        scanf("%d", &anio);

        printf("\n\tIngresar mes: ");
        scanf("%d", &mes);

        printf("\n\tIngresar dia: ");
        scanf("%d", &dia);

        system("cls");

        consumo = buscarConsumoFecha(archi,anio,mes,dia);
        fclose(archi);
    }
    return consumo;
}
///--------------------- Menu de Buscar consumo por fecha ---------------------


///--------------------- Buscar consumo por fecha ---------------------
stConsumos buscarConsumoFecha(FILE *archi,int anio, int mes, int dia){
    stConsumos a;
    stConsumos busqueda;
    int flag = 0;

    rewind(archi);

    while(flag == 0 && fread(&a,sizeof(stConsumos),1,archi) > 0){
        if(a.anio == anio && a.mes == mes && a.dia == dia && a.baja == 0){
            busqueda = a;
            flag = 1;
        }
    }

    if(flag == 0){
        busqueda.id = -1;
    }
    return busqueda;
}
///--------------------- Buscar consumo por fecha ---------------------


///---------------------- Muestra un consumo ----------------------
void muestraUnConsumo(stConsumos a){
    //printf("\n\tId..................: %d", a.id);
    printf("\n\n\tIdCliente...........: %d", a.idCliente);
    printf("\n\tAnio................: %d", a.anio);
    printf("\n\tMes.................: %d", a.mes);
    printf("\n\tDia.................: %d", a.dia);
    printf("\n\tDatos consumidos....: %d", a.datosConsumidos);
    printf("\n\tEstado..............: %d", a.baja);
}
///---------------------- Muestra un consumo ----------------------

