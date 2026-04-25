# Registro Visual: Divergencia y Error Numérico

Este directorio almacena las representaciones gráficas resultantes de la simulación del mapa logístico en régimen caótico ($r \approx 4.0$). Las gráficas se centran en las primeras 100 iteraciones, ventana empírica donde se observa la ruptura de la universalidad topológica debido a las limitaciones del estándar IEEE 754.

## Tipos de Gráficas

Para cada escenario experimental se generaron dos gráficos complementarios:

* **`Exp_[ID]_Divergencia.png`**: Compara la evolución del estado poblacional ($x_n$). Contrasta el límite de precisión simple (`float`, 32-bit) y doble (`double`, 64-bit) frente al conjunto de control calculado con precisión arbitraria (`MPFR`). Permite identificar visualmente la iteración de colapso numérico.
* **`Exp_[ID]_ErrorLog.png`**: Cuantifica el crecimiento del error absoluto en escala logarítmica base 10. Muestra la amplificación exponencial del error de redondeo iteración tras iteración, mitigando los valores nulos iniciales mediante el límite de resolución (cero de máquina).

## Cómo interpretar los Identificadores (ID)

Cada par de gráficas está asociado a un identificador único (ej. `Exp_1`, `Exp_15`, `Exp_35`). 

Este número corresponde a la columna **`ID_Exp`** del dataset maestro ubicado en la carpeta `results/`. Para conocer las condiciones exactas de una gráfica, busca su `ID` en el archivo de datos; este revelará la configuración específica de:
1.  **Tasa de crecimiento ($r$)**
2.  **Condición inicial ($x_0$)**
