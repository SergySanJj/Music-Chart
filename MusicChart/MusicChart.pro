#-------------------------------------------------
#
# Project created by QtCreator 2018-12-08T23:28:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = MusicChart
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    artist.cpp \
    composition.cpp \
    chart.cpp \
    genres.cpp \
    qcustomplot.cpp \
    chartitem.cpp \
    artistsmodel.cpp \
    compositionsmodel.cpp \
    addartistdialog.cpp \
    addcompositiondialog.cpp \
    artistslistmodel.cpp \
    filterartistgenreproxy.cpp \
    artistsboxmodel.cpp \
    compositionhistorydialog.cpp

HEADERS += \
        mainwindow.h \
    artist.h \
    composition.h \
    chart.h \
    genres.h \
    qcustomplot.h \
    chartitem.h \
    artistsmodel.h \
    compositionsmodel.h \
    addartistdialog.h \
    addcompositiondialog.h \
    artistslistmodel.h \
    filterartistgenreproxy.h \
    artistsboxmodel.h \
    compositionhistorydialog.h

FORMS += \
        mainwindow.ui \
    addartistdialog.ui \
    addcompositiondialog.ui \
    compositionhistorydialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
