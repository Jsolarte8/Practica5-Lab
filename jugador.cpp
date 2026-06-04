#include "jugador.h"

Jugador::Jugador()
    : id(0), nombre("Jugador"), vidaRepresentante(100.0), posicionBase() {}

Jugador::Jugador(int id, const std::string& nombre, double vidaRepresentante,
                 const Vector2D& posicionBase)
    : id(id), nombre(nombre), vidaRepresentante(vidaRepresentante),
      posicionBase(posicionBase) {}

void Jugador::agregarInfraestructura(const Infraestructura& infraestructura) {
    infraestructuras.push_back(infraestructura);
}

bool Jugador::tieneInfraestructuraViva() const {
    for (const Infraestructura& infraestructura : infraestructuras) {
        if (!infraestructura.estaDestruida()) {
            return true;
        }
    }
    return false;
}

void Jugador::recibirDanoRepresentante(double dano) {
    vidaRepresentante -= dano;
    if (vidaRepresentante < 0.0) {
        vidaRepresentante = 0.0;
    }
}

bool Jugador::estaDerrotado() const {
    return vidaRepresentante <= 0.0;
}

int Jugador::obtenerId() const {
    return id;
}

const std::string& Jugador::obtenerNombre() const {
    return nombre;
}

double Jugador::obtenerVidaRepresentante() const {
    return vidaRepresentante;
}

const Vector2D& Jugador::obtenerPosicionBase() const {
    return posicionBase;
}

std::vector<Infraestructura>& Jugador::obtenerInfraestructuras() {
    return infraestructuras;
}

const std::vector<Infraestructura>& Jugador::obtenerInfraestructuras() const {
    return infraestructuras;
}
