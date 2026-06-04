#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "juego.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <QDoubleSpinBox>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    Juego juego;
    QGraphicsScene* escena;
    QGraphicsView* vista;
    QTimer* temporizador;
    QDoubleSpinBox* anguloSpin;
    QDoubleSpinBox* velocidadSpin;
    QPushButton* lanzarBoton;
    QLabel* turnoLabel;
    QLabel* estadoLabel;
    QLabel* vida1Label;
    QLabel* vida2Label;
    QLabel* infra1Label;
    QLabel* infra2Label;

    void lanzar();
    void actualizarFrame();
    void dibujarEscenario();
    void actualizarPanel();
    QString resumenInfraestructura(const Jugador& jugador) const;
    void dibujarJugador(const Jugador& jugador, const QColor& colorBase,
                        const QColor& colorInfra);
};

#endif
