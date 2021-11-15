#include "cliente.h"
#include "clientes.h"

///--------------------- Cargar archivo Clientes ---------------------
void cargaArchivoClientes(const char archivo[]){
    char opcion = 0;
    int id = pasarUltimoIdClientes(archivo) + 1;

    stCliente a;

    FILE *pArchiClientes = fopen(archivo,"a+b");
    if(pArchiClientes != NULL){
        do{
            printf("\n\n");

            cargarUnCliente(&a,id,pArchiClientes);

            fwrite(&a, sizeof(stCliente), 1, pArchiClientes);

            id++;

            printf("\n\n\t ESC para salir - cualquier tecla para continuar");
            opcion = getch();
            system("cls");
        }
        while(opcion!=27);

        fclose(pArchiClientes);
    }else{
        printf("\n ERROR DE APERTURA DE ARCHIVO ");
    }
}
///--------------------- Cargar archivo Clientes ---------------------

///--------------------- Retorna el ultimo ID del archivo Clientes ---------------------
int pasarUltimoIdClientes(const char archivo[]){
    stCliente a;
    int id = 0;
    FILE *archi = fopen(archivo,"rb");

    if(archi){
            fseek(archi,sizeof(stCliente) * -1,SEEK_END);
            if(fread(&a,sizeof(stCliente),1,archi) > 0){
                id = a.id;
            }
        fclose(archi);
    }
    return id;
}
///--------------------- Retorna el ultimo ID del archivo Clientes ---------------------



///--------------------- Muestra todo el archivo Clientes ---------------------
void muestraArchivoClientes(const char archivo[]){
    stCliente a;
    FILE *pArchiClientes = fopen(archivo, "rb");

    if(pArchiClientes != NULL){
        while(fread(&a, sizeof(stCliente), 1, pArchiClientes) > 0){
            if(a.baja == 0){
                muestraUnCliente(a);
                printf("\n\n----------------------------------------------\n");
            }
        }
        fclose(pArchiClientes);
    }else{
        printf("\n ERROR DE APERTURA DE ARCHIVO ");
    }
}
///--------------------- Muestra todo el archivo Clientes ---------------------


///--------------------- Carga aleatoria de clientes ---------------------
int agregarClientesAleatorios(const char archivo_clientes[], int cantidadClientes){
    srand(time(NULL));

    stCliente cliente;

    int flag = 0;
    int i = 0;

    int idCliente = pasarUltimoIdClientes(archivo_clientes) + 1;

    FILE* archiClientes = fopen(archivo_clientes,"a+b");

    if(archiClientes){
        while(i < cantidadClientes){
            cliente.id = idCliente;
            cliente.nroCliente = idCliente;
            strcpy(cliente.nombre,getNombre());
            strcpy(cliente.apellido,getApellido());
            strcpy(cliente.dni,getDni());
            strcpy(cliente.email,getEmail());
            strcpy(cliente.domicilio,getDomicilio());
            strcpy(cliente.movil,getMovil());
            cliente.baja = 0;

            fwrite(&cliente,sizeof(stCliente),1,archiClientes);

            muestraUnCliente(cliente);
            printf("\n\n----------------------------------------------\n");

            i++;
            idCliente++;
            flag++;
        }
        fclose(archiClientes);
    }
    return flag;
}
///--------------------- Carga aleatoria de clientes ---------------------

///--------------------- Obtine datos al azar ---------------------
char *getNombre(){
    char nombres[100][30];
    char *n = (char *)malloc(sizeof(char)*30);
    int vNombres = 0;

    vNombres = csvArreglo(30,"csv/nombres.csv",nombres,100);

    strcpy(n,nombres[rand()%vNombres]);

    return n;
}

char *getApellido(){
    char apellidos[100][30];
    char *a = (char *)malloc(sizeof(char)*30);
    int vApellidos = 0;

    vApellidos = csvArreglo(30,"csv/apellidos.csv",apellidos,100);

    strcpy(a,apellidos[rand()%vApellidos]);

    return a;
}

char *getDni(){
    char *dni = (char *)malloc(sizeof(char)*10);
    char caracter[1];
    int num;

    strcpy(dni,"");

    for(int i = 0;i < 8;i++){
        num = rand()%10;
        itoa(num,caracter,10);
        strcat(dni,caracter);
    }
    return dni;
}

char *getEmail(){
    char email[100][30];
    char *e = (char *)malloc(sizeof(char)*30);
    int vEmail = 0;

    vEmail = csvArreglo(30,"csv/email.csv",email,100);

    strcpy(e,email[rand()%vEmail]);

    return e;
}

char *getDomicilio(){
    char calles[100][30];
    char *domicilio = (char *)malloc(sizeof(char)*30);
    char caracter[1];
    int vCalle = 0;
    int num;

    vCalle = csvArreglo(30,"csv/calles.csv",calles,100);

    strcpy(domicilio,"");

    strcat(domicilio,calles[rand()%vCalle]);
    strcat(domicilio," ");
    strcat(domicilio,calles[rand()%vCalle]);
    strcat(domicilio," ");

    for(int i = 0;i < 4;i++){
        num = rand()%10;
        itoa(num,caracter,10);
        strcat(domicilio,caracter);
    }

    return domicilio;
}

char *getMovil(){
    char *movil = (char *)malloc(sizeof(char)*30);
    char caracter[1];
    int num;

    strcpy(movil,"");
    strcat(movil,"2235");

    for(int i = 0;i < 6;i++){
        num = rand()%10;
        itoa(num,caracter,10);
        strcat(movil,caracter);
    }

    return movil;
}

int csvArreglo(int col,char archivo[],char n[][col],int dim){
    FILE * archi = fopen(archivo,"r");
    int i = 0;

    if(archi){
        while(fscanf(archi,"%s",n[i]) == 1){
            i++;
        }
        fclose(archi);
    }
    return i;
}
///--------------------- Obtine un nombre al azar ---------------------
