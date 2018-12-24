/*
 * QCameraControl - Qt/QML camera control.
 * Copyright (c) 2018, Sebastien Vincent
 *
 * Distributed under the terms of the BSD 3-clause License.
 * See the LICENSE file for details.
 */

/**
 * \file qcameracontrol.qml
 * \brief UI for QCameraControl.
 * \author Sebastien Vincent
 * \date 2018
 */

import QtQuick 2.0
import QtQuick.Controls 2.0
import QtMultimedia 5.4

Rectangle {
  visible: true
  color: "black"
  width: 1280
  height: 720

  Pane {
    id: root
    anchors.fill: parent
    anchors.leftMargin: 0
    anchors.topMargin: 0
    width: parent.width
    height: parent.height

    Flow {
      id: flow 
      anchors.fill: parent
      spacing: 1

      Repeater {
        //model: QtMultimedia.availableCameras
        model: cameraInfoModel
        delegate: 
        Pane {
          id: pane
          width: 640
          height: 480
          padding: 0

          Column {
            property bool showList: false
            anchors.left: parent.left
            anchors.right: parent.right 
            spacing: 0 

            Button {
              visible: true
              anchors.left: parent.left 
              anchors.right: parent.right

              text: deviceDescription

              onClicked: {
                paneSettingsList.shown = !paneSettingsList.shown

                // start or stop camera
                if(paneSettingsList.shown) {
                  camera.start();
                }
                else {
                  camera.stop();
                }
              }
            }

            Pane {
              id: paneSettingsList
              anchors.left: parent.left 
              anchors.right: parent.right 
              visible: height > 0
              height: shown ? implicitHeight : 0
              padding: 0

              property bool shown: true

              Behavior on height {
                NumberAnimation {
                  easing.type: Easing.InOutQuad
                }
              }

              VideoOutput {
                id: viewfinder
                visible: true
                anchors.fill: parent
                anchors.topMargin: 0
                anchors.leftMargin: 0

                width: parent.width
                height: parent.height
                source: camera
                // fillMode: VideoOutput.PreserveAspectCrop

                Camera {
                  id: camera
                  deviceId: deviceId
                  captureMode: Camera.CaptureViewfinder
                  viewfinder.resolution: "640x480"
                  onCameraStateChanged: {
                    console.log("Camera state changed: " + cameraState)

                    // remove camera UI
                    if(cameraState == Camera.UnloadedState) {
                      cameraInfoModel.removeRows(index, index);
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  } 
}

