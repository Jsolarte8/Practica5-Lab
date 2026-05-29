#ifndef PARTICULA_H
#define PARTICULA_H

#include "vector2d.h"

#include <string>

class Particula {
private:
    int id;
    Vector2D pos;
    Vector2D vel;
    double masa;
    double radio;
    bool activa;

public:
    Particula();
    Particula(int id, const Vector2D& posicion, const Vector2D& velocidad,
              double masa, double radio);

    void actualizar(double dt);

    bool colisionaConPared(double ancho, double alto) const;
    std::string resolverColisionPared(double ancho, double alto);
    bool colisionaConParticula(const Particula& otra) const;

    int obtenerId() const;
    const Vector2D& obtenerPosicion() const;
    const Vector2D& obtenerVelocidad() const;
    double obtenerMasa() const;
    double obtenerRadio() const;
    bool estaActiva() const;

    void asignarPosicion(const Vector2D& nuevaPosicion);
    void asignarVelocidad(const Vector2D& nuevaVelocidad);
    void asignarMasa(double nuevaMasa);
    void asignarRadio(double nuevoRadio);
    void asignarActiva(bool nuevoEstado);
};

#endif
