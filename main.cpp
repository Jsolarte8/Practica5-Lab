#include "obstaculo.h"
#include "particula.h"
#include "simulador.h"
#include "vector2d.h"

#include <iostream>
#include <string>

int main() {
    const double anchoCaja = 900.0;
    const double altoCaja = 700.0;
    const double dt = 0.02;
    const int pasos = 3000;

    Simulador simulador(anchoCaja, altoCaja, dt, pasos);

    simulador.agregarParticula(Particula(1, Vector2D(90.0, 130.0),
                                         Vector2D(150.0, 95.0), 3.0, 16.0));
    simulador.agregarParticula(Particula(2, Vector2D(790.0, 145.0),
                                         Vector2D(-135.0, 85.0), 4.0, 20.0));
    simulador.agregarParticula(Particula(3, Vector2D(180.0, 610.0),
                                         Vector2D(110.0, -120.0), 2.5, 15.0));
    simulador.agregarParticula(Particula(4, Vector2D(720.0, 560.0),
                                         Vector2D(-95.0, -105.0), 5.0, 23.0));

    simulador.agregarObstaculo(Obstaculo(1, Vector2D(250.0, 180.0),
                                         70.0, 70.0, 0.6));
    simulador.agregarObstaculo(Obstaculo(2, Vector2D(560.0, 160.0),
                                         85.0, 85.0, 0.55));
    simulador.agregarObstaculo(Obstaculo(3, Vector2D(390.0, 420.0),
                                         80.0, 80.0, 0.65));
    simulador.agregarObstaculo(Obstaculo(4, Vector2D(670.0, 430.0),
                                         75.0, 75.0, 0.6));

    const std::string archivoSalida = "salida_simulacion.txt";
    const std::string archivoObstaculos = "obstaculos_simulacion.txt";

    if (!simulador.ejecutar(archivoSalida, archivoObstaculos)) {
        return 1;
    }

    std::cout << "Simulacion completada correctamente.\n";
    std::cout << "Datos guardados en " << archivoSalida << '\n';
    std::cout << "Obstaculos guardados en " << archivoObstaculos << '\n';
    std::cout << "Grafique con: python python/graficar_simulacion.py\n";

    return 0;
}
