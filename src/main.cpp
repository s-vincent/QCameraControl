/*
 * QCameraControl - Qt/QML camera control.
 * Copyright (c) 2018, Sebastien Vincent
 *
 * Distributed under the terms of the BSD 3-clause License.
 * See the LICENSE file for details.
 */

/**
 * \file main.cpp
 * \brief Main file.
 * \author Sebastien Vincent
 * \date 2018
 */

#include <QGuiApplication>
//#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickView>

#include "camerainfomodel.hpp"

int main(int argc, char** argv)
{
  QGuiApplication app(argc, argv);
  QQuickView view;
  CameraInfoModel model;

  QQmlContext *ctxt = view.rootContext();
  ctxt->setContextProperty("cameraInfoModel", &model);
  
  view.setResizeMode(QQuickView::SizeRootObjectToView);
  view.setSource(QUrl("qrc:///qcameracontrol.qml"));
  view.showMaximized();

  return app.exec();
}

