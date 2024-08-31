#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estadisticasPDF.h"
#include "hpdf.h"
#include "estadisticas.h"

/**
 * Manejador de errores para la biblioteca libhpdf.
 * 
 * @param error_no Código de error principal.
 * @param detail_no Código de error detallado.
 * @param user_data Datos del usuario (no se utilizan en este caso).
 * 
 * Esta función se llama cuando ocurre un error en la biblioteca libhpdf.
 * Imprime un mensaje de error y termina la ejecución del programa.
 */
void error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data) {
    printf("Error: error_no=%04X, detail_no=%d\n", (unsigned int)error_no, (int)detail_no);
    exit(1);
}

/**
 * Exporta las estadísticas de ventas a un archivo PDF.
 * 
 * @param nombreArchivo Nombre del archivo PDF a crear.
 * @param categorias Array de estructuras EstadisticaCategoria con los datos de las categorías.
 * @param totalCategorias Número total de categorías en el array.
 * 
 * La función crea un documento PDF utilizando la biblioteca libhpdf, agrega una página al documento,
 * y escribe las estadísticas de ventas en la página. Luego guarda el archivo PDF con el nombre proporcionado.
 */
void exportar_estadisticas_pdf(const char *nombreArchivo, EstadisticaCategoria *categorias, int totalCategorias) {
    HPDF_Doc pdf;
    HPDF_Page page;
    HPDF_Font font;
    char buf[256];
    float y = 750;

    // Crear un nuevo documento PDF
    pdf = HPDF_New(error_handler, NULL);
    if (!pdf) {
        printf("Error al crear el objeto PDF.\n");
        return;
    }

    // Agregar una página al documento
    page = HPDF_AddPage(pdf);
    HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);

    // Obtener una fuente y establecer el tamaño del texto
    font = HPDF_GetFont(pdf, "Helvetica", NULL);

    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, font, 24);
    HPDF_Page_TextOut(page, 200, y, "Estadísticas de Ventas");
    HPDF_Page_SetFontAndSize(page, font, 16);
    y -= 50;

    // Escribir las estadísticas en el PDF
    for (int i = 0; i < totalCategorias; i++) {
        snprintf(buf, sizeof(buf), "%d. %s: %.2f", i + 1, categorias[i].categoria, categorias[i].total_ventas);
        HPDF_Page_TextOut(page, 100, y, buf);
        y -= 30;
    }

    HPDF_Page_EndText(page);

    // Guardar el archivo PDF
    HPDF_SaveToFile(pdf, nombreArchivo);
    HPDF_Free(pdf);

    printf("Estadísticas exportadas correctamente en %s\n", nombreArchivo);
}


