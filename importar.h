#ifndef IMPORTAR_H
#define IMPORTAR_H

#include "venta.h"

void importar_datos(const char *ruta_archivo, Venta **ventas, int *total_ventas);

int contar_objetos_json(const char *ruta_archivo);


#endif
