cmake_minimum_required(VERSION 3.28)
project(logistic-map-precision)

set(CMAKE_CXX_STANDARD 17)

# Rutas de MSYS2/MinGW (UCRT64) para dependencias MPFR y GMP
include_directories(C:/msys64/ucrt64/include)
link_directories(C:/msys64/ucrt64/lib)

# Forzar enlace estático para portabilidad del ejecutable
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")

# Módulos de Simulación (Se separan para evitar colisiones de la función main)
add_executable(float_sim float_sim.cpp)
target_link_libraries(float_sim mpfr gmp)

add_executable(double_sim double_sim.cpp)
target_link_libraries(double_sim mpfr gmp)

add_executable(mpfr_sim mpfr_sim.cpp)
target_link_libraries(mpfr_sim mpfr gmp)

# Módulo de Análisis y Consolidación
add_executable(analisis_error analisis_error.cpp)
target_link_libraries(analisis_error mpfr gmp)