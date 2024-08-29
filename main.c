#include <stdio.h>
#include <stdlib.h>
#include "funciones.h" // Funciones a implementar
#include "importar.h"
#include "venta.h"
#include "procesar.h"

int main() {
    int opcion;
    char rutaArchivo[256];
    Venta *ventas = NULL;
    int totalVentas = 0;

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
                printf("Ingrese la ruta del archivo JSON para importar datos: ");
                scanf("%s", rutaArchivo);

                int totalObjetos = contar_objetos_json(rutaArchivo);
                if (totalObjetos >= 0) {
                    printf("Total de ventas en el archivo: %d\n", totalObjetos);
                }

                importar_datos(rutaArchivo, &ventas, &totalVentas);
                printf("Datos importados correctamente. Total de ventas procesadas: %d\n", totalVentas); // Aquí debería usar `totalVentas`
                break;

            case 2: {
                int subopcion = 0;  // Inicializa subopcion
                do {
                    printf("\n=== Procesamiento de datos ===\n");
                    printf("1. Completar faltantes\n");
                    printf("2. Eliminar datos duplicados\n");
                    printf("3. Regresar al menú principal\n");
                    printf("Seleccione una opción: ");
                    scanf("%d", &subopcion);

                    switch (subopcion) {
                        case 1:
                            completar_datos_faltantes(ventas, totalVentas);
                            break;

                        case 2:
                            eliminar_duplicados(ventas, &totalVentas);
                            break;

                        case 3:
                            printf("Regresando al menú principal...\n");
                            break;

                        default:
                            printf("Opción no válida. Intente de nuevo.\n");
                            break;
                    }
                } while (subopcion != 3);  // Sale al menú principal cuando el usuario selecciona 3
                break;
            }

            case 3:
                // Implementar analizarDatos();
                break;

            case 4:
                // Implementar analizarTemporal();
                break;

            case 5:
                // Implementar mostrarEstadisticas();
                break;

            case 6:
                // Implementar guardarDatos();
                break;

            case 7:
                printf("Saliendo del sistema...\n");
                break;

            default:
                printf("Opción no válida. Intente de nuevo.\n");
        }
    } while (opcion != 7);

    free(ventas);

    return 0;
}

