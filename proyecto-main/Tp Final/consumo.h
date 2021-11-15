#ifndef CONSUMO_H_INCLUDED
#define CONSUMO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include "gotoxy.h"

typedef struct{
    int id;
    int idCliente;
    int anio;
    int mes;
    int dia;
    int datosConsumidos;
    int baja;
}stConsumos;

///---------------------- Cargar un Consumo ----------------------
void cargarUnConsumo(stConsumos *a, int id,const  char nombreArchivoClientes[]);

///---------------------- Validar IdCliente ----------------------
int validarCliente(int idCliente,const char nombreArchivoClientes[]);

///---------------------- Validar dia ----------------------
int validarDia(int dia, int mes,int anio);


///---------------------- Agrega los datos consumidos a otro consumo ----------------------
void agregarConsumoPorFecha(const char archivo[],int id,int datosConsumidos);


///---------------------- Da de baja un consumo ----------------------
int eliminarConsumo(const char archivo[], int id);


///---------------------- Menu modificar un consumo ----------------------
char menuModificarConsumo();

///---------------------- Modifica un Consumo ----------------------
void modificarConsumo(const char archivo[], int id,const char nombreArchivoClientes[]);


///---------------------- Menu de consultar Consumo ---------------------
char menuConsultaConsumo();

///---------------------- Consultar un Consumo ---------------------
void consultarUnConsumo(const char archivo[], char opcion, int consulta);


///--------------------- Menu de Buscar consumo por fecha ---------------------
stConsumos menuBuscarConsumoFecha(const char archivo[]);


///--------------------- Buscar consumo por fecha ---------------------
stConsumos buscarConsumoFecha(FILE *archi,int anio, int mes, int dia);


///---------------------- Muestra un consumo ----------------------
void muestraUnConsumo(stConsumos a);

#endif // CONSUMO_H_INCLUDED
