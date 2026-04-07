#include <iostream>
#include <fstream>
#include <mpfr.h>

int main() {
    // Establecer la precision global a 4096 bits.
    // El mapa logistico en caos pierde aprox 1 bit de resolucion por iteracion.
    // Con 4096 bits, garantizamos exactitud total en el umbral de 1000 iteraciones.
    mpfr_set_default_prec(4096);

    // Declaracion e inicializacion de variables MPFR
    mpfr_t r, x, temp;
    mpfr_init(r);
    mpfr_init(x);
    mpfr_init(temp);

    // Asignacion de parametros iniciales con redondeo estricto
    mpfr_set_d(r, 4.0, MPFR_RNDN); // Tasa de crecimiento
    mpfr_set_d(x, 0.1, MPFR_RNDN); // Condicion inicial

    // Preparacion del archivo de salida
    std::ofstream archivo("trayectoria_mpfr.csv");
    archivo << "Iteracion,Valor\n";

    // Buffer para almacenar la representacion en texto del numero (50 decimales)
    char buffer[100];

    // Guardar el valor en la iteracion 0
    mpfr_snprintf(buffer, sizeof(buffer), "%.50Rf", x);
    archivo << 0 << "," << buffer << "\n";

    // Bucle principal: x_{n+1} = r * x_n * (1 - x_n)
    for (int i = 1; i <= 1000; ++i) {
        // Desglose de la ecuacion en pasos para MPFR
        mpfr_ui_sub(temp, 1, x, MPFR_RNDN); // temp = 1 - x
        mpfr_mul(x, x, temp, MPFR_RNDN);    // x = x * temp
        mpfr_mul(x, x, r, MPFR_RNDN);       // x = x * r

        // Formatear el resultado a 50 decimales para el conjunto de control
        mpfr_snprintf(buffer, sizeof(buffer), "%.50Rf", x);
        archivo << i << "," << buffer << "\n";
    }

    archivo.close();

    // Liberar la memoria asignada a los tipos dinamicos
    mpfr_clear(r);
    mpfr_clear(x);
    mpfr_clear(temp);

    std::cout << "Simulacion con MPFR (Control) completada." << std::endl;
    std::cout << "Se genero el archivo: trayectoria_mpfr.csv" << std::endl;

    return 0;
}