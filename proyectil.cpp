#include "proyectil.h"

#include <cmath>

namespace {
constexpr double PI = 3.14159265358979323846;
}

Proyectil::Proyectil()
    : Particula(0, Vector2D(), Vector2D(), 8.0, 8.0), dueno(0) {
    asignarActiva(false);
}

void Proyectil::lanzar(int idDueno, const Vector2D& origen, double anguloGrados,
                       double rapidezInicial) {
    dueno = idDueno;
    const double radianes = anguloGrados * PI / 180.0;
    const double direccion = (idDueno == 1) ? 1.0 : -1.0;

    asignarId(idDueno);
    asignarMasa(8.0);
    asignarRadio(8.0);
    asignarPosicion(origen);
    asignarVelocidad(Vector2D(direccion * rapidezInicial * std::cos(radianes),
                              -rapidezInicial * std::sin(radianes)));
    asignarActiva(true);
}

void Proyectil::actualizar(double dt, double gravedad) {
    if (!estaActiva()) {
        return;
    }

    Vector2D velocidad = obtenerVelocidad();
    velocidad.y += gravedad * dt;
    asignarVelocidad(velocidad);
    Particula::actualizar(dt);
}

void Proyectil::desactivar() {
    asignarActiva(false);
}

int Proyectil::obtenerDueno() const {
    return dueno;
}
