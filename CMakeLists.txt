cmake_minimum_required(VERSION 3.28)
project(MapaLogistico)

set(CMAKE_CXX_STANDARD 17)

include_directories(C:/msys64/ucrt64/include)
link_directories(C:/msys64/ucrt64/lib)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")

add_executable(MapaLogistico main.cpp)
target_link_libraries(MapaLogistico mpfr gmp)

add_executable(float_sim float_sim.cpp
        double_sim.cpp)
target_link_libraries(float_sim mpfr gmp)

add_executable(double_sim double_sim.cpp
        mpfr_sim.cpp
        analisis_error.cpp)
target_link_libraries(double_sim mpfr gmp)

add_executable(mpfr_sim mpfr_sim.cpp)
target_link_libraries(mpfr_sim mpfr gmp)

add_executable(analisis_error analisis_error.cpp)
target_link_libraries(analisis_error mpfr gmp)