#include "cliente.h"
#include "consumo.h"
#include "consumos.h"
#include "generales.h"

///---------------------- Cargar archivo Consumos ----------------------
void cargaArchivoConsumos(const char archivo[],const char nombreArchivoClientes[]){
    stConsumos consumoFecha;
    char opcion;
    int id = pasarUltimoIdConsumo(archivo) + 1;

    stConsumos a;

    FILE *archi = fopen(archivo,"a+b");
    if(archi){
        do{
            printf("\n\n");

            cargarUnConsumo(&a,id,nombreArchivoClientes);

            consumoFecha = buscarConsumoFecha(archi,a.anio,a.mes,a.dia);
            fseek(archi,sizeof(stConsumos)*-1,SEEK_END);

            if(consumoFecha.id != -1){
                agregarConsumoPorFecha(archivo,consumoFecha.id,a.datosConsumidos);
                printf("\n\n\tSe encontro otro consumo con la misma fecha\n\ty se sumaron los datos consumidos.");
            }else{
                fwrite(&a,sizeof(stConsumos),1,archi);
                fclose(archi);
                archi = fopen(archivo,"a+b");
                id++;
            }

            printf("\n\n\t ESC para salir - cualquier tecla para continuar");
            opcion = getch();
            system("cls");
        }while(opcion != 27 && archi != NULL);
        fclose(archi);
    }
}
///---------------------- Cargar archivo Clientes ----------------------

///--------------------- Retorna el ultimo ID del archivo Consumos ---------------------
int pasarUltimoIdConsumo(const char archivo[]){
    stConsumos a;
    int id = 0;
    FILE *archi = fopen(archivo,"rb");

    if(archi){
            fseek(archi,sizeof(stConsumos) * -1,SEEK_END);
            if(fread(&a,sizeof(stConsumos),1,archi) > 0){
                id = a.id;
            }
        fclose(archi);
    }
    return id;
}
///--------------------- Retorna el ultimo ID del archivo Consumos ---------------------



///---------------------- Muestra archivo consumo ----------------------
void muestraArchivoConsumos(const char archivo[]){
    stConsumos a;

    FILE *archi = fopen(archivo,"rb");

    if(archi){
        while(fread(&a,sizeof(stConsumos),1,archi) > 0){
            if(a.baja == 0){
                muestraUnConsumo(a);
                printf("\n\n----------------------------------------------\n");
            }
        }
        fclose(archi);
    }
}
///---------------------- Muestra archivo consumo ----------------------


///---------------------- Agregar Consumos Aleatorios ----------------------
int agregarConsumosAleatorios(const char archivo_clientes[],const  char archivo_consumos[], int cantidadConsumos){
    srand(time(NULL));

    stCliente cliente;
    stConsumos a;
    stConsumos consumoFecha;

    int flag = 0;
    int validar = 0;
    int i = 0;

    int tamanioClientes = contarRegistros(archivo_clientes,sizeof(stCliente));
    int idRandom = 0;
    int idConsumo = pasarUltimoIdConsumo(archivo_consumos) + 1;

    int anioHoy;
    int mesHoy;
    int diaHoy;

    FILE *archiClientes = fopen(archivo_clientes,"rb");
    FILE *archiConsumos = fopen(archivo_consumos,"a+b");

    if(archiClientes){
        if(archiConsumos){
                devolverFechaHoy(&anioHoy,&mesHoy,&diaHoy);

                while(i < cantidadConsumos){
                    idRandom = rand() % tamanioClientes;
                    fseek(archiClientes,sizeof(stCliente)*idRandom,SEEK_SET);
                    if(fread(&cliente,sizeof(stCliente),1,archiClientes)){
                        if(cliente.baja == 0){
                            a.id = idConsumo;
                            a.idCliente = cliente.id;
                            a.anio =  anioHoy;
                            a.mes = (rand() % mesHoy) + 1;
                            do{
                                a.dia = (rand() % 31) + 1;

                                if(a.mes == mesHoy && a.dia > diaHoy){
                                    validar = 0;
                                }else{
                                    validar = validarDia(a.dia,a.mes,a.anio);
                                }
                            }while(validar == 0);
                            a.datosConsumidos = rand() % 10000;
                            a.baja = 0;


                            consumoFecha = buscarConsumoFecha(archiConsumos,a.anio,a.mes,a.dia);

                            if(consumoFecha.id != -1){
                                agregarConsumoPorFecha(archivo_consumos,consumoFecha.id,a.datosConsumidos);
                                printf("\n\nConsumo con fecha repetida, se le sumaran los datos consumidos al otro consumo.");
                            }else{
                                fwrite(&a,sizeof(stConsumos),1,archiConsumos);
                                idConsumo++;
                                fclose(archiConsumos);
                                archiConsumos = fopen(archivo_consumos,"a+b");
                            }

                            muestraUnConsumo(a);
                            printf("\n\n----------------------------------------------\n");

                            i++;
                            flag++;
                        }
                    }else{
                        i = cantidadConsumos + 1;
                    }
                }


            fclose(archiConsumos);
        }
        fclose(archiClientes);
    }

    return flag;
}
///---------------------- Agregar Consumos Aleatorios ----------------------
