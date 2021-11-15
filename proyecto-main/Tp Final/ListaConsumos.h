#ifndef LISTACONSUMOS_H_INCLUDED
#define LISTACONSUMOS_H_INCLUDED

#include "consumo.h"

typedef struct _nodoLista{
	stConsumos dato;
	struct _nodoLista* sig;
}nodoLista;


nodoLista* inicLista();

nodoLista* crearNodo(stConsumos dato);

nodoLista* agregarAlPrincipio(nodoLista* lista,nodoLista* nuevo);

void muestraLista(nodoLista* lista);
void muestraNodo(nodoLista* nodo);

#endif // LISTACONSUMOS_H_INCLUDED
