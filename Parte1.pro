TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    src/main.cpp \
    src/vector2d.cpp \
    src/particula.cpp \
    src/obstaculo.cpp \
    src/simulador.cpp

HEADERS += \
    src/vector2d.h \
    src/particula.h \
    src/obstaculo.h \
    src/simulador.h
