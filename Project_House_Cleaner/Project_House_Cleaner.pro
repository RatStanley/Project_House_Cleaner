TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Character/enemy_1.cpp \
        Weapons/machinegun.cpp \
        Weapons/pistol.cpp \
        Weapons/shotgun.cpp \
        Weapons/weapon.cpp \
        Character/character.cpp \
        Character/hero.cpp \
        game.cpp \
        main.cpp \
        map.cpp \
        maska.cpp


INCLUDEPATH += "E:/Code/SFML-2.5.1/include"
LIBS += -L"E:/Code/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

HEADERS += \
    BMP.h \
    Character/enemy_1.h \
    Weapons/machinegun.h \
    Weapons/pistol.h \
    Weapons/shotgun.h \
    Weapons/weapon.h \
    Character/character.h \
    Character/hero.h \
    game.h \
    map.h \
    maska.h
