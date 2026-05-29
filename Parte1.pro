TEMPLATE = app

CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

TARGET = Parte1

SOURCES += \
    main.cpp \
    vector2d.cpp \
    particula.cpp \
    obstaculo.cpp \
    simulador.cpp

HEADERS += \
    vector2d.h \
    particula.h \
    obstaculo.h \
    simulador.h