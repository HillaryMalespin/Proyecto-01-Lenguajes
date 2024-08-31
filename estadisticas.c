#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "venta.h"
#include "estadisticas.h"

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
void mostrar_top_5_categorias(Venta *ventas, int total_ventas, EstadisticaCategoria *categorias) {
    EstadisticaCategoria categoriasLocal[50];
    int num_categorias = 0;

    // Recorre las ventas y acumula el total de ventas para cada categoría
    for (int i = 0; i < total_ventas; i++) {
        int j;
        for (j = 0; j < num_categorias; j++) {
            if (strcmp(categoriasLocal[j].categoria, ventas[i].categoria) == 0) {
                categoriasLocal[j].total_ventas += ventas[i].total;
                break;
            }
        }
        if (j == num_categorias) {
            strcpy(categoriasLocal[num_categorias].categoria, ventas[i].categoria);
            categoriasLocal[num_categorias].total_ventas = ventas[i].total;
            num_categorias++;
        }
    }

    // Ordena las categorías por total de ventas en orden descendente
    for (int i = 0; i < num_categorias - 1; i++) {
        for (int j = i + 1; j < num_categorias; j++) {
            if (categoriasLocal[j].total_ventas > categoriasLocal[i].total_ventas) {
                EstadisticaCategoria temp = categoriasLocal[i];
                categoriasLocal[i] = categoriasLocal[j];
                categoriasLocal[j] = temp;
            }
        }
    }

    // Muestra las 5 primeras categorías y copia los resultados al arreglo de salida
    printf("\nTop 5 Categorías con Mayores Ventas:\n");
    for (int i = 0; i < 5 && i < num_categorias; i++) {
        printf("%d. %s - Total Ventas: %.2f\n", i + 1, categoriasLocal[i].categoria, categoriasLocal[i].total_ventas);
        strcpy(categorias[i].categoria, categoriasLocal[i].categoria);
        categorias[i].total_ventas = categoriasLocal[i].total_ventas;
    }
}
