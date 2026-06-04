#ifndef PROYECTIL_H
#define PROYECTIL_H

#include "particula.h"

class Proyectil : public Particula {
private:
    int dueno;

public:
    Proyectil();

    void lanzar(int idDueno, const Vector2D& origen, double anguloGrados,
                double rapidezInicial);
    void actualizar(double dt, double gravedad);
    void desactivar();

    int obtenerDueno() const;
};

#endif
