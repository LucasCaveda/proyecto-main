#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include "gotoxy.h"

typedef struct{
    int id;
    int nroCliente;
    char nombre[30];
    char apellido[30];
    char dni[10];
    char email[30];
    char domicilio[30];
    char movil[30];
    int baja;
}stCliente;

///--------------------- Cargar un cliente ---------------------
void cargarUnCliente(stCliente *a, int id,FILE *archi);

///--------------------- Convertir a Minusculas ---------------------
void convertirNombreYApellido(char cadena[]);

///--------------------- Valida el email ---------------------
int validarEmail(char email[]);

///--------------------- Validar DNI ----------------------
int validarDni(FILE *archi,char dni[]);


///--------------------- Da de baja a un cliente ---------------------
int eliminarCliente(const char archivo[], int id);


///--------------------- Meunu de modificar cliente ---------------------
char menuModificar();

///--------------------- Modificar cliente ---------------------
void modificarCliente(const char archivo[], int id);

///--------------------- Modificar cliente ---------------------
void modificarCliente(const char archivo[], int id);


///--------------------- Menu de consultar Cliente ---------------------
char menuConsulta();


///--------------------- Consultar un Cliente ---------------------
void consultarUnCliente(const char archivo[], char opcion, char consulta[]);


///--------------------- Muestra un Clientes---------------------
void muestraUnCliente(stCliente a);

///---------------------- Recorrer Archivo de clientes ----------------------
stCliente recorrerArchivoClientes(const char nombreArchivoClientes[],int idCliente);

#endif // CLIENTE_H_INCLUDED
