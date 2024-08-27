#ifndef VENTA_H
#define VENTA_H

typedef struct {
    int venta_id;
    char fecha[11];  // formato yyyy-mm-dd
    int producto_id;
    char producto_nombre[100];
    char categoria[50];
    int cantidad;
    float precio_unitario;
    float total;
} Venta;
#endif

