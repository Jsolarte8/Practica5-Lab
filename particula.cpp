#include "particula.h"

#include <cmath>
#include <sstream>

Particula::Particula()
    : id(0), pos(), vel(), masa(1.0), radio(1.0), activa(true) {}

Particula::Particula(int id, const Vector2D& posicion, const Vector2D& velocidad,
                     double masa, double radio)
    : id(id), pos(posicion), vel(velocidad), masa(masa), radio(radio), activa(true) {}

void Particula::actualizar(double dt) {
    if (!activa) {
        return;
    }
    pos += vel * dt;
}

bool Particula::colisionaConPared(double ancho, double alto) const {
    if (!activa) {
        return false;
    }
    return (pos.x - radio <= 0.0 || pos.x + radio >= ancho ||
            pos.y - radio <= 0.0 || pos.y + radio >= alto);
}

std::string Particula::resolverColisionPared(double ancho, double alto) {
    if (!activa) {
        return "";
    }

    std::ostringstream evento;
    bool huboColision = false;

    if (pos.x - radio < 0.0) {
        pos.x = radio;
        if (vel.x < 0.0) {
            vel.x *= -1.0;
        }
        evento << "pared_izquierda";
        huboColision = true;
    } else if (pos.x + radio > ancho) {
        pos.x = ancho - radio;
        if (vel.x > 0.0) {
            vel.x *= -1.0;
        }
        evento << "pared_derecha";
        huboColision = true;
    }

    if (pos.y - radio < 0.0) {
        pos.y = radio;
        if (vel.y < 0.0) {
            vel.y *= -1.0;
        }
        if (huboColision) {
            evento << "|";
        }
        evento << "pared_superior";
        huboColision = true;
    } else if (pos.y + radio > alto) {
        pos.y = alto - radio;
        if (vel.y > 0.0) {
            vel.y *= -1.0;
        }
        if (huboColision) {
            evento << "|";
        }
        evento << "pared_inferior";
        huboColision = true;
    }

    return evento.str();
}

bool Particula::colisionaConParticula(const Particula& otra) const {
    if (!activa || !otra.activa || id == otra.id) {
        return false;
    }
    const double distancia2 = (pos - otra.pos).magnitudCuadrada();
    const double radios = radio + otra.radio;
    return distancia2 <= radios * radios;
}

int Particula::obtenerId() const {
    return id;
}

const Vector2D& Particula::obtenerPosicion() const {
    return pos;
}

const Vector2D& Particula::obtenerVelocidad() const {
    return vel;
}

double Particula::obtenerMasa() const {
    return masa;
}

double Particula::obtenerRadio() const {
    return radio;
}

bool Particula::estaActiva() const {
    return activa;
}

void Particula::asignarPosicion(const Vector2D& nuevaPosicion) {
    pos = nuevaPosicion;
}

void Particula::asignarVelocidad(const Vector2D& nuevaVelocidad) {
    vel = nuevaVelocidad;
}

void Particula::asignarMasa(double nuevaMasa) {
    masa = nuevaMasa;
}

void Particula::asignarRadio(double nuevoRadio) {
    radio = nuevoRadio;
}

void Particula::asignarActiva(bool nuevoEstado) {
    activa = nuevoEstado;
}
