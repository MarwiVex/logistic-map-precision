#include <iostream>
#include <fstream>
#include <iomanip>

int main() {
    // Definicion de parametros del mapa logistico
    float r = 4.0f;          // Tasa de crecimiento para caos determinista
    float x = 0.1f;          // Condicion inicial (x_0). Usaremos 0.1 en todas las pruebas.
    int iteraciones = 1000;  // Limite de la simulacion

    // Archivo de salida para registrar la trayectoria
    std::ofstream archivo("trayectoria_float.csv");
    archivo << "Iteracion,Valor\n";
    
    // Guardar el valor inicial (iteracion 0) con 9 decimales (maxima resolucion de un float)
    archivo << 0 << "," << std::fixed << std::setprecision(9) << x << "\n";

    // Bucle principal: x_{n+1} = r * x_n * (1 - x_n)
    for (int i = 1; i <= iteraciones; ++i) {
        x = r * x * (1.0f - x);
        archivo << i << "," << std::fixed << std::setprecision(9) << x << "\n";
    }

    archivo.close();
    std::cout << "Simulacion con FLOAT completada." << std::endl;
    std::cout << "Se genero el archivo: trayectoria_float.csv" << std::endl;

    return 0;
}