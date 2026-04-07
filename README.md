# Análisis de Precisión en las Trayectorias del Mapa Logístico

Este repositorio contiene la implementación en C++ y el análisis de datos empíricos para cuantificar la pérdida de precisión en la simulación del mapa logístico bajo un régimen de caos determinista.

Se estudia el comportamiento del mapa logístico, definido por la ecuación:
$x_{n+1} = rx_n(1-x_n)$
utilizando el parámetro $r = 4.0$ a lo largo de 1000 iteraciones. El objetivo es contrastar la divergencia de implementaciones estándar en coma flotante frente a un control de precisión arbitraria.

## Stack Tecnológico y Dependencias
* **Lenguaje:** C++ (Estándar C++17/20)
* **Entorno:** MinGW, CMake
* **Bibliotecas:** GNU MPFR (4096 bits) y GMP (enlazadas estáticamente)
* **Análisis de datos:** Excel, CSV

## Resultados Clave

Las simulaciones numéricas demostraron el "Efecto Mariposa" y la sensibilidad a las condiciones iniciales:
1.  **Precisión Simple (float 32-bit):** La trayectoria diverge totalmente de la referencia matemática real cerca de la iteración 23.
2.  **Precisión Doble (double 64-bit):** Retrasa el colapso numérico, divergiendo cerca de la iteración 52.
3.  **Análisis Logarítmico:** Se observó un crecimiento exponencial del error, validando la pérdida de información progresiva característica de los sistemas dinámicos caóticos.

## Estructura de Archivos
* simulation: Algoritmos de generación de trayectorias.
* analisis_error.cpp: Script para el cálculo de divergencias y errores relativos.
* resultados_comparacion.csv: Dataset consolidado con 1000 iteraciones.

El proyecto requiere las librerías MPFR y GMP. La forma más robusta de instalarlas en Windows es mediante MSYS2:

1. Descarga e instala [MSYS2](https://www.msys2.org/).
2. Abre la terminal de MSYS2 UCRT64 y ejecuta los siguientes comandos para instalar el compilador y las librerías matemáticas:
   ```bash
   pacman -S mingw-w64-ucrt-x86_64-gcc
   pacman -S mingw-w64-ucrt-x86_64-cmake
   pacman -S mingw-w64-ucrt-x86_64-mpfr
   pacman -S mingw-w64-ucrt-x86_64-gmp
