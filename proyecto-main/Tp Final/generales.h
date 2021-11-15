#ifndef GENERALES_H_INCLUDED
#define GENERALES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

///--------------------- Contar registros ---------------------
int contarRegistros(const char archivo[], int tam);


///---------------------- Retornar Fecha ----------------------
void fecha(char date[]);


///--------------------- Valida Cadena de Letras ----------------------
int validarCadenaLetras(char cadena[]);


///--------------------- Valida Cadena de Números ---------------------
int validarCadenaNumeros(char cadena[]);


///---------------------- Devuelve el anio, mes, dia en variables enteras ----------------------
void devolverFechaHoy(int *anioHoy, int *mesHoy, int *diaHoy);

///---------------------- Presentacion del Sistema y Grupo ----------------------
void loader();


#endif // GENERALES_H_INCLUDED
