#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

int main() {
    // Flujos de lectura y escritura de archivos
    std::ifstream arch_in("resultados_comparacion.csv");
    std::ofstream arch_out("estimacion_lyapunov.csv");

    if (!arch_in.is_open()) {
        std::cerr << "Error de lectura." << std::endl;
        return 1;
    }

    // Encabezado con los tres valores finales (n=1000) y los exponentes estimados
    arch_out << "ID_Exp,X_Final_MPFR,X_Final_Float,X_Final_Double,Lyapunov_Float,Lyapunov_Double\n";

    std::string linea;
    std::getline(arch_in, linea); // Saltar el encabezado del consolidado

    std::string current_id, x_fin_m, x_fin_f, x_fin_d;
    double e1_f = 0, e2_f = 0, e1_d = 0, e2_d = 0;
    const double EPSILON = 1e-50; // Seguridad para evitar log(0)

    while (std::getline(arch_in, linea)) {
        // Tokenización manual por posición de comas para maximizar eficiencia
        size_t c1 = linea.find(',');
        size_t c2 = linea.find(',', c1 + 1);
        size_t c3 = linea.find(',', c2 + 1);
        size_t c4 = linea.find(',', c3 + 1);
        size_t c5 = linea.find(',', c4 + 1);
        size_t c6 = linea.find(',', c5 + 1);
        size_t c7 = linea.find(',', c6 + 1);
        size_t c8 = linea.find(',', c7 + 1);

        int iter = std::stoi(linea.substr(c1 + 1, c2 - c1 - 1));

        // Captura de errores en los puntos de control
        if (iter == 5) {
            current_id = linea.substr(0, c1);
            double dif_f = std::stod(linea.substr(c4 + 1, c5 - c4 - 1));
            double dif_d = std::stod(linea.substr(c7 + 1, c8 - c7 - 1));

            e1_f = (dif_f < EPSILON) ? EPSILON : dif_f;
            e1_d = (dif_d < EPSILON) ? EPSILON : dif_d;

        } else if (iter == 20) {
            double dif_f = std::stod(linea.substr(c4 + 1, c5 - c4 - 1));
            e2_f = (dif_f < EPSILON) ? EPSILON : dif_f;

        } else if (iter == 45) {
            double dif_d = std::stod(linea.substr(c7 + 1, c8 - c7 - 1));
            e2_d = (dif_d < EPSILON) ? EPSILON : dif_d;

        } else if (iter == 1000) {
            // Captura de los tres resultados finales para comparación visual
            x_fin_m = linea.substr(c2 + 1, c3 - c2 - 1);
            x_fin_f = linea.substr(c3 + 1, c4 - c3 - 1);
            x_fin_d = linea.substr(c6 + 1, c7 - c6 - 1);

            // Estimación directa de Lyapunov (pendiente entre dos puntos)
            double lyap_f = (std::log(e2_f) - std::log(e1_f)) / 15.0; // (20 - 5)
            double lyap_d = (std::log(e2_d) - std::log(e1_d)) / 40.0; // (45 - 5)

            // Registro final de los 35 experimentos
            arch_out << current_id << "," << x_fin_m << "," << x_fin_f << "," << x_fin_d << ","
                     << lyap_f << "," << lyap_d << "\n";
        }
    }

    arch_in.close();
    arch_out.close();

    std::cout << "Analisis finalizado: estimacion_lyapunov.csv generado con exito." << std::endl;
    return 0;
}