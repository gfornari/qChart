######################################################################
# Automatically generated by qmake (2.01a) Thu Apr 18 17:30:01 2013
######################################################################

TEMPLATE = app
TARGET = qChart
QT += gui core xml
DEPENDPATH += . gui lib
INCLUDEPATH += . gui lib

# Input
HEADERS += gui/mainwindow.h \
           gui/mycustomscene.h \
           gui/myhorizontallayoutwidget.h \
           gui/mytablewidget.h \
           gui/mytabwidget.h \
    lib/chart.h \
    lib/barchart.h \
    lib/piechart.h \
    lib/linechart.h \
    lib/mygraphicsellipseitem.h

SOURCES += main.cpp \
           gui/mainwindow.cpp \
           gui/mycustomscene.cpp \
           gui/myhorizontallayoutwidget.cpp \
           gui/mytablewidget.cpp \
           gui/mytabwidget.cpp \
    lib/chart.cpp \
    lib/barchart.cpp \
    lib/piechart.cpp \
    lib/linechart.cpp \
    lib/mygraphicsellipseitem.cpp

RESOURCES += \
    img/img.qrc
