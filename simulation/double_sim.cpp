#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <sstream>

int main() {
    // Arreglos estáticos con los parámetros del diseño experimental en 64 bits
    const std::vector<double> tasas_r = {3.90, 3.92, 3.95, 3.98, 4.00};
    const std::vector<double> condiciones_x0 = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7};
    const int iteraciones = 1000; // Límite de la simulación

    // Archivo de salida para registrar las 35 trayectorias consolidadas
    std::ofstream archivo("trayectoria_double.csv");
    archivo << "ID_Exp,Iteracion,Valor\n";

    // Ejecución en bloque de los 35 experimentos independientes
    for (double r : tasas_r) {
        for (double x0 : condiciones_x0) {
            // Generación dinámica del identificador (EXP-R[valor_r]-X[valor_x0])
            std::ostringstream id_stream;
            id_stream << "EXP-R" << std::fixed << std::setprecision(2) << r
                      << "-X" << std::setprecision(1) << x0;
            std::string id_exp = id_stream.str();

            double x = x0;

            // Registro de la condición inicial con 17 decimales de resolución
            archivo << id_exp << ",0," << std::fixed << std::setprecision(17) << x << "\n";

            // Bucle principal del mapa logístico
            for (int i = 1; i <= iteraciones; ++i) {
                x = r * x * (1.0 - x);
                archivo << id_exp << "," << i << "," << std::fixed << std::setprecision(17) << x << "\n";
            }
        }
    }

    archivo.close();
    std::cout << "Simulacion en bloque con DOUBLE completada (35 experimentos)." << std::endl;
    std::cout << "Se genero el archivo consolidado: trayectoria_double.csv" << std::endl;

    return 0;
}