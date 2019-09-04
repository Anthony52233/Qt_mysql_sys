#-------------------------------------------------
#
# Project created by QtCreator 2019-08-28T13:42:20
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mysql_camera_sys
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
        admin_show.cpp \
        custom_show.cpp \
        dialog_add_admin.cpp \
        dialog_add_camera.cpp \
        dialog_add_custom.cpp \
        dialog_edit_admin.cpp \
        dialog_edit_camera.cpp \
        dialog_edit_custom.cpp \
        dialog_edit_indent.cpp \
        dialog_find_admin.cpp \
        dialog_find_custom.cpp \
        indent_show.cpp \
        main.cpp \
        widget.cpp

HEADERS += \
        admin_show.h \
        custom_show.h \
        dialog_add_admin.h \
        dialog_add_camera.h \
        dialog_add_custom.h \
        dialog_edit_admin.h \
        dialog_edit_camera.h \
        dialog_edit_custom.h \
        dialog_edit_indent.h \
        dialog_find_admin.h \
        dialog_find_custom.h \
        indent_show.h \
        widget.h

FORMS += \
        admin_show.ui \
        custom_show.ui \
        dialog_add_admin.ui \
        dialog_add_camera.ui \
        dialog_add_custom.ui \
        dialog_edit_admin.ui \
        dialog_edit_custom.ui \
        dialog_edit_indent.ui \
        dialog_find_admin.ui \
        dialog_find_custom.ui \
        indent_show.ui \
        widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
