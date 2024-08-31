#ifndef ESTADISTICAS_H
#define ESTADISTICAS_H

#include "venta.h"

/**
 * Estructura para almacenar las estadísticas de ventas por categoría.
 */
typedef struct {
    char categoria[50];    ///< Nombre de la categoría.
    double total_ventas;  ///< Total de ventas para la categoría.
} EstadisticaCategoria;

/**
 * Muestra las 5 categorías con mayores ventas y copia los resultados al arreglo de salida.
 * 
 * @param ventas Array de estructuras Venta que contiene los datos de las ventas.
 * @param total_ventas Cantidad total de ventas en el array.
 * @param categorias Array de estructuras EstadisticaCategoria donde se almacenarán los resultados.
 * 
 * La función recorre todas las ventas y acumula el total de ventas para cada categoría. Luego, ordena
 * las categorías por total de ventas en orden descendente y muestra las 5 categorías con mayores ventas.
 * Los resultados se copian al arreglo de salida proporcionado.
 */
void mostrar_top_5_categorias(Venta *ventas, int total_ventas, EstadisticaCategoria *categorias);

#endif
