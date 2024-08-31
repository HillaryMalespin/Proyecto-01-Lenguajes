#ifndef PROCESAR_H
#define PROCESAR_H

#include "venta.h"

// Función para completar los datos faltantes en el arreglo de ventas.
void completar_datos_faltantes(Venta *ventas, int total_ventas);

// Función para eliminar registros duplicados en el arreglo de ventas.
void eliminar_duplicados(Venta *ventas, int *total_ventas);

#endif
