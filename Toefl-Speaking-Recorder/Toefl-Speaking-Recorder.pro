#-------------------------------------------------
#
# Project created by QtCreator 2014-02-14T20:10:58
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Toefl-Speaking-Recorder
TEMPLATE = app
CONFIG  += release

win32:RC_FILE = myapp.rc
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    tsr.cpp \
    dialogabout.cpp \
    dialogaudiosettings.cpp

HEADERS  += mainwindow.h \
    tsr.h \
    dialogabout.h \
    structs.h \
    dialogaudiosettings.h \
    util.h

FORMS    += mainwindow.ui \
    dialogabout.ui \
    dialogaudiosettings.ui

RESOURCES += \
    rc.qrc

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    android/AndroidManifest.xml
