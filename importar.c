#include "importar.h"
#include "venta.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

void importar_datos(const char *ruta_archivo, Venta **ventas, int *total_ventas) {
    FILE *archivo = fopen(ruta_archivo, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    fseek(archivo, 0, SEEK_END);
    long length = ftell(archivo);
    fseek(archivo, 0, SEEK_SET);

    char *data = malloc(length + 1);
    if (data == NULL) {
        perror("Error al asignar memoria");
        fclose(archivo);
        return;
    }

    fread(data, 1, length, archivo);
    data[length] = '\0';

    fclose(archivo);

    cJSON *json = cJSON_Parse(data);
    if (json == NULL) {
        printf("Error al parsear el JSON\n");
        free(data);
        return;
    }

    int num_ventas = cJSON_GetArraySize(json);
    *ventas = realloc(*ventas, (*total_ventas + num_ventas) * sizeof(Venta));
    if (*ventas == NULL) {
        perror("Error al asignar memoria para ventas");
        cJSON_Delete(json);
        free(data);
        return;
    }

    for (int i = 0; i < num_ventas; i++) {
        cJSON *venta_json = cJSON_GetArrayItem(json, i);

        Venta nueva_venta;
        nueva_venta.venta_id = cJSON_GetObjectItem(venta_json, "venta_id")->valueint;
        strcpy(nueva_venta.fecha, cJSON_GetObjectItem(venta_json, "fecha")->valuestring);
        nueva_venta.producto_id = cJSON_GetObjectItem(venta_json, "producto_id")->valueint;
        strcpy(nueva_venta.producto_nombre, cJSON_GetObjectItem(venta_json, "producto_nombre")->valuestring);
        strcpy(nueva_venta.categoria, cJSON_GetObjectItem(venta_json, "categoria")->valuestring);
        nueva_venta.cantidad = cJSON_GetObjectItem(venta_json, "cantidad")->valueint;
        nueva_venta.precio_unitario = cJSON_GetObjectItem(venta_json, "precio_unitario")->valuedouble;
        nueva_venta.total = cJSON_GetObjectItem(venta_json, "total")->valuedouble;

        (*ventas)[*total_ventas] = nueva_venta;
        (*total_ventas)++;
    }

    cJSON_Delete(json);
    free(data);
}

