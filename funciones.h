// funciones.h
#ifndef FUNCIONES_H
#define FUNCIONES_H

/**
 * Importa datos desde un archivo o fuente externa.
 * 
 * Esta función se encarga de cargar datos necesarios para el sistema desde una fuente externa.
 */
void importarDatos();

/**
 * Procesa los datos importados para prepararlos para el análisis.
 * 
 * Esta función realiza operaciones de limpieza, validación y transformación de datos.
 */
void procesarDatos();

/**
 * Analiza los datos para obtener información relevante.
 * 
 * Esta función ejecuta análisis sobre los datos procesados, generando resultados que pueden ser utilizados para informes.
 */
void analizarDatos();

/**
 * Realiza un análisis temporal sobre los datos.
 * 
 * Esta función se centra en analizar los datos en función de aspectos temporales, como fechas y periodos de tiempo.
 */
void analizarTemporal();

/**
 * Muestra las estadísticas obtenidas del análisis de datos.
 * 
 * Esta función presenta las estadísticas calculadas de manera que sea fácil de interpretar por el usuario.
 */
void mostrarEstadisticas();

/**
 * Guarda los datos procesados o resultados del análisis en un archivo.
 * 
 * Esta función se encarga de almacenar los datos o resultados generados en un archivo para su persistencia y posterior uso.
 */
void guardarDatos();

#endif // FUNCIONES_H
