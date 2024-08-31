#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include "importar.h"
#include "venta.h"
#include "procesar.h"
#include "analizar.h"
#include "analizarTemporal.h"
#include "estadisticas.h"
#include "guardar.h"
#include "estadisticasPDF.h"

#define RUTA_ARCHIVO "ventas.json"
#define ARCHIVO_PDF "estadisticas.pdf"

int main() {
    int opcion;
    char rutaArchivo[256] = "";
    Venta *ventas = NULL;
    int totalVentas = 0;

    cargar_datos_previos(RUTA_ARCHIVO, &ventas, &totalVentas);

    do {
        printf("\n===== Sistema de Análisis de Datos de Ventas =====\n");
        printf("1. Importar datos de ventas\n");
        printf("2. Procesar datos\n");
        printf("3. Analizar datos\n");
        printf("4. Análisis temporal\n");
        printf("5. Mostrar estadísticas\n");
        printf("6. Guardar datos\n");
        printf("7. Exportar estadísticas a PDF\n");
        printf("8. Salir\n");
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
                printf("Datos importados correctamente. Total de ventas procesadas: %d\n", totalVentas);
                break;

            case 2:
                if (rutaArchivo[0] == '\0') {
                    printf("Primero debe importar los datos.\n");
                    break;
                }

                int subopcion;
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
                } while (subopcion != 3);
                break;

            case 3:
                if (rutaArchivo[0] == '\0') {
                    printf("Primero debe importar los datos.\n");
                    break;
                }

                do {
                    printf("\n=== Análisis de datos ===\n");
                    printf("1. Total de ventas\n");
                    printf("2. Total de ventas mensuales\n");
                    printf("3. Total de ventas anuales\n");
                    printf("4. Regresar al menú principal\n");
                    printf("Seleccione una opción: ");
                    scanf("%d", &subopcion);

                    switch (subopcion) {
                        case 1: {
                            double total = calcular_total_ventas(ventas, totalVentas);
                            printf("Total de ventas: %.2f\n", total);
                            break;
                        }

                        case 2:
                            calcular_total_ventas_mensuales(ventas, totalVentas);
                            break;

                        case 3:
                            calcular_total_ventas_anuales(ventas, totalVentas);
                            break;

                        case 4:
                            printf("Regresando al menú principal...\n");
                            break;

                        default:
                            printf("Opción no válida. Intente de nuevo.\n");
                            break;
                    }
                } while (subopcion != 4);
                break;

            case 4:
                if (rutaArchivo[0] == '\0') {
                    printf("Primero debe importar los datos.\n");
                    break;
                }

                do {
                    printf("\n=== Análisis Temporal ===\n");
                    printf("1. Mes con mayor venta y día más activo\n");
                    printf("2. Tasa de crecimiento o decrecimiento en un trimestre\n");
                    printf("3. Regresar al menú principal\n");
                    printf("Seleccione una opción: ");
                    scanf("%d", &subopcion);

                    switch (subopcion) {
                        case 1:
                            mes_con_mayor_venta_y_dia_mas_activo(ventas, totalVentas);
                            break;

                        case 2: {
                            int trimestre;
                            printf("Ingrese el trimestre (1-4): ");
                            scanf("%d", &trimestre);
                            calcular_tasa_crecimiento_trimestre(ventas, totalVentas, trimestre);
                            break;
                        }

                        case 3:
                            printf("Regresando al menú principal...\n");
                            break;

                        default:
                            printf("Opción no válida. Intente de nuevo.\n");
                            break;
                    }
                } while (subopcion != 3);
                break;

            case 5:
                if (rutaArchivo[0] == '\0') {
                    printf("Primero debe importar los datos.\n");
                    break;
                }

                EstadisticaCategoria categorias[5];
                mostrar_top_5_categorias(ventas, totalVentas, categorias);
                break;

            case 6:
		if (rutaArchivo[0] == '\0') {
                    printf("Primero debe importar los datos.\n");
                    break;
                }

                guardar_datos(RUTA_ARCHIVO, ventas, totalVentas);
                break;

            case 7: {
		if (rutaArchivo[0] == '\0') {
                    printf("Primero debe importar los datos.\n");
                    break;
                }

                EstadisticaCategoria categorias[5];
                // Llenar la estructura con los datos del top 5 y exportar a PDF
                mostrar_top_5_categorias(ventas, totalVentas, categorias);
                exportar_estadisticas_pdf(ARCHIVO_PDF, categorias, 5);
                break;
            }

            case 8:
		if (rutaArchivo[0] == '\0') {
                    printf("Primero debe importar los datos.\n");
                    break;
                }

                guardar_datos(RUTA_ARCHIVO, ventas, totalVentas);
                printf("Saliendo del sistema...\n");
                break;

            default:
                printf("Opción no válida. Intente de nuevo.\n");
        }
    } while (opcion != 8);

    free(ventas);
    return 0;
}

