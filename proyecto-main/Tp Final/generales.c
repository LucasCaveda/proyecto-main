#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#include "generales.h"
#include "gotoxy.h"

///--------------------- Contar registros ---------------------
//Devuelve la cantidad de registros que contiene un archivo
int contarRegistros(const char archivo[], int tam){
    int cant = 0;
    FILE *archi = fopen(archivo,"rb");

    if(archi)
    {
        fseek(archi,0,SEEK_END);
        cant = ftell(archi) / tam;

        fclose(archi);
    }
    return cant;
}
///--------------------- Contar registros ---------------------


///---------------------- Retornar Fecha ----------------------
//Devuelve la fecha en un String (Año-Mes-Dia)
void fecha(char date[]){
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    strftime(date,128,"%Y-%m-%d",tlocal);
}
///---------------------- Retornar Fecha ----------------------



///--------------------- Valida Cadena de Letras ----------------------
//  Valida que la cadena contenga solo letras. Funciona con la libreria Ctype.
int validarCadenaLetras(char cadena[]){
    int validar = 0;
    int l = strlen(cadena);

    for(int i = 0; i < l && validar == 0; i++)
    {
        //  Usa la funcion "isalpha" de la libreria "Ctype.h" para verificar si lo que ingresa es una letra.
        if(!isalpha(cadena[i]))
        {
            validar = 1;
        }
    }

    return validar;
}
///--------------------- Valida Cadena de Letras ----------------------



///--------------------- Valida Cadena de Números ---------------------
//  Valida si una cadena tiene solo numeros.
int validarCadenaNumeros(char cadena[]){
    int validar = 0;
    int l = strlen(cadena);

    for(int i = 0; i < l && validar == 0; i++)
    {
        //  Usa la funcion "isdigit" de la libreria "Ctype.h" para verificar si lo que ingresa es una letra.
        if(!isdigit(cadena[i]))
        {
            validar = 1;
        }
    }

    return validar;
}
///--------------------- Valida Cadena de Números ---------------------



///---------------------- Devuelve el anio, mes, dia en variables enteras ----------------------
void devolverFechaHoy(int *anioHoy, int *mesHoy, int *diaHoy){
    char anio[10];
    char mes[10];
    char dia[10];

    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    strftime(anio,128,"%Y",tlocal);
    strftime(mes,128,"%m",tlocal);
    strftime(dia,128,"%d",tlocal);

    *anioHoy = atoi(anio);
    *mesHoy = atoi(mes);
    *diaHoy = atoi(dia);
}
///---------------------- Devuelve el anio, mes, dia en variables enteras ----------------------

/// ---------------------- Presentacion del Sistema y Grupo ------------------------------------

void loader(void){
    system("cls");
    char d[25]="| Bienvenido |";
    int j;

    // Hace un ciclo de repeticion para simular una carga y que el usuario reconozca el inicio del programa.
    // Con este espera la interacion del usuario para proseguir.

    gotoxy(10,4);
    for(j=0; j<20; j++)
    {
        Sleep(50);
        printf("*");
    }
    for(j=0; j<14; j++)
    {
        Sleep(50);
        printf("%c",d[j]);
    }
    for(j=0; j<20; j++)
    {
        Sleep(50);
        printf("*");
    }

    gotoxy(15,9);
    printf("* Sistema de Clientes y Consumos");
    gotoxy(15,11);
    printf("GRUPO: IGCAMA");
    gotoxy(15,12);
    printf("Dominguez - Tarchini - Carro");
}
/// ---------------------- Presentacion del Sistema y Grupo ------------------------------------
