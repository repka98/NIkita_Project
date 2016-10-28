QT       += core gui \
         multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TowerDefence
TEMPLATE = app



SOURCES += \
    main.cpp \
    tower.cpp \
    game.cpp \
    bullet.cpp \
    enemy.cpp \
    buildbrowndtowerTwoicon.cpp \
    browntower.cpp \
    buildgreentowericon.cpp \
    buildredtowericon.cpp \
    greentower.cpp \
    redtower.cpp

HEADERS += \
    tower.h \
    game.h \
    bullet.h \
    enemy.h \
    buildbrowntowericon.h \
    browntower.h \
    buildgreentowericon.h \
    buildredtowericon.h \
    greentower.h \
    redtower.h

RESOURCES += \
    area.qrc
