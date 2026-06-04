#ifndef INFRAESTRUCTURA_H
#define INFRAESTRUCTURA_H

#include "proyectil.h"
#include "vector2d.h"

enum class LadoInfraestructura {
    Ninguno,
    Izquierda,
    Derecha,
    Arriba,
    Abajo
};

class Infraestructura {
private:
    int id;
    int dueno;
    Vector2D pos;
    double ancho;
    double alto;
    double resistencia;
    double resistenciaInicial;
    double restitucion;

public:
    Infraestructura();
    Infraestructura(int id, int dueno, const Vector2D& posicion, double ancho,
                    double alto, double resistencia, double restitucion);

    bool colisionaCon(const Proyectil& proyectil) const;
    double resolverColision(Proyectil& proyectil, double factorDano,
                            bool aplicarDano);
    void recibirDano(double dano);
    bool estaDestruida() const;

    int obtenerId() const;
    int obtenerDueno() const;
    const Vector2D& obtenerPosicion() const;
    double obtenerAncho() const;
    double obtenerAlto() const;
    double obtenerResistencia() const;
    double obtenerResistenciaInicial() const;
    double obtenerRestitucion() const;

private:
    LadoInfraestructura determinarLadoImpacto(const Proyectil& proyectil) const;
    static double limitar(double valor, double minimo, double maximo);
};

#endif
