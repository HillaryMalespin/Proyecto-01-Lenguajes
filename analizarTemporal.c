#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "venta.h"
#include "analizarTemporal.h"

/**
 * Calcula el mes con mayor venta y el día de la semana más activo en función de las ventas.
 * 
 * @param ventas Puntero al array de estructuras Venta que contiene los datos de las ventas.
 * @param total_ventas Cantidad total de ventas en el array.
 * 
 * La función inicializa arrays para almacenar el total de ventas por mes y el total de transacciones 
 * por día de la semana. Recorre las ventas, extrae el mes y el día de la semana de cada venta, y acumula 
 * el total de ventas por mes y el total de transacciones por día de la semana. Luego, determina el mes 
 * con mayor venta y el día de la semana más activo, e imprime estos resultados.
 */
void mes_con_mayor_venta_y_dia_mas_activo(Venta *ventas, int total_ventas) {
    MesVenta ventas_mensuales[12] = {0};  // Array para almacenar el total de ventas por mes
    DiaSemana dias_semana[7] = {0};       // Array para almacenar el total de transacciones por día de la semana

    const char *nombres_dias[] = {"Domingo", "Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado"};
    
    for (int i = 0; i < 7; i++) {
        strcpy(dias_semana[i].dia_semana, nombres_dias[i]); // Inicializa los nombres de los días de la semana
        dias_semana[i].total_transacciones = 0; // Inicializa el total de transacciones por día de la semana
    }

    for (int i = 0; i < total_ventas; i++) {
        int mes;
        int dia_semana;

        sscanf(ventas[i].fecha, "%*d-%d-%*d", &mes);  // Extrae el mes de la fecha de la venta
        sscanf(ventas[i].fecha, "%*d-%*d-%d", &dia_semana);  // Extrae el día de la semana (1 = lunes, ..., 7 = domingo)
        
        ventas_mensuales[mes - 1].mes = mes; // Almacena el mes en el array
        ventas_mensuales[mes - 1].total_ventas += ventas[i].total; // Acumula el total de ventas del mes

        // Suponiendo que la función `sscanf` obtiene un día de la semana válido
        dias_semana[dia_semana % 7].total_transacciones += 1; // Acumula el total de transacciones del día de la semana
    }

    int mes_mayor_venta = 0;
    double max_ventas = 0.0;
    for (int i = 0; i < 12; i++) {
        if (ventas_mensuales[i].total_ventas > max_ventas) { // Encuentra el mes con el mayor total de ventas
            max_ventas = ventas_mensuales[i].total_ventas;
            mes_mayor_venta = i + 1;
        }
    }

    int dia_mas_activo = 0;
    int max_transacciones = 0;
    for (int i = 0; i < 7; i++) {
        if (dias_semana[i].total_transacciones > max_transacciones) { // Encuentra el día de la semana con el mayor número de transacciones
            max_transacciones = dias_semana[i].total_transacciones;
            dia_mas_activo = i;
        }
    }

    printf("Mes con mayor venta: %d con un total de %.2f en ventas.\n", mes_mayor_venta, max_ventas);
    printf("Día de la semana más activo: %s con un total de %d transacciones.\n", dias_semana[dia_mas_activo].dia_semana, max_transacciones);
}

/**
 * Calcula y muestra la tasa de crecimiento de las ventas entre dos trimestres.
 * 
 * @param ventas Array de estructuras Venta que contiene los datos de las ventas.
 * @param total_ventas Cantidad total de ventas en el array.
 * @param trimestre El trimestre para el cual se desea calcular la tasa de crecimiento (1-4).
 * 
 * La función calcula las ventas para el trimestre actual y el trimestre anterior. Luego, calcula
 * la tasa de crecimiento comparando las ventas del trimestre actual con las del trimestre anterior
 * y muestra el resultado en porcentaje. Si no hay datos suficientes para calcular la tasa de crecimiento,
 * se muestra un mensaje de advertencia.
 */
void calcular_tasa_crecimiento_trimestre(Venta *ventas, int total_ventas, int trimestre) {
    double ventas_trimestre_actual = 0.0;
    double ventas_trimestre_anterior = 0.0;

    for (int i = 0; i < total_ventas; i++) {
        int mes;
        sscanf(ventas[i].fecha, "%*d-%d-%*d", &mes);  // Extrae el mes de la fecha de la venta

        // Determina si el mes pertenece al trimestre actual o al trimestre anterior
        if ((mes - 1) / 3 + 1 == trimestre) {
            ventas_trimestre_actual += ventas[i].total; // Acumula las ventas del trimestre actual
        } else if ((mes - 1) / 3 + 1 == trimestre - 1) {
            ventas_trimestre_anterior += ventas[i].total; // Acumula las ventas del trimestre anterior
        }
    }

    if (ventas_trimestre_anterior > 0) { // Verifica si hay datos suficientes para calcular la tasa de crecimiento
        double tasa_crecimiento = ((ventas_trimestre_actual - ventas_trimestre_anterior) / ventas_trimestre_anterior) * 100;
        printf("Tasa de crecimiento para el trimestre %d: %.2f%%\n", trimestre, tasa_crecimiento);
    } else {
        printf("No hay suficientes datos para calcular la tasa de crecimiento para el trimestre %d.\n", trimestre);
    }
}
