#include "importar.h"      // Incluye el archivo de encabezado con las declaraciones de las funciones
#include "venta.h"        // Incluye el archivo de encabezado donde se define la estructura Venta
#include <stdio.h>        // Incluye la biblioteca estándar de entrada/salida
#include <stdlib.h>       // Incluye la biblioteca estándar de funciones utilitarias
#include <string.h>       // Incluye la biblioteca estándar para manipulación de cadenas
#include "cJSON.h"        // Incluye la biblioteca cJSON para manejar JSON

/**
 * Función: importar_datos
 * Retorno: void
 * Parámetros: 
 *   - const char *ruta_archivo: Ruta del archivo JSON que contiene los datos.
 *   - Venta **ventas: Puntero a un puntero de tipo `Venta` donde se almacenarán los datos cargados.
 *   - int *total_ventas: Puntero a un entero donde se almacenará el total de ventas cargadas.
 * Descripción: Carga los datos de ventas desde un archivo JSON y los almacena en un arreglo de ventas.
 */
void importar_datos(const char *ruta_archivo, Venta **ventas, int *total_ventas) {
    // Abre el archivo JSON para lectura
    FILE *archivo = fopen(ruta_archivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo: %s\n", ruta_archivo);
        return;
    }

    // Mueve el puntero del archivo al final para obtener el tamaño del archivo
    fseek(archivo, 0, SEEK_END);
    long length = ftell(archivo);
    fseek(archivo, 0, SEEK_SET);

    // Asigna memoria para almacenar el contenido del archivo
    char *data = malloc(length + 1);
    if (data == NULL) {
        printf("No se pudo asignar memoria para leer el archivo.\n");
        fclose(archivo);
        return;
    }
    
    // Lee el contenido del archivo
    fread(data, 1, length, archivo);
    fclose(archivo);
    data[length] = '\0';  // Termina la cadena con null

    printf("Contenido del archivo JSON:\n%s\n", data);  // Depuración: Imprimir contenido del archivo

    // Analiza el contenido del archivo JSON
    cJSON *json = cJSON_Parse(data);
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            // Contar la línea del error en el JSON y mostrarla
            int line = 1;
            for (const char *ptr = data; ptr < error_ptr; ptr++) {
                if (*ptr == '\n') {
                    line++;
                }
            }
            printf("Error en el producto en la línea %d: %s\n", line, error_ptr);
        }
        printf("El formato del archivo JSON es incorrecto.\n");
        free(data);
        return;
    }

    // Verifica que el JSON sea un array
    if (!cJSON_IsArray(json)) {
        printf("El JSON no es un array.\n");
        cJSON_Delete(json);
        free(data);
        return;
    }

    int registros_omitidos = 0;  // Contador de registros omitidos
    int ventas_procesadas = 0;   // Contador de ventas procesadas

    // Reasigna memoria para el arreglo de ventas, agregando el tamaño del nuevo JSON
    int nuevo_tamano = *total_ventas + cJSON_GetArraySize(json);
    *ventas = realloc(*ventas, nuevo_tamano * sizeof(Venta));

    // Itera sobre cada elemento del array JSON
    for (int i = 0; i < cJSON_GetArraySize(json); i++) {
        cJSON *item = cJSON_GetArrayItem(json, i);

        // Obtiene los elementos del JSON
        cJSON *venta_id = cJSON_GetObjectItem(item, "venta_id");
        cJSON *fecha = cJSON_GetObjectItem(item, "fecha");
        cJSON *producto_id = cJSON_GetObjectItem(item, "producto_id");
        cJSON *producto_nombre = cJSON_GetObjectItem(item, "producto_nombre");
        cJSON *categoria = cJSON_GetObjectItem(item, "categoria");
        cJSON *cantidad = cJSON_GetObjectItem(item, "cantidad");
        cJSON *precio_unitario = cJSON_GetObjectItem(item, "precio_unitario");
        cJSON *total = cJSON_GetObjectItem(item, "total");

        // Verifica que todos los campos requeridos estén presentes y sean del tipo correcto
        if (!cJSON_IsNumber(venta_id)) {
            printf("Registro %d omitido: falta 'venta_id'.\n", i + 1);
            registros_omitidos++;
            continue;
        }
        if (!cJSON_IsString(fecha)) {
            printf("Registro %d omitido: falta 'fecha'.\n", i + 1);
            registros_omitidos++;
            continue;
        }
        if (!cJSON_IsNumber(producto_id)) {
            printf("Registro %d omitido: falta 'producto_id'.\n", i + 1);
            registros_omitidos++;
            continue;
        }
        if (!cJSON_IsString(producto_nombre)) {
            printf("Registro %d omitido: falta 'producto_nombre'.\n", i + 1);
            registros_omitidos++;
            continue;
        }
        if (!cJSON_IsString(categoria)) {
            printf("Registro %d omitido: falta 'categoria'.\n", i + 1);
            registros_omitidos++;
            continue;
        }
        if (!cJSON_IsNumber(cantidad)) {
            printf("Registro %d omitido: falta 'cantidad'.\n", i + 1);
            registros_omitidos++;
            continue;
        }
        if (!cJSON_IsNumber(precio_unitario)) {
            printf("Registro %d omitido: falta 'precio_unitario'.\n", i + 1);
            registros_omitidos++;
            continue;
        }
        if (!cJSON_IsNumber(total)) {
            printf("Registro %d omitido: falta 'total'.\n", i + 1);
            registros_omitidos++;
            continue;
        }

        // Si todos los campos son válidos, almacena el registro
        Venta nueva_venta;
        nueva_venta.venta_id = venta_id->valueint;
        strcpy(nueva_venta.fecha, fecha->valuestring);
        nueva_venta.producto_id = producto_id->valueint;
        strcpy(nueva_venta.producto_nombre, producto_nombre->valuestring);
        strcpy(nueva_venta.categoria, categoria->valuestring);
        nueva_venta.cantidad = cantidad->valueint;
        nueva_venta.precio_unitario = precio_unitario->valuedouble;
        nueva_venta.total = total->valuedouble;

        (*ventas)[*total_ventas] = nueva_venta;
        (*total_ventas)++;
        ventas_procesadas++;
    }

    // Libera la memoria utilizada y elimina el objeto JSON
    cJSON_Delete(json);
    free(data);

    printf("Importación completada. Total de ventas procesadas: %d\n", ventas_procesadas);
    printf("Registros omitidos: %d\n", registros_omitidos);
}

/**
 * Función: contar_objetos_json
 * Retorno: int
 * Parámetros:
 *   - const char *ruta_archivo: Ruta del archivo JSON del cual contar los objetos.
 * Descripción: Cuenta la cantidad de objetos en un archivo JSON y retorna el total.
 */
int contar_objetos_json(const char *ruta_archivo) {
    // Abre el archivo JSON para lectura
    FILE *archivo = fopen(ruta_archivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo: %s\n", ruta_archivo);
        return -1;  // Retorna -1 en caso de error
    }

    // Mueve el puntero del archivo al final para obtener el tamaño del archivo
    fseek(archivo, 0, SEEK_END);
    long length = ftell(archivo);
    fseek(archivo, 0, SEEK_SET);

    // Asigna memoria para almacenar el contenido del archivo
    char *data = malloc(length + 1);
    if (data == NULL) {
        printf("No se pudo asignar memoria para leer el archivo.\n");
        fclose(archivo);
        return -1;  // Retorna -1 en caso de error
    }

    // Lee el contenido del archivo
    fread(data, 1, length, archivo);
    fclose(archivo);
    data[length] = '\0';  // Termina la cadena con null

    // Analiza el contenido del archivo JSON
    cJSON *json = cJSON_Parse(data);
    free(data);

    if (json == NULL) {
        printf("El formato del archivo JSON es incorrecto.\n");
        return -1;  // Retorna -1 en caso de error
    }

    // Verifica que el JSON sea un array
    if (!cJSON_IsArray(json)) {
        printf("El JSON no es un array.\n");
        cJSON_Delete(json);
        return -1;  // Retorna -1 si el JSON no es un array
    }

    // Cuenta y retorna la cantidad de objetos en el array JSON
    int cantidad_objetos = cJSON_GetArraySize(json);
    cJSON_Delete(json);

    return cantidad_objetos;  // Retorna la cantidad de objetos
}

