#-------------------------------------------------
#
# Project created by QtCreator 2023-10-02T12:19:25
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gestioncite
TEMPLATE = app


SOURCES += \
    cruds/batimentcrud.cpp \
    cruds/calendriercrud.cpp \
    cruds/chambrecrud.cpp \
    cruds/etudiantcrud.cpp \
    cruds/louercrud.cpp \
    database/db.cpp \
    dialogs/addbatiment.cpp \
    dialogs/addcalendrier.cpp \
    dialogs/addchambre.cpp \
    dialogs/addetudiant.cpp \
    dialogs/addlouer.cpp \
    main.cpp \
    mainwindow.cpp \
    tableDelegate/customDelegate.cpp \
    tableDelegate/format.cpp \
    widget/customCombo.cpp \
    widget/customLineEdit.cpp \
    widget/customSpinBox.cpp

HEADERS += \
    cruds/batimentcrud.h \
    cruds/calendriercrud.h \
    cruds/chambrecrud.h \
    cruds/etudiantcrud.h \
    cruds/louercrud.h \
    database/db.h \
    dialogs/addbatiment.h \
    dialogs/addcalendrier.h \
    dialogs/addchambre.h \
    dialogs/addetudiant.h \
    dialogs/addlouer.h \
    mainwindow.h \
    tableDelegate/customDelegate.h \
    tableDelegate/format.h \
    widget/customCombo.h \
    widget/customLineEdit.h \
    widget/customSpinBox.h

FORMS += \
    cruds/batimentcrud.ui \
    cruds/calendriercrud.ui \
    cruds/chambrecrud.ui \
    cruds/etudiantcrud.ui \
    cruds/louercrud.ui \
    dialogs/addbatiment.ui \
    dialogs/addcalendrier.ui \
    dialogs/addchambre.ui \
    dialogs/addetudiant.ui \
    dialogs/addlouer.ui \
    mainwindow.ui

INCLUDEPATH += \
    widget/ \
    cituniv/
