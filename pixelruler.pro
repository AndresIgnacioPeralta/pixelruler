#-------------------------------------------------
#
# Project created by QtCreator 2015-05-01T18:19:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pixelruler
TEMPLATE = app


SOURCES += main.cpp\
        rulerwidget.cpp \
    configurationwidget.cpp \
    meassurewidget.cpp \
    colorselectorwidget.cpp \
    coloritem.cpp \
    sizeselectionwidget.cpp

HEADERS  += rulerwidget.h \
    constants.h \
    configurationwidget.h \
    meassurewidget.h \
    colorselectorwidget.h \
    coloritem.h \
    sizeselectionwidget.h

FORMS    += rulerwidget.ui \
    configurationwidget.ui \
    meassurewidget.ui \
    colorselectorwidget.ui \
    sizeselectionwidget.ui

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    style.qss
