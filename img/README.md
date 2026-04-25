# Registro Visual: Divergencia y Error Numérico

Este directorio almacena las representaciones gráficas resultantes de la simulación del mapa logístico en régimen caótico ($r \approx 4.0$). Las gráficas se centran en las primeras 100 iteraciones, ventana empírica donde se observa la ruptura de la universalidad topológica debido a las limitaciones del estándar IEEE 754.

## Tipos de Gráficas

Para cada escenario experimental se generaron dos gráficos complementarios:

* **`Divergencia_EXP-R[VALOR]-X[VALOR].png`**: Compara la evolución del estado poblacional ($x_n$). Contrasta el límite de precisión simple (`float`, 32-bit) y doble (`double`, 64-bit) frente al conjunto de control calculado con precisión arbitraria (`MPFR`). Permite identificar visualmente la iteración de colapso numérico.
* **`Error_EXP-R[VALOR]-X[VALOR].png`**: Cuantifica el crecimiento del error absoluto en escala logarítmica base 10. Muestra la amplificación exponencial del error de redondeo iteración tras iteración, mitigando los valores nulos iniciales mediante el límite de resolución (cero de máquina).

## Estructura de los Identificadores (ID)

A diferencia de un índice numérico arbitrario, los nombres de los archivos están codificados para reflejar directamente los parámetros de control del sistema dinámico:

**Formato:** `[Tipo]_EXP-R[Tasa]-X[Condición]`

1. **R (Tasa de crecimiento):** El valor inmediatamente posterior a la `R` indica el parámetro de control $r$ utilizado en la ecuación $x_{n+1} = rx_n(1-x_n)$. 
   * *Ejemplo:* `R4.00` representa un régimen de caos total.
2. **X (Condición inicial):** El valor posterior a la `X` indica el valor de $x_0$ con el que inició la semilla del experimento.
   * *Ejemplo:* `X0.1` representa una población inicial del 10% del máximo posible.

De este modo, un archivo nombrado `Divergencia_EXP-R3.92-X0.2.png` permite identificar rápidamente que la simulación corresponde a una tasa de $3.92$ con una semilla inicial de $0.2$.
