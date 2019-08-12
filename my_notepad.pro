#-------------------------------------------------
#
# Project created by QtCreator 2019-08-05T16:33:32
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = my_notepad
TEMPLATE = app


SOURCES += main.cpp\
        notepad.cpp \
    search/searchdialog.cpp \
    replace/replacedialog.cpp \
    goto/gotodialog.cpp

HEADERS  += notepad.h \
    search/searchdialog.h \
    replace/replacedialog.h \
    goto/gotodialog.h

FORMS    += notepad.ui \
    search/searchdialog.ui \
    replace/replacedialog.ui \
    goto/gotodialog.ui


DESTDIR = ../bin

RC_ICONS = image/logo.ico

RESOURCES += \
    source.qrc
