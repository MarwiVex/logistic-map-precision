#include <iostream>
#include <fstream>
#include <iomanip>

int main() {
    // Definicion de parametros utilizando precision doble (64 bits)
    double r = 4.0;          // Tasa de crecimiento
    double x = 0.1;          // Condicion inicial
    int iteraciones = 1000;  // Limite de la simulacion

    // Archivo de salida para registrar la trayectoria
    std::ofstream archivo("trayectoria_double.csv");
    archivo << "Iteracion,Valor\n";
    
    // Guardar el valor inicial con 17 decimales de resolucion
    archivo << 0 << "," << std::fixed << std::setprecision(17) << x << "\n";

    // Bucle principal del mapa logistico
    for (int i = 1; i <= iteraciones; ++i) {
        x = r * x * (1.0 - x);
        archivo << i << "," << std::fixed << std::setprecision(17) << x << "\n";
    }

    archivo.close();
    std::cout << "Simulacion con DOUBLE completada." << std::endl;
    std::cout << "Se genero el archivo: trayectoria_double.csv" << std::endl;

    return 0;
}
