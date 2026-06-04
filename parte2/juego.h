#ifndef JUEGO_H
#define JUEGO_H

#include "jugador.h"
#include "proyectil.h"

#include <string>

enum class EstadoJuego {
    EsperandoLanzamiento,
    ProyectilEnMovimiento,
    Finalizado
};

class Juego {
private:
    Jugador jugador1;
    Jugador jugador2;
    int turnoActual;
    Proyectil proyectilActual;
    EstadoJuego estado;
    double anchoEscenario;
    double altoEscenario;
    double dt;
    double gravedad;
    double tiempoTurno;
    double tiempoMaximoTurno;
    std::string mensaje;
    int ganador;

public:
    Juego();

    bool lanzarProyectil(double anguloGrados, double rapidezInicial);
    void actualizarSimulacion();
    void cambiarTurno();
    void verificarVictoria();

    const Jugador& obtenerJugador1() const;
    const Jugador& obtenerJugador2() const;
    const Proyectil& obtenerProyectil() const;
    EstadoJuego obtenerEstado() const;
    int obtenerTurnoActual() const;
    int obtenerGanador() const;
    const std::string& obtenerMensaje() const;
    double obtenerAncho() const;
    double obtenerAlto() const;
    double obtenerDt() const;

    Vector2D obtenerOrigenDisparoActual() const;
    Vector2D obtenerPosicionRepresentante(int idJugador) const;
    double obtenerAnchoRepresentante() const;
    double obtenerAltoRepresentante() const;

private:
    Jugador& jugadorActual();
    Jugador& rivalActual();
    const Jugador& jugadorActual() const;
    const Jugador& rivalActual() const;

    void resolverImpactosInfraestructura(Jugador& jugador);
    bool colisionaRepresentante(const Proyectil& proyectil,
                                const Jugador& jugador) const;
    double resolverImpactoRepresentante(Jugador& jugador);
    static bool circuloContraRectangulo(const Vector2D& centro, double radio,
                                        const Vector2D& rectPos,
                                        double rectAncho, double rectAlto);
    static double limitar(double valor, double minimo, double maximo);
};

#endif
