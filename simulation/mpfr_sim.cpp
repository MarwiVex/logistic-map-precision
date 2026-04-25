#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <mpfr.h>

int main() {
    // Configuración de 4096 bits para garantizar exactitud tras 1000 iteraciones [cite: 46, 47]
    mpfr_set_default_prec(4096);

    // Parámetros experimentales en formato string para evitar truncamiento inicial [cite: 49]
    const std::vector<std::string> tasas_r = {"3.90", "3.92", "3.95", "3.98", "4.00"};
    const std::vector<std::string> cond_x0 = {"0.1", "0.2", "0.3", "0.4", "0.5", "0.6", "0.7"};
    const int iteraciones = 1000;

    // Inicialización de variables MPFR
    mpfr_t r_mpfr, x_mpfr, temp;
    mpfr_init(r_mpfr);
    mpfr_init(x_mpfr);
    mpfr_init(temp);

    std::ofstream archivo("trayectoria_mpfr.csv");
    archivo << "ID_Exp,Iteracion,Valor\n";

    char buffer[150];

    // Ejecución de la batería de 35 experimentos [cite: 48, 50]
    for (const auto& r_str : tasas_r) {
        for (const auto& x0_str : cond_x0) {

            // Asignación directa desde string para preservar precisión matemática [cite: 64]
            mpfr_set_str(r_mpfr, r_str.c_str(), 10, MPFR_RNDN);
            mpfr_set_str(x_mpfr, x0_str.c_str(), 10, MPFR_RNDN);

            std::string id_exp = "EXP-R" + r_str + "-X" + x0_str;

            // Registro de condición inicial (n=0)
            mpfr_snprintf(buffer, sizeof(buffer), "%.50Rf", x_mpfr);
            archivo << id_exp << ",0," << buffer << "\n";

            // Bucle del mapa logístico: x = r * x * (1 - x) [cite: 14, 73]
            for (int i = 1; i <= iteraciones; ++i) {
                mpfr_ui_sub(temp, 1, x_mpfr, MPFR_RNDN);     // (1 - x)
                mpfr_mul(x_mpfr, x_mpfr, temp, MPFR_RNDN);   // x * (1 - x)
                mpfr_mul(x_mpfr, x_mpfr, r_mpfr, MPFR_RNDN); // r * x * (1 - x)

                // Exportación a 50 decimales (Conjunto de Control) [cite: 53, 54]
                mpfr_snprintf(buffer, sizeof(buffer), "%.50Rf", x_mpfr);
                archivo << id_exp << "," << i << "," << buffer << "\n";
            }
        }
    }

    archivo.close();

    // Liberación de memoria MPFR
    mpfr_clear(r_mpfr);
    mpfr_clear(x_mpfr);
    mpfr_clear(temp);

    std::cout << "Simulacion MPFR completada. Archivo generado: trayectoria_mpfr.csv" << std::endl;

    return 0;
}