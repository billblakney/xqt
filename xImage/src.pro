######################################################################
# Automatically generated by qmake (2.01a) Thu Jan 15 11:53:06 2015
######################################################################

TEMPLATE = app
TARGET = go
DEPENDPATH += .
INCLUDEPATH += .
greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
    DEFINES += QT_V5
}

QMAKE_CLEAN   = $(BIN_DIR)/go
QMAKE_CLEAN  += debug/* release/*
CONFIG       += debug_and_release


# Input
HEADERS += MainWindow.hh \
           Board.hh \
           ImageUtil.hh \
           Square.hh \

SOURCES += main.cc MainWindow.cc \
           Board.cc \
           ImageUtil.cc \
           Square.cc \
