TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

LIBS += -lsfml-system -lsfml-window -lsfml-graphics -lz

SOURCES += main.cpp \
    game.cpp \
    maingame.cpp \
    player.cpp \
    wall.cpp \
    entity.cpp \
    guard.cpp

INCLUDEPATH += $$PWD/include
SOURCES += $$PWD/src/*.cpp
HEADERS += $$PWD/include/*.hpp \
    wall.hpp \
    entity.hpp \
    guard.hpp

HEADERS += \
    maingame.hpp \
    game.hpp \
    gamestate.hpp \
    player.hpp

include(deployment.pri)
qtcAddDeployment()
