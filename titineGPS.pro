#-------------------------------------------------
#
# Project created by QtCreator 2017-07-16T15:14:20
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = titineGPS
TEMPLATE = app

INCLUDEPATH += /usr/local/include/opencv

LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_videoio\
        -lopencv_imgproc -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d\
        -lopencv_objdetect -lopencv_flann -lopencv_tracking

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    joystick.cpp

HEADERS += \
        mainwindow.h \
    joystick.h

FORMS += \
        mainwindow.ui

