#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "generales.h"

///--------------------- Cargar archivo Clientes ---------------------
void cargaArchivoClientes(const char archivo[]);

///--------------------- Retorna el ultimo ID del archivo Clientes ---------------------
int pasarUltimoIdClientes(const char archivo[]);


///--------------------- Muestra todo el archivo Clientes ---------------------
void muestraArchivoClientes(const char archivo[]);


///--------------------- Carga aleatoria de clientes ---------------------
int agregarClientesAleatorios(const char archivo_clientes[], int cantidadClientes);

///--------------------- Obtine datos al azar ---------------------
char *getNombre();
char *getApellido();
char *getDni();
char *getEmail();
char *getDomicilio();
char *getMovil();

int csvArreglo(int col,char archivo[],char n[][col],int dim);

#endif // CLIENTES_H_INCLUDED
