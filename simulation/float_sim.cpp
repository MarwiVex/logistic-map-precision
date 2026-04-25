#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <sstream>

int main() {
    // Arreglos estáticos con los parámetros del diseño experimental
    const std::vector<float> tasas_r = {3.90f, 3.92f, 3.95f, 3.98f, 4.00f};
    const std::vector<float> condiciones_x0 = {0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f};
    const int iteraciones = 1000; // Límite de la simulación

    // Archivo de salida para registrar las 35 trayectorias consolidadas
    std::ofstream archivo("trayectoria_float.csv");
    archivo << "ID_Exp,Iteracion,Valor\n";

    // Ejecución en bloque de los 35 experimentos independientes
    for (float r : tasas_r) {
        for (float x0 : condiciones_x0) {
            // Generación dinámica del identificador (EXP-R[valor_r]-X[valor_x0])
            std::ostringstream id_stream;
            id_stream << "EXP-R" << std::fixed << std::setprecision(2) << r
                      << "-X" << std::setprecision(1) << x0;
            std::string id_exp = id_stream.str();

            float x = x0;

            // Registro de la condición inicial (iteración 0) con máxima resolución float
            archivo << id_exp << ",0," << std::fixed << std::setprecision(9) << x << "\n";

            // Bucle principal: x_{n+1} = r * x_n * (1 - x_n)
            for (int i = 1; i <= iteraciones; ++i) {
                x = r * x * (1.0f - x);
                archivo << id_exp << "," << i << "," << std::fixed << std::setprecision(9) << x << "\n";
            }
        }
    }

    archivo.close();
    std::cout << "Simulacion en bloque con FLOAT completada (35 experimentos)." << std::endl;
    std::cout << "Se genero el archivo consolidado: trayectoria_float.csv" << std::endl;

    return 0;
}