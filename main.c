#include <stdio.h>
#include <stdlib.h>
#include "funciones.h" // funciones a implementar
#include "importar.h"
#include "venta.h"


int main() {
    int opcion;
    char rutaArchivo[256];  // Buffer para la ruta del archivo
    Venta *ventas = NULL;   // Puntero a la estructura de ventas
    int totalVentas = 0;    // Contador de ventas

    do {
        printf("\n===== Sistema de Análisis de Datos de Ventas =====\n");
        printf("1. Importar datos de ventas\n");
        printf("2. Procesar datos\n");
        printf("3. Analizar datos\n");
        printf("4. Análisis temporal\n");
        printf("5. Mostrar estadísticas\n");
        printf("6. Guardar datos\n");
        printf("7. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingrese la ruta del archivo JSON: ");
                scanf("%s", rutaArchivo);

                // Llamada a la función importar_datos
                importar_datos(rutaArchivo, &ventas, &totalVentas);

                printf("Datos importados correctamente. Total de ventas: %d\n", totalVentas);
                break;

            case 2:
                //procesarDatos();  // Función a implementar
                break;
            case 3:
                //analizarDatos();  // Función a implementar
                break;
            case 4:
                //analizarTemporal();  // Función a implementar
                break;
            case 5:
                //mostrarEstadisticas();  // Función a implementar
                break;
            case 6:
                //guardarDatos();  // Función a implementar
                break;
            case 7:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opción no válida. Intente de nuevo.\n");
        }
    } while (opcion != 7);

    // Liberar la memoria asignada a las ventas antes de salir
    free(ventas);

    return 0;
}
