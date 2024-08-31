#ifndef GUARDAR_H
#define GUARDAR_H

#include "venta.h"  // Incluye el archivo de encabezado donde se define la estructura Venta

/**
 * Carga datos previos desde un archivo JSON y los almacena en un arreglo de ventas.
 * 
 * @param ruta Ruta del archivo JSON que contiene los datos previos.
 * @param ventas Puntero a un puntero de tipo `Venta` donde se almacenarán los datos cargados.
 * @param totalVentas Puntero a un entero donde se almacenará el total de ventas cargadas.
 */
void cargar_datos_previos(const char *ruta, Venta **ventas, int *totalVentas);

/**
 * Guarda los datos de ventas en un archivo JSON.
 * 
 * @param ruta Ruta del archivo JSON donde se guardarán los datos.
 * @param ventas Arreglo de ventas que se guardará en el archivo.
 * @param totalVentas Total de ventas que se deben guardar.
 */
void guardar_datos(const char *ruta, Venta *ventas, int totalVentas);

#endif
