#include <stdio.h>
#include "venta.h"
#include "analizar.h"

/**
 * Calcula el total de ventas sumando los importes de todas las ventas.
 * 
 * @param ventas Array de estructuras Venta con los datos de las ventas.
 * @param total_ventas Cantidad total de ventas en el array.
 * @return La suma total de las ventas.
 * 
 * La función recorre el array de ventas y acumula el total de cada venta en una variable
 * `suma_total`, que luego se retorna como el resultado total de ventas.
 */
double calcular_total_ventas(Venta *ventas, int total_ventas) {
    double suma_total = 0.0; // Inicializa la variable para la suma total
    for (int i = 0; i < total_ventas; i++) { // Recorre todas las ventas
        suma_total += ventas[i].total; // Suma el total de cada venta
    }
    return suma_total; // Retorna la suma total de ventas
}

/**
 * Calcula y muestra el total de ventas por cada mes.
 * 
 * @param ventas Array de estructuras Venta con los datos de las ventas.
 * @param total_ventas Cantidad total de ventas en el array.
 * 
 * La función inicializa un array para almacenar las ventas mensuales, recorre las ventas,
 * extrae el mes de la fecha de cada venta y acumula el total de ventas en el mes correspondiente.
 * Luego imprime las ventas totales por cada mes.
 */
void calcular_total_ventas_mensuales(Venta *ventas, int total_ventas) {
    double ventas_mensuales[12] = {0.0};  // Array para almacenar las ventas de cada mes
    for (int i = 0; i < total_ventas; i++) { // Recorre todas las ventas
        int mes;
        sscanf(ventas[i].fecha, "%*d-%d-%*d", &mes);  // Extrae el mes de la fecha
        ventas_mensuales[mes - 1] += ventas[i].total; // Acumula el total de ventas del mes
    }

    printf("Ventas mensuales:\n"); // Imprime el encabezado
    for (int i = 0; i < 12; i++) { // Recorre los meses
        printf("Mes %d: %.2f\n", i + 1, ventas_mensuales[i]); // Imprime el total de ventas del mes
    }
}

/**
 * Calcula y muestra el total de ventas por cada año.
 * 
 * @param ventas Array de estructuras Venta con los datos de las ventas.
 * @param total_ventas Cantidad total de ventas en el array.
 * 
 * La función inicializa arrays para almacenar las ventas anuales y los años correspondientes.
 * Recorre las ventas, extrae el año de la fecha de cada venta y acumula el total de ventas en el
 * año correspondiente. Luego imprime las ventas totales por cada año.
 */
void calcular_total_ventas_anuales(Venta *ventas, int total_ventas) {
    double ventas_anuales[10] = {0.0};  // Array para almacenar las ventas de cada año
    int anos[10] = {0};  // Array para almacenar los años correspondientes
    int num_anos = 0;    // Contador de años únicos

    for (int i = 0; i < total_ventas; i++) { // Recorre todas las ventas
        int ano;
        sscanf(ventas[i].fecha, "%d-%*d-%*d", &ano);  // Extrae el año de la fecha

        int j;
        for (j = 0; j < num_anos; j++) { // Busca si el año ya está en el array
            if (anos[j] == ano) {
                ventas_anuales[j] += ventas[i].total; // Acumula el total de ventas del año
                break;
            }
        }

        if (j == num_anos) { // Si el año no está en el array
            anos[num_anos] = ano; // Añade el año al array
            ventas_anuales[num_anos] += ventas[i].total; // Acumula el total de ventas del año
            num_anos++; // Incrementa el contador de años únicos
        }
    }

    printf("Ventas anuales:\n"); // Imprime el encabezado
    for (int i = 0; i < num_anos; i++) { // Recorre los años únicos
        printf("Año %d: %.2f\n", anos[i], ventas_anuales[i]); // Imprime el total de ventas del año
    }
}
