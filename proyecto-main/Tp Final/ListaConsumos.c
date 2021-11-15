#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ListaConsumos.h"

nodoLista* inicLista(){
    return NULL;
}

nodoLista* crearNodo(stConsumos dato){
    nodoLista* nuevo = (nodoLista *)malloc(sizeof(nodoLista));

    nuevo->dato = dato;
    nuevo->sig = NULL;

    return nuevo;
}

nodoLista* agregarAlPrincipio(nodoLista* lista,nodoLista* nuevo){
    nuevo->sig = lista;

    return nuevo;
}

void muestraLista(nodoLista* lista){
    if(lista){
        nodoLista* seg = lista;
        while(seg){
            muestraNodo(seg);
            printf("\n");
            seg = seg->sig;
        }
    }
}

void muestraNodo(nodoLista* nodo){
    muestraUnConsumo(nodo->dato);
}
