QT += widgets

TEMPLATE = app

CONFIG += c++17
CONFIG -= app_bundle

TARGET = Parte2

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    vector2d.cpp \
    particula.cpp \
    proyectil.cpp \
    infraestructura.cpp \
    jugador.cpp \
    juego.cpp

HEADERS += \
    mainwindow.h \
    vector2d.h \
    particula.h \
    proyectil.h \
    infraestructura.h \
    jugador.h \
    juego.h