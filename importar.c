#include "importar.h"
#include "venta.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

void importar_datos(const char *ruta_archivo, Venta **ventas, int *total_ventas) {
    FILE *archivo = fopen(ruta_archivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo: %s\n", ruta_archivo);
        return;
    }

    fseek(archivo, 0, SEEK_END);
    long length = ftell(archivo);
    fseek(archivo, 0, SEEK_SET);

    char *data = malloc(length + 1);
    if (data == NULL) {
        printf("No se pudo asignar memoria para leer el archivo.\n");
        fclose(archivo);
        return;
    }
    
    fread(data, 1, length, archivo);
    fclose(archivo);
    data[length] = '\0';

    printf("Contenido del archivo JSON:\n%s\n", data);  // Depuración: Imprimir contenido del archivo

    cJSON *json = cJSON_Parse(data);
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            // Obtener la línea exacta del error y mostrarla
            int line = 1;
            for (const char *ptr = data; ptr < error_ptr; ptr++) {
                if (*ptr == '\n') {
                    line++;
                }
            }
            printf("Error en el producto en la línea %d: %s\n",line, error_ptr);
        }
        printf("El formato del archivo JSON es incorrecto.\n");
        free(data);
        return;
    }

    if (!cJSON_IsArray(json)) {
        printf("El JSON no es un array.\n");
        cJSON_Delete(json);
        free(data);
        return;
    }

    int registros_omitidos = 0;
    int ventas_procesadas = 0;  // Para contar los productos válidos

    int nuevo_tamano = *total_ventas + cJSON_GetArraySize(json);
    *ventas = realloc(*ventas, nuevo_tamano * sizeof(Venta));

    for (int i = 0; i < cJSON_GetArraySize(json); i++) {
        cJSON *item = cJSON_GetArrayItem(json, i);

        // Validar que todos los campos necesarios estén presentes
        cJSON *venta_id = cJSON_GetObjectItem(item, "venta_id");
        cJSON *fecha = cJSON_GetObjectItem(item, "fecha");
        cJSON *producto_id = cJSON_GetObjectItem(item, "producto_id");
        cJSON *producto_nombre = cJSON_GetObjectItem(item, "producto_nombre");
        cJSON *categoria = cJSON_GetObjectItem(item, "categoria");
        cJSON *cantidad = cJSON_GetObjectItem(item, "cantidad");
        cJSON *precio_unitario = cJSON_GetObjectItem(item, "precio_unitario");
        cJSON *total = cJSON_GetObjectItem(item, "total");

        // Reportar el registro si falta algún campo requerido
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

        // Si todos los campos son válidos, agregamos el registro
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
        ventas_procesadas++;  // Incrementar el contador de productos procesados correctamente
    }

    cJSON_Delete(json);
    free(data);

    printf("Importación completada. Total de ventas procesadas: %d\n", ventas_procesadas);
    printf("Registros omitidos: %d\n", registros_omitidos);
}



int contar_objetos_json(const char *ruta_archivo) {
    FILE *archivo = fopen(ruta_archivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo: %s\n", ruta_archivo);
        return -1;  // Retorna -1 en caso de error
    }

    fseek(archivo, 0, SEEK_END);
    long length = ftell(archivo);
    fseek(archivo, 0, SEEK_SET);

    char *data = malloc(length + 1);
    if (data == NULL) {
        printf("No se pudo asignar memoria para leer el archivo.\n");
        fclose(archivo);
        return -1;  // Retorna -1 en caso de error
    }

    fread(data, 1, length, archivo);
    fclose(archivo);
    data[length] = '\0';

    cJSON *json = cJSON_Parse(data);
    free(data);

    if (json == NULL) {
        printf("El formato del archivo JSON es incorrecto.\n");
        return -1;  // Retorna -1 en caso de error
    }

    if (!cJSON_IsArray(json)) {
        printf("El JSON no es un array.\n");
        cJSON_Delete(json);
        return -1;  // Retorna -1 si el JSON no es un array
    }

    int cantidad_objetos = cJSON_GetArraySize(json);
    cJSON_Delete(json);

    return cantidad_objetos;  // Retorna la cantidad de objetos
}


    cJSON_Delete(json);
    free(data);
}

