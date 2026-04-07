#include <iostream>
#include <fstream>
#include <string>
#include <mpfr.h>

// Funcion auxiliar para extraer el numero despues de la coma en el CSV
std::string extraerValor(const std::string& linea) {
    size_t pos = linea.find(',');
    if (pos != std::string::npos) {
        return linea.substr(pos + 1);
    }
    return "0";
}

int main() {
    // Usamos 4096 bits de precision para no perder datos al hacer las restas
    mpfr_set_default_prec(4096);

    // Abrir los tres archivos de entrada generados previamente
    std::ifstream arch_float("trayectoria_float.csv");
    std::ifstream arch_double("trayectoria_double.csv");
    std::ifstream arch_mpfr("trayectoria_mpfr.csv");

    // Crear el archivo consolidado de salida
    std::ofstream arch_out("resultados_comparacion.csv");

    // Verificar que los archivos se abrieron correctamente
    if (!arch_float.is_open() || !arch_double.is_open() || !arch_mpfr.is_open()) {
        std::cerr << "Error: No se encontraron los archivos CSV de entrada." << std::endl;
        return 1;
    }

    // Escribir los encabezados de la tabla consolidada
    arch_out << "Iteracion,Valor_MPFR,Valor_Float,Dif_Abs_Float,Err_Rel_Float_%,Valor_Double,Dif_Abs_Double,Err_Rel_Double_%\n";

    std::string linea_f, linea_d, linea_m;

    // Saltar la primera linea (encabezados) de los archivos de entrada
    std::getline(arch_float, linea_f);
    std::getline(arch_double, linea_d);
    std::getline(arch_mpfr, linea_m);

    // Inicializar las variables MPFR para los calculos de error
    mpfr_t val_m, val_f, val_d, dif_f, dif_d, err_f, err_d;
    mpfr_init(val_m); mpfr_init(val_f); mpfr_init(val_d);
    mpfr_init(dif_f); mpfr_init(dif_d); mpfr_init(err_f); mpfr_init(err_d);

    char buf_val_m[100], buf_val_f[100], buf_val_d[100];
    char buf_dif_f[100], buf_err_f[100], buf_dif_d[100], buf_err_d[100];

    int iteracion = 0;

    // Leer linea por linea (hasta 1000 iteraciones)
    while (std::getline(arch_mpfr, linea_m) && 
           std::getline(arch_float, linea_f) && 
           std::getline(arch_double, linea_d)) {
        
        // Extraer los valores en formato texto
        std::string str_m = extraerValor(linea_m);
        std::string str_f = extraerValor(linea_f);
        std::string str_d = extraerValor(linea_d);

        // Convertir texto a formato de precision arbitraria MPFR
        mpfr_set_str(val_m, str_m.c_str(), 10, MPFR_RNDN);
        mpfr_set_str(val_f, str_f.c_str(), 10, MPFR_RNDN);
        mpfr_set_str(val_d, str_d.c_str(), 10, MPFR_RNDN);

        // --- CALCULOS PARA FLOAT ---
        // Diferencia absoluta: |Float - MPFR|
        mpfr_sub(dif_f, val_f, val_m, MPFR_RNDN);
        mpfr_abs(dif_f, dif_f, MPFR_RNDN);
        
        // Error relativo porcentual: (Diferencia / MPFR) * 100
        mpfr_div(err_f, dif_f, val_m, MPFR_RNDN);
        mpfr_abs(err_f, err_f, MPFR_RNDN);
        mpfr_mul_ui(err_f, err_f, 100, MPFR_RNDN);

        // --- CALCULOS PARA DOUBLE ---
        // Diferencia absoluta: |Double - MPFR|
        mpfr_sub(dif_d, val_d, val_m, MPFR_RNDN);
        mpfr_abs(dif_d, dif_d, MPFR_RNDN);
        
        // Error relativo porcentual: (Diferencia / MPFR) * 100
        mpfr_div(err_d, dif_d, val_m, MPFR_RNDN);
        mpfr_abs(err_d, err_d, MPFR_RNDN);
        mpfr_mul_ui(err_d, err_d, 100, MPFR_RNDN);

        // --- FORMATEO Y EXPORTACION ---
        // Formateamos los valores y los errores a notacion cientifica o decimal segun corresponda
        mpfr_snprintf(buf_val_m, sizeof(buf_val_m), "%.17Re", val_m);
        mpfr_snprintf(buf_val_f, sizeof(buf_val_f), "%.9Re", val_f);
        mpfr_snprintf(buf_dif_f, sizeof(buf_dif_f), "%.5Re", dif_f);
        mpfr_snprintf(buf_err_f, sizeof(buf_err_f), "%.5Re", err_f);
        
        mpfr_snprintf(buf_val_d, sizeof(buf_val_d), "%.17Re", val_d);
        mpfr_snprintf(buf_dif_d, sizeof(buf_dif_d), "%.5Re", dif_d);
        mpfr_snprintf(buf_err_d, sizeof(buf_err_d), "%.5Re", err_d);

        // Escribir la fila en el CSV consolidado
        arch_out << iteracion << "," 
                 << buf_val_m << "," 
                 << buf_val_f << "," << buf_dif_f << "," << buf_err_f << ","
                 << buf_val_d << "," << buf_dif_d << "," << buf_err_d << "\n";

        iteracion++;
    }

    // Limpieza de memoria
    arch_float.close(); arch_double.close(); arch_mpfr.close(); arch_out.close();
    mpfr_clear(val_m); mpfr_clear(val_f); mpfr_clear(val_d);
    mpfr_clear(dif_f); mpfr_clear(dif_d); mpfr_clear(err_f); mpfr_clear(err_d);

    std::cout << "Analisis y cruce de datos completado." << std::endl;
    std::cout << "Se genero la tabla consolidada: resultados_comparacion.csv" << std::endl;

    return 0;
}