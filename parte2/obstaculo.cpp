#include "obstaculo.h"

#include <algorithm>
#include <cmath>
#include <sstream>

Obstaculo::Obstaculo()
    : id(0), pos(), ancho(10.0), alto(10.0), restitucion(0.6) {}

Obstaculo::Obstaculo(int id, const Vector2D& posicion, double ancho, double alto,
                     double coeficienteRestitucion)
    : id(id), pos(posicion), ancho(ancho), alto(alto),
      restitucion(coeficienteRestitucion) {}

bool Obstaculo::colisionaCon(const Particula& particula) const {
    if (!particula.estaActiva()) {
        return false;
    }

    const Vector2D& centro = particula.obtenerPosicion();
    const double cercanoX = limitar(centro.x, pos.x, pos.x + ancho);
    const double cercanoY = limitar(centro.y, pos.y, pos.y + alto);
    const double dx = centro.x - cercanoX;
    const double dy = centro.y - cercanoY;
    const double r = particula.obtenerRadio();

    return dx * dx + dy * dy <= r * r;
}

LadoImpacto Obstaculo::determinarLadoImpacto(const Particula& particula) const {
    const Vector2D& centro = particula.obtenerPosicion();
    const double r = particula.obtenerRadio();

    const double penetracionIzquierda = (centro.x + r) - pos.x;
    const double penetracionDerecha = (pos.x + ancho) - (centro.x - r);
    const double penetracionArriba = (centro.y + r) - pos.y;
    const double penetracionAbajo = (pos.y + alto) - (centro.y - r);

    double menor = penetracionIzquierda;
    LadoImpacto lado = LadoImpacto::Izquierda;

    if (penetracionDerecha < menor) {
        menor = penetracionDerecha;
        lado = LadoImpacto::Derecha;
    }
    if (penetracionArriba < menor) {
        menor = penetracionArriba;
        lado = LadoImpacto::Arriba;
    }
    if (penetracionAbajo < menor) {
        lado = LadoImpacto::Abajo;
    }

    return lado;
}

std::string Obstaculo::resolverColision(Particula& particula) const {
    if (!colisionaCon(particula)) {
        return "";
    }

    const LadoImpacto lado = determinarLadoImpacto(particula);
    Vector2D posicion = particula.obtenerPosicion();
    Vector2D velocidad = particula.obtenerVelocidad();
    const double r = particula.obtenerRadio();

    switch (lado) {
    case LadoImpacto::Izquierda:
        posicion.x = pos.x - r;
        if (velocidad.x > 0.0) {
            velocidad.x = -restitucion * velocidad.x;
        } else {
            velocidad.x *= -restitucion;
        }
        break;
    case LadoImpacto::Derecha:
        posicion.x = pos.x + ancho + r;
        if (velocidad.x < 0.0) {
            velocidad.x = -restitucion * velocidad.x;
        } else {
            velocidad.x *= -restitucion;
        }
        break;
    case LadoImpacto::Arriba:
        posicion.y = pos.y - r;
        if (velocidad.y > 0.0) {
            velocidad.y = -restitucion * velocidad.y;
        } else {
            velocidad.y *= -restitucion;
        }
        break;
    case LadoImpacto::Abajo:
        posicion.y = pos.y + alto + r;
        if (velocidad.y < 0.0) {
            velocidad.y = -restitucion * velocidad.y;
        } else {
            velocidad.y *= -restitucion;
        }
        break;
    case LadoImpacto::Ninguno:
        break;
    }

    particula.asignarPosicion(posicion);
    particula.asignarVelocidad(velocidad);

    std::ostringstream evento;
    evento << "obstaculo_" << id << "_" << nombreLado(lado);
    return evento.str();
}

int Obstaculo::obtenerId() const {
    return id;
}

const Vector2D& Obstaculo::obtenerPosicion() const {
    return pos;
}

double Obstaculo::obtenerAncho() const {
    return ancho;
}

double Obstaculo::obtenerAlto() const {
    return alto;
}

double Obstaculo::obtenerRestitucion() const {
    return restitucion;
}

double Obstaculo::limitar(double valor, double minimo, double maximo) {
    return std::max(minimo, std::min(valor, maximo));
}

std::string Obstaculo::nombreLado(LadoImpacto lado) {
    switch (lado) {
    case LadoImpacto::Izquierda:
        return "izquierda";
    case LadoImpacto::Derecha:
        return "derecha";
    case LadoImpacto::Arriba:
        return "arriba";
    case LadoImpacto::Abajo:
        return "abajo";
    case LadoImpacto::Ninguno:
        return "ninguno";
    }
    return "ninguno";
}
