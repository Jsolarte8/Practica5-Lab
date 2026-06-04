QT += widgets

TEMPLATE = app
CONFIG += c++17
CONFIG -= app_bundle

SOURCES += \
    src/main.cpp \
    src/vector2d.cpp \
    src/particula.cpp \
    src/proyectil.cpp \
    src/infraestructura.cpp \
    src/jugador.cpp \
    src/juego.cpp \
    src/mainwindow.cpp

HEADERS += \
    src/vector2d.h \
    src/particula.h \
    src/proyectil.h \
    src/infraestructura.h \
    src/jugador.h \
    src/juego.h \
    src/mainwindow.h
