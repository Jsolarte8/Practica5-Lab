#include "particula.h"

Particula::Particula()
    : id(0), pos(), vel(), masa(1.0), radio(1.0), activa(false) {}

Particula::Particula(int id, const Vector2D& posicion, const Vector2D& velocidad,
                     double masa, double radio)
    : id(id), pos(posicion), vel(velocidad), masa(masa), radio(radio), activa(true) {}

void Particula::actualizar(double dt) {
    if (!activa) {
        return;
    }
    pos += vel * dt;
}

bool Particula::resolverColisionLimites(double ancho, double alto) {
    if (!activa) {
        return false;
    }

    bool colision = false;

    if (pos.x - radio < 0.0) {
        pos.x = radio;
        if (vel.x < 0.0) {
            vel.x *= -1.0;
        }
        colision = true;
    } else if (pos.x + radio > ancho) {
        pos.x = ancho - radio;
        if (vel.x > 0.0) {
            vel.x *= -1.0;
        }
        colision = true;
    }

    if (pos.y - radio < 0.0) {
        pos.y = radio;
        if (vel.y < 0.0) {
            vel.y *= -1.0;
        }
        colision = true;
    } else if (pos.y + radio > alto) {
        pos.y = alto - radio;
        if (vel.y > 0.0) {
            vel.y *= -1.0;
        }
        colision = true;
    }

    return colision;
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

void Particula::asignarId(int nuevoId) {
    id = nuevoId;
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
