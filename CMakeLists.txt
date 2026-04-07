cmake_minimum_required(VERSION 3.28)
project(MapaLogistico)

set(CMAKE_CXX_STANDARD 17)

# --- RUTAS MANUALES PARA MSYS2 UCRT64 ---
include_directories(C:/msys64/ucrt64/include)
link_directories(C:/msys64/ucrt64/lib)

# Agrega esto para evitar conflictos de DLLs dinámicas
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")

# --- PROYECTO 1: MapaLogistico ---
# Solo incluimos main.cpp porque es el que tiene el main principal
add_executable(MapaLogistico main.cpp)
target_link_libraries(MapaLogistico mpfr gmp)

# --- PROYECTO 2: float_sim ---
# Creamos un ejecutable separado para la simulación con floats
add_executable(float_sim float_sim.cpp
        double_sim.cpp)
target_link_libraries(float_sim mpfr gmp)

# --- PROYECTO 3: double_sim ---
# Ejecutable separado para la simulacion con double
add_executable(double_sim double_sim.cpp
        mpfr_sim.cpp
        analisis_error.cpp)
target_link_libraries(double_sim mpfr gmp)

# --- PROYECTO 4: mpfr_sim ---
# Ejecutable separado para generar el conjunto de datos de control
add_executable(mpfr_sim mpfr_sim.cpp)
target_link_libraries(mpfr_sim mpfr gmp)

# --- PROYECTO 5: analisis_error ---
# Ejecutable para procesar los CSVs y calcular la perdida de informacion
add_executable(analisis_error analisis_error.cpp)
target_link_libraries(analisis_error mpfr gmp)