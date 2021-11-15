#ifndef ARBOLCLIENTE_H_INCLUDED
#define ARBOLCLIENTE_H_INCLUDED

#include "cliente.h"
#include "ListaConsumos.h"

typedef struct _nodoArbol{
	stCliente dato;
	nodoLista* consumos;
	struct _nodoArbol* izq;
	struct _nodoArbol* der;
}nodoArbol;

///---------------------- Recorrer Archivo de consumos y crea un arbol de Clientes ----------------------
nodoArbol* crearArbolClientes(const char nombreArchivoConsumos[],const char nombreArchivoClientes[]);

nodoArbol* crearNodoArbol(stCliente dato);

nodoArbol* agregarAlFinalArbol(nodoArbol* arbol,nodoArbol* nuevo);

nodoArbol* alta(nodoArbol* arbol,stCliente cliente,stConsumos consumo);

nodoArbol* buscaCliente(nodoArbol* arbol,int idCliente);

void muestraArbol(nodoArbol* arbol);
void muestraUnNodoArbol(nodoArbol* arbol);

void mostrarConsumoClientePorMes(nodoArbol* arbol, int mes);
void liquidarUnMes(nodoArbol* arbol, int idCliente, int mes);

nodoArbol* borrarNodo(nodoArbol* arbol, int id);
nodoArbol* NMD(nodoArbol* arbol);
nodoArbol* NMI(nodoArbol* arbol);

#endif // ARBOLCLIENTE_H_INCLUDED
