#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ArbolCliente.h"
#include "ListaConsumos.h"
#include "cliente.h"

///---------------------- Recorrer Archivo de consumos y crea un arbol de Clientes ----------------------
nodoArbol* crearArbolClientes(const char nombreArchivoConsumos[],const char nombreArchivoClientes[]){
    stConsumos consumo;
    stCliente cliente;
    nodoArbol* arbol = NULL;
    FILE* archi = fopen(nombreArchivoConsumos,"rb");

    if(archi){
        while(fread(&consumo,sizeof(stConsumos),1,archi) > 0){
            cliente = recorrerArchivoClientes(nombreArchivoClientes,consumo.idCliente);

            arbol = alta(arbol,cliente,consumo);
        }
        fclose(archi);
    }
    return arbol;
}
///---------------------- Recorrer Archivo de consumos y crea un arbol de Clientes ----------------------


nodoArbol* crearNodoArbol(stCliente dato){
    nodoArbol* nuevo = (nodoArbol*)malloc(sizeof(nodoArbol));

    nuevo->dato = dato;
    nuevo->consumos = NULL;
    nuevo->izq = NULL;
    nuevo->der = NULL;

    return nuevo;
}

nodoArbol* agregarAlFinalArbol(nodoArbol* arbol,nodoArbol* nuevo){
    if(!arbol){
        arbol = nuevo;
    }else{
        if(nuevo->dato.id != arbol->dato.id){
            if(nuevo->dato.id < arbol->dato.id){
                arbol->izq = agregarAlFinalArbol(arbol->izq,nuevo);
            }else{
                arbol->der = agregarAlFinalArbol(arbol->der,nuevo);
            }
        }
    }
    return arbol;
}

nodoArbol* alta(nodoArbol* arbol,stCliente cliente,stConsumos consumo){
    nodoLista* aux = crearNodo(consumo);
    nodoArbol* pos = buscaCliente(arbol,cliente.id);

    if(!pos){
        arbol = agregarAlFinalArbol(arbol,crearNodoArbol(cliente));
        pos = buscaCliente(arbol,cliente.id);
    }
    if(!pos->consumos){
        pos->consumos = inicLista();
    }
    pos->consumos = agregarAlPrincipio(pos->consumos,aux);
    return arbol;
}

nodoArbol* buscaCliente(nodoArbol* arbol,int idCliente){
    nodoArbol* rta = NULL;
    if(arbol){
        if(arbol->dato.id == idCliente){
            rta = arbol;
        }else{
            if(idCliente < arbol->dato.id){
                rta = buscaCliente(arbol->izq,idCliente);
            }else{
                rta = buscaCliente(arbol->der,idCliente);
            }
        }
    }
    return rta;
}

void muestraArbol(nodoArbol* arbol){
    if(arbol){
        muestraUnNodoArbol(arbol);
        muestraArbol(arbol->izq);
        muestraArbol(arbol->der);
    }
}

void muestraUnNodoArbol(nodoArbol* arbol){
    printf("\n\tCliente Nro: %d \n",arbol->dato.nroCliente);
    muestraUnCliente(arbol->dato);
    if(arbol->consumos){
        printf("\n\n\n\tConsumos del Cliente Nro %d: \n",arbol->dato.nroCliente);
        muestraLista(arbol->consumos);
        printf("\n\n------------------------------------------------------------------\n\n");
    }
}

/// Funciones de borrar nodo

nodoArbol* NMD(nodoArbol* arbol){
    if(arbol->der != NULL){
        arbol=NMD(arbol->der);
    }else{
    return arbol;
    }
}

nodoArbol* NMI(nodoArbol* arbol){
    if(arbol->izq != NULL){
        arbol=NMD(arbol->izq);
    }else{
    return arbol;
    }
}

nodoArbol* borrarNodo(nodoArbol* arbol, int id){
    if(arbol){
        if(id == arbol->dato.id){
            if(arbol->izq){
                nodoArbol* masDer = NMD(arbol->izq);
                arbol->dato = masDer->dato;
                arbol->izq = borrarNodo(arbol->izq, masDer->dato.id);
            }else{
                if(arbol->der){
                    nodoArbol* masIzq = NMI(arbol->der);
                    arbol->dato = masIzq->dato;
                    arbol->der = borrarNodo(arbol->izq, masIzq->dato.id);
                }else{
                free(arbol);
                arbol=NULL;
                }
            }
        }
        if(id > arbol->dato.id){
            arbol->der=borrarNodo(arbol->der,id);
        }
        if(id < arbol->dato.id){
            arbol->izq=borrarNodo(arbol->izq,id);
        }
    }
    return arbol;
}


/// Muestra consumos en un mes especifico de un cliente especifico

void mostrarConsumoClientePorMes(nodoArbol* arbol, int mes){
    nodoLista* seg = arbol->consumos;

    while(seg->sig != NULL){
        if(arbol->consumos->dato.mes == mes){
            muestraUnConsumo(arbol->consumos->dato);
        }
        seg=seg->sig;
    }
}


void liquidarUnMes(nodoArbol* arbol, int idCliente, int mes){

    if(buscaNodoArbol(arbol,idCliente)!=NULL){
        printf("\nMostrando los consumos del cliente %c %c en el mes %d:\n\n\n", arbol->dato.nombre, arbol->dato.apellido, mes);
        mostrarConsumoCliente(buscaNodoArbol(arbol,idCliente),mes);
    }else{
        printf("\nId no encontrado.");
    }
}
