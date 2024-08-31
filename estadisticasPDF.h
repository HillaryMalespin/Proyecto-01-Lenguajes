#ifndef ESTADISTICASPDF_H
#define ESTADISTICASPDF_H

#include "estadisticas.h"  // Incluimos el archivo donde se define EstadisticaCategoria

/**
 * Exporta las estadísticas de ventas a un archivo PDF.
 * 
 * @param nombreArchivo Nombre del archivo PDF a crear.
 * @param categorias Array de estructuras EstadisticaCategoria con los datos de las categorías.
 * @param totalCategorias Número total de categorías en el array.
 * 
 * La función crea un documento PDF y agrega una página con las estadísticas de ventas en formato de texto.
 * Luego guarda el archivo PDF con el nombre proporcionado.
 */
void exportar_estadisticas_pdf(const char *nombreArchivo, EstadisticaCategoria *categorias, int totalCategorias);

#endif
