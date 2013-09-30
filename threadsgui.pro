CONFIG -= debug release
CONFIG += debug

TEMPLATE = app

QT += widgets core

SOURCES = main.cpp \
          mainwindow.cpp \
          progresswidget.cpp \
          thread.cpp \
          threadpool.cpp

HEADERS = mainwindow.h \
          progresswidget.h \
          thread.h \
          threadpool.h

FORMS   = mainwindow.ui \
          progresswidget.ui

DEFINES += MEMORY_LEAKS_SEARCH
