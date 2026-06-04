#ifndef OBSTACULO_H
#define OBSTACULO_H

#include "particula.h"
#include "vector2d.h"

#include <string>

enum class LadoImpacto {
    Ninguno,
    Izquierda,
    Derecha,
    Arriba,
    Abajo
};

class Obstaculo {
private:
    int id;
    Vector2D pos;
    double ancho;
    double alto;
    double restitucion;

public:
    Obstaculo();
    Obstaculo(int id, const Vector2D& posicion, double ancho, double alto,
              double coeficienteRestitucion);

    bool colisionaCon(const Particula& particula) const;
    LadoImpacto determinarLadoImpacto(const Particula& particula) const;
    std::string resolverColision(Particula& particula) const;

    int obtenerId() const;
    const Vector2D& obtenerPosicion() const;
    double obtenerAncho() const;
    double obtenerAlto() const;
    double obtenerRestitucion() const;

private:
    static double limitar(double valor, double minimo, double maximo);
    static std::string nombreLado(LadoImpacto lado);
};

#endif
