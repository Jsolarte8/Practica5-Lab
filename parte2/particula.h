#ifndef PARTICULA_H
#define PARTICULA_H

#include "vector2d.h"

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

    virtual ~Particula() = default;

    virtual void actualizar(double dt);
    bool resolverColisionLimites(double ancho, double alto);

    int obtenerId() const;
    const Vector2D& obtenerPosicion() const;
    const Vector2D& obtenerVelocidad() const;
    double obtenerMasa() const;
    double obtenerRadio() const;
    bool estaActiva() const;

    void asignarId(int nuevoId);
    void asignarPosicion(const Vector2D& nuevaPosicion);
    void asignarVelocidad(const Vector2D& nuevaVelocidad);
    void asignarMasa(double nuevaMasa);
    void asignarRadio(double nuevoRadio);
    void asignarActiva(bool nuevoEstado);
};

#endif
