TEMPLATE=app
TARGET=qcameracontrol
QT += quick qml multimedia

HEADERS += src/camerainfomodel.hpp
SOURCES += src/main.cpp src/camerainfomodel.cpp
RESOURCES += qml/qcameracontrol.qrc

target.path = /usr/bin/qcameracontrol
INSTALLS += target

