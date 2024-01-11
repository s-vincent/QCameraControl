/*
 * QCameraControl - Qt/QML camera control.
 * Copyright (c) 2018, Sebastien Vincent
 *
 * Distributed under the terms of the BSD 3-clause License.
 * See the LICENSE file for details.
 */

/**
 * \file camerainfomodel.cpp
 * \brief ListModel for QCameraInfo.
 * \author Sebastien Vincent
 * \date 2018
 */

#include <QTimer>
#include "camerainfomodel.hpp"

CameraInfoModel::CameraInfoModel(QObject* parent)
  : QAbstractListModel(parent)
{
  m_cameraInfos = QCameraInfo::availableCameras();

  QTimer* timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(updateCameras()));
  timer->start(2000);
}

CameraInfoModel::~CameraInfoModel()
{
}

int CameraInfoModel::rowCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent);
  return m_cameraInfos.count();
}

QVariant CameraInfoModel::data(const QModelIndex& parent, int role) const
{
  if(parent.row() < 0 || parent.row() >= m_cameraInfos.count())
  {
    return QVariant();
  }

  const QCameraInfo& cameraInfo = m_cameraInfos[parent.row()];
  if(role == DeviceIdRole)
  {
    return cameraInfo.deviceName();
  }
  else if(role == DescriptionRole)
  {
    return cameraInfo.description();
  }

  return QVariant();
}

bool CameraInfoModel::removeRows(int row, int count, const QModelIndex& parent)
{
  if(row < 0 || row >= m_cameraInfos.count())
  {
    return false;
  }

  beginRemoveRows(parent, row, row + count - 1);
  m_cameraInfos.removeAt(row);
  endRemoveRows();

  return true;
}

QHash<int, QByteArray> CameraInfoModel::roleNames() const
{
  QHash<int, QByteArray> roles;

  roles[DeviceIdRole] = "deviceId";
  roles[DescriptionRole] = "deviceDescription";
  return roles;
}

void CameraInfoModel::updateCameras()
{
  // If camera is currently running (i.e. started) it will not be in
  // availableCameras().
  //
  // This method will only take care of new camera.
  QList<QCameraInfo> cameraInfos = QCameraInfo::availableCameras();

  if(cameraInfos.count() == 0)
  {
    return;
  }

  foreach(auto c, cameraInfos)
  {
    bool found = false;
    QCameraInfo cameraInfo;

    foreach(auto c2, m_cameraInfos)
    {
      if(c.deviceName() == c2.deviceName())
      {
        found = true;
        break;
      }
    }

    if(!found)
    {
      beginInsertRows(QModelIndex(), rowCount(), rowCount());
      m_cameraInfos.append(c);
      endInsertRows();
    }
  }
}

