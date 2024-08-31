#ifndef IMPORTAR_H
#define IMPORTAR_H

#include "venta.h"  // Incluye el archivo de encabezado con la definición de la estructura Venta

/**
 * Función: importar_datos
 * Descripción: Carga los datos de ventas desde un archivo JSON y los almacena en un arreglo de ventas.
 * Parámetros:
 *   - const char *ruta_archivo: Ruta del archivo JSON que contiene los datos.
 *   - Venta **ventas: Puntero a un puntero de tipo `Venta` donde se almacenarán los datos cargados.
 *   - int *total_ventas: Puntero a un entero donde se almacenará el total de ventas cargadas.
 */
void importar_datos(const char *ruta_archivo, Venta **ventas, int *total_ventas);

/**
 * Función: contar_objetos_json
 * Descripción: Cuenta la cantidad de objetos en un archivo JSON y retorna el total.
 * Parámetros:
 *   - const char *ruta_archivo: Ruta del archivo JSON del cual contar los objetos.
 * Retorno: La cantidad de objetos en el archivo JSON, o -1 en caso de error.
 */
int contar_objetos_json(const char *ruta_archivo);

#endif
