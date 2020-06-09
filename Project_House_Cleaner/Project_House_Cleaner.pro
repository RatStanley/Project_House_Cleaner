TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Weapons/weapon.cpp \
        Character/character.cpp \
        Character/hero.cpp \
        main.cpp \
        map.cpp \
        maska.cpp


INCLUDEPATH += "C:/SFML-2.5.1/include"
LIBS += -L"C:/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

HEADERS += \
    BMP.h \
    Weapons/weapon.h \
    Character/character.h \
    Character/hero.h \
    map.h \
    maska.h
