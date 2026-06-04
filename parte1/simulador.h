#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "obstaculo.h"
#include "particula.h"

#include <fstream>
#include <map>
#include <string>
#include <vector>

class Simulador {
private:
    double ancho;
    double alto;
    std::vector<Particula> particulas;
    std::vector<Obstaculo> obstaculos;
    double tiempoActual;
    double dt;
    int pasosTotales;

public:
    Simulador(double ancho, double alto, double dt, int pasosTotales);

    void agregarParticula(const Particula& particula);
    void agregarObstaculo(const Obstaculo& obstaculo);

    void actualizar(std::map<int, std::string>& eventos);
    void resolverColisionesParedes(std::map<int, std::string>& eventos);
    void resolverColisionesObstaculos(std::map<int, std::string>& eventos);
    void resolverColisionesParticulas(std::map<int, std::string>& eventos);

    void guardarEstado(std::ofstream& archivo,
                       const std::map<int, std::string>& eventos) const;
    void guardarObstaculos(const std::string& rutaArchivo) const;
    bool ejecutar(const std::string& rutaSalida,
                  const std::string& rutaObstaculos);

    double obtenerAncho() const;
    double obtenerAlto() const;
    const std::vector<Particula>& obtenerParticulas() const;
    const std::vector<Obstaculo>& obtenerObstaculos() const;

private:
    static void agregarEvento(std::map<int, std::string>& eventos, int id,
                              const std::string& evento);
};

#endif
