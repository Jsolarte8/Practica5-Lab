#include "simulador.h"

#include <cmath>
#include <iomanip>
#include <iostream>

Simulador::Simulador(double ancho, double alto, double dt, int pasosTotales)
    : ancho(ancho), alto(alto), tiempoActual(0.0), dt(dt),
      pasosTotales(pasosTotales) {}

void Simulador::agregarParticula(const Particula& particula) {
    particulas.push_back(particula);
}

void Simulador::agregarObstaculo(const Obstaculo& obstaculo) {
    obstaculos.push_back(obstaculo);
}

void Simulador::actualizar(std::map<int, std::string>& eventos) {
    for (Particula& particula : particulas) {
        particula.actualizar(dt);
    }

    resolverColisionesParedes(eventos);
    resolverColisionesObstaculos(eventos);
    resolverColisionesParticulas(eventos);
    tiempoActual += dt;
}

void Simulador::resolverColisionesParedes(std::map<int, std::string>& eventos) {
    for (Particula& particula : particulas) {
        const std::string evento = particula.resolverColisionPared(ancho, alto);
        if (!evento.empty()) {
            agregarEvento(eventos, particula.obtenerId(), evento);
        }
    }
}

void Simulador::resolverColisionesObstaculos(std::map<int, std::string>& eventos) {
    for (Particula& particula : particulas) {
        if (!particula.estaActiva()) {
            continue;
        }
        for (const Obstaculo& obstaculo : obstaculos) {
            const std::string evento = obstaculo.resolverColision(particula);
            if (!evento.empty()) {
                agregarEvento(eventos, particula.obtenerId(), evento);
            }
        }
    }
}

void Simulador::resolverColisionesParticulas(std::map<int, std::string>& eventos) {
    for (std::size_t i = 0; i < particulas.size(); ++i) {
        if (!particulas[i].estaActiva()) {
            continue;
        }

        for (std::size_t j = i + 1; j < particulas.size(); ++j) {
            if (!particulas[j].estaActiva() ||
                !particulas[i].colisionaConParticula(particulas[j])) {
                continue;
            }

            const double m1 = particulas[i].obtenerMasa();
            const double m2 = particulas[j].obtenerMasa();
            const double masaFinal = m1 + m2;

            const Vector2D posicionFinal =
                (particulas[i].obtenerPosicion() * m1 +
                 particulas[j].obtenerPosicion() * m2) /
                masaFinal;

            const Vector2D velocidadFinal =
                (particulas[i].obtenerVelocidad() * m1 +
                 particulas[j].obtenerVelocidad() * m2) /
                masaFinal;

            const double radioFinal = std::sqrt(
                particulas[i].obtenerRadio() * particulas[i].obtenerRadio() +
                particulas[j].obtenerRadio() * particulas[j].obtenerRadio());

            const int idFusionado = particulas[j].obtenerId();
            particulas[i].asignarMasa(masaFinal);
            particulas[i].asignarPosicion(posicionFinal);
            particulas[i].asignarVelocidad(velocidadFinal);
            particulas[i].asignarRadio(radioFinal);
            particulas[j].asignarActiva(false);

            agregarEvento(eventos, particulas[i].obtenerId(),
                          "fusion_con_particula_" + std::to_string(idFusionado));
            agregarEvento(eventos, idFusionado,
                          "fusionada_en_particula_" +
                              std::to_string(particulas[i].obtenerId()));
        }
    }
}

void Simulador::guardarEstado(std::ofstream& archivo,
                              const std::map<int, std::string>& eventos) const {
    archivo << std::fixed << std::setprecision(4);

    for (const Particula& particula : particulas) {
        const auto evento = eventos.find(particula.obtenerId());
        if (!particula.estaActiva() && evento == eventos.end()) {
            continue;
        }

        const Vector2D& pos = particula.obtenerPosicion();
        const Vector2D& vel = particula.obtenerVelocidad();

        archivo << tiempoActual << ','
                << particula.obtenerId() << ','
                << pos.x << ','
                << pos.y << ','
                << vel.x << ','
                << vel.y << ','
                << particula.obtenerMasa() << ','
                << particula.obtenerRadio() << ',';

        if (evento != eventos.end()) {
            archivo << evento->second;
        }

        archivo << '\n';
    }
}

void Simulador::guardarObstaculos(const std::string& rutaArchivo) const {
    std::ofstream archivo(rutaArchivo);
    archivo << "id,x,y,ancho,alto,e\n";
    archivo << std::fixed << std::setprecision(4);

    for (const Obstaculo& obstaculo : obstaculos) {
        archivo << obstaculo.obtenerId() << ','
                << obstaculo.obtenerPosicion().x << ','
                << obstaculo.obtenerPosicion().y << ','
                << obstaculo.obtenerAncho() << ','
                << obstaculo.obtenerAlto() << ','
                << obstaculo.obtenerRestitucion() << '\n';
    }
}

bool Simulador::ejecutar(const std::string& rutaSalida,
                         const std::string& rutaObstaculos) {
    std::ofstream archivo(rutaSalida);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo crear " << rutaSalida << '\n';
        return false;
    }

    guardarObstaculos(rutaObstaculos);

    archivo << "tiempo,id,x,y,vx,vy,masa,radio,evento\n";
    guardarEstado(archivo, std::map<int, std::string>());

    for (int paso = 0; paso < pasosTotales; ++paso) {
        std::map<int, std::string> eventos;
        actualizar(eventos);
        guardarEstado(archivo, eventos);
    }

    return true;
}

double Simulador::obtenerAncho() const {
    return ancho;
}

double Simulador::obtenerAlto() const {
    return alto;
}

const std::vector<Particula>& Simulador::obtenerParticulas() const {
    return particulas;
}

const std::vector<Obstaculo>& Simulador::obtenerObstaculos() const {
    return obstaculos;
}

void Simulador::agregarEvento(std::map<int, std::string>& eventos, int id,
                              const std::string& evento) {
    if (evento.empty()) {
        return;
    }

    auto actual = eventos.find(id);
    if (actual == eventos.end() || actual->second.empty()) {
        eventos[id] = evento;
    } else {
        actual->second += "|" + evento;
    }
}
