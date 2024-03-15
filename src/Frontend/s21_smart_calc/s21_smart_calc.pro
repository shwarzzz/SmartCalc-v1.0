QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bankcalc.cpp \
    main.cpp \
    mainwindow.cpp \
    ../../Backend/s21_calc.c \
    ../../Backend/s21_convert_to_polish.c \
    ../../Backend/s21_parser.c \
    ../../Backend/s21_stack.c \
    qcustomplot.cpp
HEADERS += \
    bankcalc.h \
    mainwindow.h \
    ../../Backend/s21_calc.h \
    ../../Backend/s21_convert_to_polish.h \
    ../../Backend/s21_parser.h \
    ../../Backend/s21_stack.h \
    qcustomplot.h
FORMS += \
    bankcalc.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
