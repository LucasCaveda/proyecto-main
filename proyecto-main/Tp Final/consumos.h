#ifndef CONSUMOS_H_INCLUDED
#define CONSUMOS_H_INCLUDED

///---------------------- Cargar archivo Consumos ----------------------
void cargaArchivoConsumos(const char archivo[],const char nombreArchivoClientes[]);

///--------------------- Retorna el ultimo ID del archivo Consumos ---------------------
int pasarUltimoIdConsumo(const char archivo[]);


///---------------------- Muestra archivo consumo ----------------------
void muestraArchivoConsumos(const char archivo[]);

///---------------------- Agregar Consumos Aleatorios ----------------------
int agregarConsumosAleatorios(const char archivo_clientes[],const  char archivo_consumos[], int cantidadConsumos);

#endif // CONSUMOS_H_INCLUDED
