#include "mainwindow.h"

#include <QBrush>
#include <QColor>
#include <QFormLayout>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QHBoxLayout>
#include <QPen>
#include <QPainter>
#include <QStringList>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), escena(new QGraphicsScene(this)),
      vista(new QGraphicsView(escena, this)), temporizador(new QTimer(this)),
      anguloSpin(new QDoubleSpinBox(this)),
      velocidadSpin(new QDoubleSpinBox(this)),
      lanzarBoton(new QPushButton("Lanzar", this)),
      turnoLabel(new QLabel(this)), estadoLabel(new QLabel(this)),
      vida1Label(new QLabel(this)), vida2Label(new QLabel(this)),
      infra1Label(new QLabel(this)), infra2Label(new QLabel(this)) {
    setWindowTitle("Practica 5 - Juego por turnos");

    escena->setSceneRect(0, 0, juego.obtenerAncho(), juego.obtenerAlto());
    vista->setRenderHint(QPainter::Antialiasing);
    vista->setFixedSize(static_cast<int>(juego.obtenerAncho()) + 24,
                        static_cast<int>(juego.obtenerAlto()) + 24);

    anguloSpin->setRange(5.0, 85.0);
    anguloSpin->setValue(45.0);
    anguloSpin->setSuffix(" deg");

    velocidadSpin->setRange(40.0, 220.0);
    velocidadSpin->setValue(130.0);
    velocidadSpin->setSuffix(" px/s");

    QWidget* panel = new QWidget(this);
    QVBoxLayout* panelLayout = new QVBoxLayout(panel);
    QFormLayout* controlesLayout = new QFormLayout();
    controlesLayout->addRow("Angulo", anguloSpin);
    controlesLayout->addRow("Velocidad", velocidadSpin);

    panelLayout->addWidget(turnoLabel);
    panelLayout->addWidget(estadoLabel);
    panelLayout->addSpacing(12);
    panelLayout->addLayout(controlesLayout);
    panelLayout->addWidget(lanzarBoton);
    panelLayout->addSpacing(12);
    panelLayout->addWidget(vida1Label);
    panelLayout->addWidget(infra1Label);
    panelLayout->addSpacing(8);
    panelLayout->addWidget(vida2Label);
    panelLayout->addWidget(infra2Label);
    panelLayout->addStretch();
    panel->setFixedWidth(260);

    QWidget* central = new QWidget(this);
    QHBoxLayout* layoutPrincipal = new QHBoxLayout(central);
    layoutPrincipal->addWidget(vista);
    layoutPrincipal->addWidget(panel);
    setCentralWidget(central);

    connect(lanzarBoton, &QPushButton::clicked, this, &MainWindow::lanzar);
    connect(temporizador, &QTimer::timeout, this, &MainWindow::actualizarFrame);

    temporizador->start(25);
    dibujarEscenario();
    actualizarPanel();
}

void MainWindow::lanzar() {
    if (juego.lanzarProyectil(anguloSpin->value(), velocidadSpin->value())) {
        lanzarBoton->setEnabled(false);
    }
    actualizarPanel();
}

void MainWindow::actualizarFrame() {
    juego.actualizarSimulacion();
    dibujarEscenario();
    actualizarPanel();
}

void MainWindow::dibujarEscenario() {
    escena->clear();

    escena->addRect(0, 0, juego.obtenerAncho(), juego.obtenerAlto(),
                    QPen(QColor("#263238"), 2), QBrush(QColor("#eef3f0")));
    escena->addLine(0, 640, juego.obtenerAncho(), 640, QPen(QColor("#607d6d"), 2));

    dibujarJugador(juego.obtenerJugador1(), QColor("#2f80ed"), QColor("#85b7ff"));
    dibujarJugador(juego.obtenerJugador2(), QColor("#c0392b"), QColor("#f09b91"));

    const Proyectil& proyectil = juego.obtenerProyectil();
    if (proyectil.estaActiva()) {
        const Vector2D& p = proyectil.obtenerPosicion();
        const double r = proyectil.obtenerRadio();
        escena->addEllipse(p.x - r, p.y - r, 2.0 * r, 2.0 * r,
                           QPen(QColor("#222222"), 1), QBrush(QColor("#ffd43b")));
    }
}

void MainWindow::actualizarPanel() {
    turnoLabel->setText(QString("Turno: Jugador %1").arg(juego.obtenerTurnoActual()));
    estadoLabel->setText(QString::fromStdString(juego.obtenerMensaje()));
    vida1Label->setText(
        QString("Vida J1: %1").arg(juego.obtenerJugador1().obtenerVidaRepresentante(), 0, 'f', 1));
    vida2Label->setText(
        QString("Vida J2: %1").arg(juego.obtenerJugador2().obtenerVidaRepresentante(), 0, 'f', 1));
    infra1Label->setText(resumenInfraestructura(juego.obtenerJugador1()));
    infra2Label->setText(resumenInfraestructura(juego.obtenerJugador2()));

    lanzarBoton->setEnabled(juego.obtenerEstado() == EstadoJuego::EsperandoLanzamiento);
    if (juego.obtenerEstado() == EstadoJuego::Finalizado) {
        lanzarBoton->setEnabled(false);
    }
}

QString MainWindow::resumenInfraestructura(const Jugador& jugador) const {
    QStringList partes;
    for (const Infraestructura& infraestructura : jugador.obtenerInfraestructuras()) {
        partes << QString("I%1:%2")
                      .arg(infraestructura.obtenerId())
                      .arg(infraestructura.obtenerResistencia(), 0, 'f', 0);
    }
    return QString("Infra %1: %2")
        .arg(jugador.obtenerId())
        .arg(partes.join(" | "));
}

void MainWindow::dibujarJugador(const Jugador& jugador, const QColor& colorBase,
                                const QColor& colorInfra) {
    const Vector2D representante = juego.obtenerPosicionRepresentante(jugador.obtenerId());
    escena->addRect(representante.x, representante.y,
                    juego.obtenerAnchoRepresentante(),
                    juego.obtenerAltoRepresentante(),
                    QPen(QColor("#1f2933"), 2), QBrush(colorBase));

    for (const Infraestructura& infraestructura : jugador.obtenerInfraestructuras()) {
        QColor relleno = infraestructura.estaDestruida() ? QColor("#9e9e9e") : colorInfra;
        QPen borde(infraestructura.estaDestruida() ? QColor("#616161") : QColor("#263238"));
        borde.setWidth(2);
        if (infraestructura.estaDestruida()) {
            borde.setStyle(Qt::DashLine);
        }

        escena->addRect(infraestructura.obtenerPosicion().x,
                        infraestructura.obtenerPosicion().y,
                        infraestructura.obtenerAncho(),
                        infraestructura.obtenerAlto(),
                        borde, QBrush(relleno));
    }
}
