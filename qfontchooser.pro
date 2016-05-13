cache

TEMPLATE = app

TARGET = qfontchooser

QT += core gui widgets

CONFIG += release

unix {
	target.path = /usr/local/bin
	INSTALLS += target
}

INCLUDEPATH += GeneratedFiles
MOC_DIR = GeneratedFiles
OBJECTS_DIR = Objects
UI_DIR = GeneratedFiles
RCC_DIR = GeneratedFiles

HEADERS += fontchooser.h

SOURCES += main.cpp fontchooser.cpp

FORMS += fontchooser.ui
