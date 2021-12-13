QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    city.cpp \
    gameblock.cpp \
    gameblockmanager.cpp \
    gameoverpopup.cpp \
    gridtile.cpp \
    logbook.cpp \
    main.cpp \
    mainwindow.cpp \
    particlemanager.cpp

HEADERS += \
    city.h \
    gameblock.h \
    gameblockmanager.h \
    gamedata.h \
    gameoverpopup.h \
    gridtile.h \
    logbook.h \
    mainwindow.h \
    particlemanager.h

FORMS += \
    gameoverpopup.ui \
    logbook.ui \
    mainwindow.ui

macx: LIBS += -L$$PWD/../box2d/build/bin/ -lbox2d

INCLUDEPATH += $$PWD/../box2d/include
DEPENDPATH += $$PWD/../box2d/include

macx: PRE_TARGETDEPS += $$PWD/../box2d/build/bin/libbox2d.a

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../box2d/bin/ -lbox2d
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../box2d/bin/ -lbox2d
else:unix: LIBS += -L$$PWD/../box2d/build/bin/ -lbox2d

INCLUDEPATH += $$PWD/../box2d/bin
DEPENDPATH += $$PWD/../box2d/bin
