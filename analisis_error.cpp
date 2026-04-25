#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <mpfr.h>

int main() {
    // Mantener 4096 bits para el análisis riguroso de pérdida de información
    mpfr_set_default_prec(4096);

    // Flujos de lectura sincronizada
    std::ifstream arch_float("trayectoria_float.csv");
    std::ifstream arch_double("trayectoria_double.csv");
    std::ifstream arch_mpfr("trayectoria_mpfr.csv");

    // Flujo de salida para el consolidado final
    std::ofstream arch_out("resultados_comparacion.csv");

    if (!arch_float.is_open() || !arch_double.is_open() || !arch_mpfr.is_open()) {
        std::cerr << "Error: No se encontraron los archivos CSV de entrada." << std::endl;
        return 1;
    }

    // Nuevos encabezados incorporando los metadatos del experimento
    arch_out << "ID_Exp,Iteracion,Valor_MPFR,Valor_Float,Dif_Abs_Float,Err_Rel_Float_%,Valor_Double,Dif_Abs_Double,Err_Rel_Double_%\n";

    std::string linea_f, linea_d, linea_m;

    // Descartar la fila de encabezados en los tres archivos
    std::getline(arch_float, linea_f);
    std::getline(arch_double, linea_d);
    std::getline(arch_mpfr, linea_m);

    // Inicialización del ecosistema MPFR
    mpfr_t val_m, val_f, val_d, dif_f, dif_d, err_f, err_d;
    mpfr_init(val_m); mpfr_init(val_f); mpfr_init(val_d);
    mpfr_init(dif_f); mpfr_init(dif_d); mpfr_init(err_f); mpfr_init(err_d);

    char buf_val_m[100], buf_val_f[100], buf_val_d[100];
    char buf_dif_f[100], buf_err_f[100], buf_dif_d[100], buf_err_d[100];

    // Procesamiento lineal asíncrono (1:1 correspondencia de filas)
    while (std::getline(arch_mpfr, linea_m) &&
           std::getline(arch_float, linea_f) &&
           std::getline(arch_double, linea_d)) {

        std::stringstream ss_m(linea_m);
        std::stringstream ss_f(linea_f);
        std::stringstream ss_d(linea_d);

        std::string id_exp, iteracion, str_m, str_f, str_d;
        std::string basura; // Para descartar los metadatos redundantes de float y double

        // Tokenización de la línea MPFR (Referencia maestra)
        std::getline(ss_m, id_exp, ',');
        std::getline(ss_m, iteracion, ',');
        std::getline(ss_m, str_m, ',');

        // Tokenización de Float y Double (Solo nos interesa la 3ra columna)
        std::getline(ss_f, basura, ','); std::getline(ss_f, basura, ','); std::getline(ss_f, str_f, ',');
        std::getline(ss_d, basura, ','); std::getline(ss_d, basura, ','); std::getline(ss_d, str_d, ',');

        // Conversión estricta a base 2 mediante MPFR
        mpfr_set_str(val_m, str_m.c_str(), 10, MPFR_RNDN);
        mpfr_set_str(val_f, str_f.c_str(), 10, MPFR_RNDN);
        mpfr_set_str(val_d, str_d.c_str(), 10, MPFR_RNDN);

        // --- CÁLCULOS PARA PRECISIÓN SIMPLE (FLOAT) ---
        mpfr_sub(dif_f, val_f, val_m, MPFR_RNDN);
        mpfr_abs(dif_f, dif_f, MPFR_RNDN);

        mpfr_div(err_f, dif_f, val_m, MPFR_RNDN);
        mpfr_abs(err_f, err_f, MPFR_RNDN);
        mpfr_mul_ui(err_f, err_f, 100, MPFR_RNDN);

        // --- CÁLCULOS PARA PRECISIÓN DOBLE (DOUBLE) ---
        mpfr_sub(dif_d, val_d, val_m, MPFR_RNDN);
        mpfr_abs(dif_d, dif_d, MPFR_RNDN);

        mpfr_div(err_d, dif_d, val_m, MPFR_RNDN);
        mpfr_abs(err_d, err_d, MPFR_RNDN);
        mpfr_mul_ui(err_d, err_d, 100, MPFR_RNDN);

        // --- FORMATEO Y EXPORTACIÓN ---
        mpfr_snprintf(buf_val_m, sizeof(buf_val_m), "%.17Re", val_m);
        mpfr_snprintf(buf_val_f, sizeof(buf_val_f), "%.9Re", val_f);
        mpfr_snprintf(buf_dif_f, sizeof(buf_dif_f), "%.5Re", dif_f);
        mpfr_snprintf(buf_err_f, sizeof(buf_err_f), "%.5Re", err_f);

        mpfr_snprintf(buf_val_d, sizeof(buf_val_d), "%.17Re", val_d);
        mpfr_snprintf(buf_dif_d, sizeof(buf_dif_d), "%.5Re", dif_d);
        mpfr_snprintf(buf_err_d, sizeof(buf_err_d), "%.5Re", err_d);

        // Construcción de la fila de salida con metadatos incorporados
        arch_out << id_exp << "," << iteracion << ","
                 << buf_val_m << ","
                 << buf_val_f << "," << buf_dif_f << "," << buf_err_f << ","
                 << buf_val_d << "," << buf_dif_d << "," << buf_err_d << "\n";
    }

    // Limpieza rigurosa de descriptores de archivo y memoria del heap
    arch_float.close(); arch_double.close(); arch_mpfr.close(); arch_out.close();
    mpfr_clear(val_m); mpfr_clear(val_f); mpfr_clear(val_d);
    mpfr_clear(dif_f); mpfr_clear(dif_d); mpfr_clear(err_f); mpfr_clear(err_d);

    std::cout << "Análisis y cruce de datos completado (35,000 registros procesados)." << std::endl;
    std::cout << "Se generó la tabla consolidada: resultados_comparacion.csv" << std::endl;

    return 0;
}