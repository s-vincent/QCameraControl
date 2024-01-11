# QCameraControl

Simple Qt/QML application that displays all connected webcams streams.

The project uses QtMultimedia for webcam access.

## Pre-requisites

You need Qt 5, QMake, QML Quick and QtMultimedia.

On Debian 11/12:
```
apt-get install qtbase5-dev qtdeclarative5-dev qtmultimedia5-dev qt5-qmake \
      qml-module-qtmultimedia qml-module-qtquick2  qml-module-qtquick-controls2
```

## Build

```
qmake
make
```

## Usage

To run from the project directory:

`./qcameracontrol`

## License

All codes are under BSD-3 license.

