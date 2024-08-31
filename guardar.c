#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#include "venta.h"
#include <string.h>

/**
 * Carga datos previos desde un archivo JSON y los almacena en un arreglo de ventas.
 * 
 * @param ruta Ruta del archivo JSON que contiene los datos previos.
 * @param ventas Puntero a un puntero de tipo `Venta` donde se almacenarán los datos cargados.
 * @param totalVentas Puntero a un entero donde se almacenará el total de ventas cargadas.
 */
void cargar_datos_previos(const char *ruta, Venta **ventas, int *totalVentas) {
    // Abrir el archivo en modo lectura
    FILE *archivo = fopen(ruta, "r");
    if (!archivo) {
        // Si el archivo no se puede abrir, mostrar un mensaje y salir
        printf("No se encontraron datos previos. Iniciando con un nuevo conjunto de datos.\n");
        return;
    }

    // Mover el puntero de archivo al final para obtener el tamaño del archivo
    fseek(archivo, 0, SEEK_END);
    long length = ftell(archivo);
    // Volver al inicio del archivo
    fseek(archivo, 0, SEEK_SET);

    // Asignar memoria para leer el contenido del archivo
    char *data = malloc(length + 1);
    // Leer el contenido del archivo en el buffer
    fread(data, 1, length, archivo);
    // Asegurarse de que el buffer esté terminado en nulo
    data[length] = '\0';
    // Cerrar el archivo
    fclose(archivo);

    // Parsear el contenido JSON del buffer
    cJSON *json = cJSON_Parse(data);
    if (!json) {
        // Si el parseo falla, mostrar un mensaje de error y liberar la memoria
        printf("Error al cargar el archivo JSON.\n");
        free(data);
        return;
    }

    // Obtener el número de elementos en el array JSON
    int count = cJSON_GetArraySize(json);
    // Asignar memoria para el arreglo de ventas
    *ventas = malloc(count * sizeof(Venta));

    // Extraer datos de cada elemento en el array JSON
    for (int i = 0; i < count; i++) {
        cJSON *item = cJSON_GetArrayItem(json, i);
        // Leer y almacenar cada campo en la estructura Venta
        (*ventas)[i].venta_id = cJSON_GetObjectItem(item, "venta_id")->valueint;
        strcpy((*ventas)[i].fecha, cJSON_GetObjectItem(item, "fecha")->valuestring);
        (*ventas)[i].producto_id = cJSON_GetObjectItem(item, "producto_id")->valueint;
        strcpy((*ventas)[i].producto_nombre, cJSON_GetObjectItem(item, "producto_nombre")->valuestring);
        strcpy((*ventas)[i].categoria, cJSON_GetObjectItem(item, "categoria")->valuestring);
        (*ventas)[i].cantidad = cJSON_GetObjectItem(item, "cantidad")->valueint;
        (*ventas)[i].precio_unitario = cJSON_GetObjectItem(item, "precio_unitario")->valuedouble;
        (*ventas)[i].total = cJSON_GetObjectItem(item, "total")->valuedouble;
    }

    // Almacenar el total de ventas cargadas
    *totalVentas = count;
    // Liberar memoria del objeto JSON y del buffer de datos
    cJSON_Delete(json);
    free(data);

    // Mostrar mensaje de éxito con el total de ventas cargadas
    printf("Datos previos cargados exitosamente. Total de ventas cargadas: %d\n", *totalVentas);
}



/**
 * Guarda los datos de ventas en un archivo JSON.
 * 
 * @param ruta Ruta del archivo JSON donde se guardarán los datos.
 * @param ventas Arreglo de ventas que se guardará en el archivo.
 * @param totalVentas Total de ventas que se deben guardar.
 */
void guardar_datos(const char *ruta, Venta *ventas, int totalVentas) {
    // Crear un objeto JSON como array
    cJSON *json = cJSON_CreateArray();

    // Crear un objeto JSON para cada venta y añadirlo al array
    for (int i = 0; i < totalVentas; i++) {
        cJSON *item = cJSON_CreateObject();
        // Añadir cada campo de la venta al objeto JSON
        cJSON_AddNumberToObject(item, "venta_id", ventas[i].venta_id);
        cJSON_AddStringToObject(item, "fecha", ventas[i].fecha);
        cJSON_AddNumberToObject(item, "producto_id", ventas[i].producto_id);
        cJSON_AddStringToObject(item, "producto_nombre", ventas[i].producto_nombre);
        cJSON_AddStringToObject(item, "categoria", ventas[i].categoria);
        cJSON_AddNumberToObject(item, "cantidad", ventas[i].cantidad);
        cJSON_AddNumberToObject(item, "precio_unitario", ventas[i].precio_unitario);
        cJSON_AddNumberToObject(item, "total", ventas[i].total);

        // Añadir el objeto al array JSON
        cJSON_AddItemToArray(json, item);
    }

    // Convertir el objeto JSON a una cadena
    char *data = cJSON_Print(json);
    // Abrir el archivo en modo escritura
    FILE *archivo = fopen(ruta, "w");
    if (archivo) {
        // Escribir los datos JSON en el archivo
        fputs(data, archivo);
        // Cerrar el archivo
        fclose(archivo);
    } else {
        // Mostrar mensaje de error si no se puede abrir el archivo
        printf("Error al guardar el archivo JSON.\n");
    }

    // Liberar memoria del objeto JSON y de la cadena
    free(data);
    cJSON_Delete(json);

    // Mostrar mensaje de éxito con la ruta del archivo guardado
    printf("Datos guardados correctamente en %s\n", ruta);
}
