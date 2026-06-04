#ifndef JUGADOR_H
#define JUGADOR_H

#include "infraestructura.h"
#include "vector2d.h"

#include <string>
#include <vector>

class Jugador {
private:
    int id;
    std::string nombre;
    double vidaRepresentante;
    Vector2D posicionBase;
    std::vector<Infraestructura> infraestructuras;

public:
    Jugador();
    Jugador(int id, const std::string& nombre, double vidaRepresentante,
            const Vector2D& posicionBase);

    void agregarInfraestructura(const Infraestructura& infraestructura);
    bool tieneInfraestructuraViva() const;
    void recibirDanoRepresentante(double dano);
    bool estaDerrotado() const;

    int obtenerId() const;
    const std::string& obtenerNombre() const;
    double obtenerVidaRepresentante() const;
    const Vector2D& obtenerPosicionBase() const;

    std::vector<Infraestructura>& obtenerInfraestructuras();
    const std::vector<Infraestructura>& obtenerInfraestructuras() const;
};

#endif
