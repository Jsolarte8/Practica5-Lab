#include "juego.h"

#include <algorithm>
#include <iomanip>
#include <sstream>

namespace {
constexpr double FACTOR_DANO_INFRAESTRUCTURA = 0.05;
constexpr double FACTOR_DANO_REPRESENTANTE = 0.06;
constexpr double ANCHO_REPRESENTANTE = 40.0;
constexpr double ALTO_REPRESENTANTE = 80.0;
}

Juego::Juego()
    : jugador1(1, "Jugador 1", 100.0, Vector2D(60.0, 560.0)),
      jugador2(2, "Jugador 2", 100.0, Vector2D(800.0, 560.0)),
      turnoActual(1), proyectilActual(),
      estado(EstadoJuego::EsperandoLanzamiento), anchoEscenario(900.0),
      altoEscenario(700.0), dt(0.025), gravedad(95.0), tiempoTurno(0.0),
      tiempoMaximoTurno(10.0), mensaje("Turno del Jugador 1"), ganador(0) {
    jugador1.agregarInfraestructura(
        Infraestructura(1, 1, Vector2D(150.0, 548.0), 30.0, 92.0, 90.0, 0.55));
    jugador1.agregarInfraestructura(
        Infraestructura(2, 1, Vector2D(205.0, 515.0), 34.0, 125.0, 110.0, 0.55));
    jugador1.agregarInfraestructura(
        Infraestructura(3, 1, Vector2D(260.0, 575.0), 45.0, 65.0, 80.0, 0.60));

    jugador2.agregarInfraestructura(
        Infraestructura(4, 2, Vector2D(720.0, 548.0), 30.0, 92.0, 90.0, 0.55));
    jugador2.agregarInfraestructura(
        Infraestructura(5, 2, Vector2D(660.0, 515.0), 34.0, 125.0, 110.0, 0.55));
    jugador2.agregarInfraestructura(
        Infraestructura(6, 2, Vector2D(595.0, 575.0), 45.0, 65.0, 80.0, 0.60));
}

bool Juego::lanzarProyectil(double anguloGrados, double rapidezInicial) {
    if (estado != EstadoJuego::EsperandoLanzamiento) {
        return false;
    }

    proyectilActual.lanzar(turnoActual, obtenerOrigenDisparoActual(),
                           anguloGrados, rapidezInicial);
    tiempoTurno = 0.0;
    estado = EstadoJuego::ProyectilEnMovimiento;
    mensaje = "Proyectil en movimiento";
    return true;
}

void Juego::actualizarSimulacion() {
    if (estado != EstadoJuego::ProyectilEnMovimiento) {
        return;
    }

    proyectilActual.actualizar(dt, gravedad);
    if (proyectilActual.resolverColisionLimites(anchoEscenario, altoEscenario)) {
        mensaje = "Rebote elastico contra limite";
    }

    resolverImpactosInfraestructura(jugador1);
    resolverImpactosInfraestructura(jugador2);

    Jugador& rival = rivalActual();
    if (!rival.tieneInfraestructuraViva() &&
        colisionaRepresentante(proyectilActual, rival)) {
        resolverImpactoRepresentante(rival);
        verificarVictoria();
    }

    tiempoTurno += dt;
    if (estado == EstadoJuego::ProyectilEnMovimiento &&
        (!proyectilActual.estaActiva() || tiempoTurno >= tiempoMaximoTurno ||
         proyectilActual.obtenerVelocidad().magnitud() < 12.0)) {
        cambiarTurno();
    }
}

void Juego::cambiarTurno() {
    if (estado == EstadoJuego::Finalizado) {
        return;
    }

    proyectilActual.desactivar();
    turnoActual = (turnoActual == 1) ? 2 : 1;
    estado = EstadoJuego::EsperandoLanzamiento;
    mensaje = "Turno del " + jugadorActual().obtenerNombre();
}

void Juego::verificarVictoria() {
    if (jugador1.estaDerrotado()) {
        ganador = 2;
        estado = EstadoJuego::Finalizado;
        proyectilActual.desactivar();
        mensaje = "Gana Jugador 2";
    } else if (jugador2.estaDerrotado()) {
        ganador = 1;
        estado = EstadoJuego::Finalizado;
        proyectilActual.desactivar();
        mensaje = "Gana Jugador 1";
    }
}

const Jugador& Juego::obtenerJugador1() const {
    return jugador1;
}

const Jugador& Juego::obtenerJugador2() const {
    return jugador2;
}

const Proyectil& Juego::obtenerProyectil() const {
    return proyectilActual;
}

EstadoJuego Juego::obtenerEstado() const {
    return estado;
}

int Juego::obtenerTurnoActual() const {
    return turnoActual;
}

int Juego::obtenerGanador() const {
    return ganador;
}

const std::string& Juego::obtenerMensaje() const {
    return mensaje;
}

double Juego::obtenerAncho() const {
    return anchoEscenario;
}

double Juego::obtenerAlto() const {
    return altoEscenario;
}

double Juego::obtenerDt() const {
    return dt;
}

Vector2D Juego::obtenerOrigenDisparoActual() const {
    const Jugador& jugador = jugadorActual();
    const Vector2D base = jugador.obtenerPosicionBase();
    if (jugador.obtenerId() == 1) {
        return Vector2D(base.x + ANCHO_REPRESENTANTE + 10.0, base.y + 25.0);
    }
    return Vector2D(base.x - 10.0, base.y + 25.0);
}

Vector2D Juego::obtenerPosicionRepresentante(int idJugador) const {
    return (idJugador == 1) ? jugador1.obtenerPosicionBase()
                            : jugador2.obtenerPosicionBase();
}

double Juego::obtenerAnchoRepresentante() const {
    return ANCHO_REPRESENTANTE;
}

double Juego::obtenerAltoRepresentante() const {
    return ALTO_REPRESENTANTE;
}

Jugador& Juego::jugadorActual() {
    return (turnoActual == 1) ? jugador1 : jugador2;
}

Jugador& Juego::rivalActual() {
    return (turnoActual == 1) ? jugador2 : jugador1;
}

const Jugador& Juego::jugadorActual() const {
    return (turnoActual == 1) ? jugador1 : jugador2;
}

const Jugador& Juego::rivalActual() const {
    return (turnoActual == 1) ? jugador2 : jugador1;
}

void Juego::resolverImpactosInfraestructura(Jugador& jugador) {
    for (Infraestructura& infraestructura : jugador.obtenerInfraestructuras()) {
        const bool esRival = infraestructura.obtenerDueno() != turnoActual;
        const double dano = infraestructura.resolverColision(
            proyectilActual, FACTOR_DANO_INFRAESTRUCTURA, esRival);

        if (dano > 0.0) {
            std::ostringstream salida;
            salida << "Impacto a infraestructura " << infraestructura.obtenerId()
                   << " | dano: " << std::fixed << std::setprecision(1) << dano;
            if (infraestructura.estaDestruida()) {
                salida << " | destruida";
            }
            mensaje = salida.str();
        }
    }
}

bool Juego::colisionaRepresentante(const Proyectil& proyectil,
                                   const Jugador& jugador) const {
    return circuloContraRectangulo(proyectil.obtenerPosicion(),
                                   proyectil.obtenerRadio(),
                                   jugador.obtenerPosicionBase(),
                                   ANCHO_REPRESENTANTE, ALTO_REPRESENTANTE);
}

double Juego::resolverImpactoRepresentante(Jugador& jugador) {
    const double dano = FACTOR_DANO_REPRESENTANTE *
                        proyectilActual.obtenerMasa() *
                        proyectilActual.obtenerVelocidad().magnitud();
    jugador.recibirDanoRepresentante(dano);
    proyectilActual.desactivar();

    std::ostringstream salida;
    salida << "Impacto al representante de " << jugador.obtenerNombre()
           << " | dano: " << std::fixed << std::setprecision(1) << dano;
    mensaje = salida.str();
    return dano;
}

bool Juego::circuloContraRectangulo(const Vector2D& centro, double radio,
                                    const Vector2D& rectPos, double rectAncho,
                                    double rectAlto) {
    const double cercanoX = limitar(centro.x, rectPos.x, rectPos.x + rectAncho);
    const double cercanoY = limitar(centro.y, rectPos.y, rectPos.y + rectAlto);
    const double dx = centro.x - cercanoX;
    const double dy = centro.y - cercanoY;
    return dx * dx + dy * dy <= radio * radio;
}

double Juego::limitar(double valor, double minimo, double maximo) {
    return std::max(minimo, std::min(valor, maximo));
}
