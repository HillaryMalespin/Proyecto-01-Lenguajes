#include <stdio.h>
#include <stdlib.h>
#include "procesar.h"

// Función para calcular la media de un arreglo de enteros
double calcular_media(int *valores, int n) {
    double suma = 0.0;
    for (int i = 0; i < n; i++) {
        suma += valores[i];  // Sumar todos los valores
    }
    return suma / n;  // Devolver la media
}

// Función para calcular la media de un arreglo de números de punto flotante
double calcular_media_double(double *valores, int n) {
    double suma = 0.0;
    for (int i = 0; i < n; i++) {
        suma += valores[i];  // Sumar todos los valores
    }
    return suma / n;  // Devolver la media
}

// Función para completar los datos faltantes en el arreglo de ventas
void completar_datos_faltantes(Venta *ventas, int total_ventas) {
    // Reservar memoria para almacenar las cantidades y precios unitarios válidos
    int *cantidades = malloc(total_ventas * sizeof(int));
    double *precios_unitarios = malloc(total_ventas * sizeof(double));

    // Extraer las cantidades válidas para calcular la media
    int count = 0;
    for (int i = 0; i < total_ventas; i++) {
        if (ventas[i].cantidad > 0) {
            cantidades[count] = ventas[i].cantidad;
            count++;
        }
    }

    // Calcular la media de las cantidades
    double media_cantidad = calcular_media(cantidades, count);

    // Extraer los precios unitarios válidos para calcular la media
    count = 0;
    for (int i = 0; i < total_ventas; i++) {
        if (ventas[i].precio_unitario > 0) {
            precios_unitarios[count] = ventas[i].precio_unitario;
            count++;
        }
    }

    // Calcular la media de los precios unitarios
    double media_precio = calcular_media_double(precios_unitarios, count);

    // Rellenar los datos faltantes con las medias calculadas
    for (int i = 0; i < total_ventas; i++) {
        if (ventas[i].cantidad <= 0) {
            ventas[i].cantidad = (int)media_cantidad;
            printf("Registro %d (ID de Venta: %d) alterado: cantidad completada con la media (%d)\n", i + 1, ventas[i].venta_id, ventas[i].cantidad);
        }
        if (ventas[i].precio_unitario <= 0) {
            ventas[i].precio_unitario = media_precio;
            printf("Registro %d (ID de Venta: %d) alterado: precio_unitario completado con la media (%.2f)\n", i + 1, ventas[i].venta_id, ventas[i].precio_unitario);
        }
    }

    // Liberar la memoria reservada para las cantidades y precios unitarios
    free(cantidades);
    free(precios_unitarios);

    printf("Datos faltantes completados correctamente.\n");
}

// Función para eliminar registros duplicados en el arreglo de ventas
void eliminar_duplicados(Venta *ventas, int *total_ventas) {
    // Crear un arreglo para marcar los elementos duplicados
    int *marcado = calloc(*total_ventas, sizeof(int));

    // Buscar y marcar los registros duplicados
    for (int i = 0; i < *total_ventas; i++) {
        if (marcado[i]) continue;  // Si ya está marcado, omitir

        for (int j = i + 1; j < *total_ventas; j++) {
            if (ventas[i].venta_id == ventas[j].venta_id) {
                printf("Registro duplicado eliminado (ID de Venta: %d)\n", ventas[j].venta_id);
                marcado[j] = 1;  // Marcar el registro duplicado
            }
        }
    }

    // Reorganizar el arreglo para eliminar los elementos marcados
    int index = 0;
    for (int i = 0; i < *total_ventas; i++) {
        if (!marcado[i]) {
            ventas[index++] = ventas[i];  // Copiar los elementos no marcados
        }
    }

    *total_ventas = index;  // Actualizar el total de ventas
    free(marcado);  // Liberar la memoria reservada para el arreglo de marcado
}
