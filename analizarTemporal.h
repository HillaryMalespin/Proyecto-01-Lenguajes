#ifndef ANALISIS_TEMPORAL_H
#define ANALISIS_TEMPORAL_H

/**
 * Estructura para almacenar el total de ventas por mes.
 */
typedef struct {
    int mes;                ///< Número del mes (1-12).
    double total_ventas;    ///< Total de ventas en el mes.
} MesVenta;

/**
 * Estructura para almacenar el total de transacciones por día de la semana.
 */
typedef struct {
    char dia_semana[10];    ///< Nombre del día de la semana (e.g., "Lunes").
    int total_transacciones; ///< Total de transacciones en el día de la semana.
} DiaSemana;

/**
 * Calcula el mes con mayor venta y el día de la semana más activo en función de las ventas.
 * 
 * @param ventas Array de estructuras Venta que contiene los datos de las ventas.
 * @param total_ventas Cantidad total de ventas en el array.
 * 
 * La función inicializa arrays para almacenar el total de ventas por mes y el total de transacciones 
 * por día de la semana. Recorre las ventas, extrae el mes y el día de la semana de cada venta, y acumula 
 * el total de ventas por mes y el total de transacciones por día de la semana. Luego, determina el mes 
 * con mayor venta y el día de la semana más activo, e imprime estos resultados.
 */
void mes_con_mayor_venta_y_dia_mas_activo(Venta *ventas, int total_ventas);

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
void calcular_tasa_crecimiento_trimestre(Venta *ventas, int total_ventas, int trimestre);

#endif
