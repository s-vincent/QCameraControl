/*
 * QCameraControl - Qt/QML camera control.
 * Copyright (c) 2018, Sebastien Vincent
 *
 * Distributed under the terms of the BSD 3-clause License.
 * See the LICENSE file for details.
 */

/**
 * \file camerainfomodel.hpp
 * \brief Model for QCameraInfo.
 * \author Sebastien Vincent
 * \date 2018
 */

#ifndef CAMERA_INFO_MODEL_HPP
#define CAMERA_INFO_MODEL_HPP

#include <QAbstractListModel>
#include <QModelIndex>
#include <QCameraInfo>

/**
 * \class CameraInfoModel
 * \brief Model for CameraInfo.
 */
class CameraInfoModel : public QAbstractListModel
{
  Q_OBJECT

  public:
    /**
     * \brief Model role enumeration.
     */
    enum ModelRoles
    {
      /**
       * \brief Device identifier.
       */
      DeviceIdRole = Qt::UserRole + 1,

      /**
       * \brief Description.
       */
      DescriptionRole
    };

    /**
     * \brief Constructor.
     * \param parent Qt parent object.
     */
    CameraInfoModel(QObject* parent = NULL);

    /**
     * \brief Destructor.
     */
    virtual ~CameraInfoModel();

    /**
     * \brief Returns number of rows.
     * \param parent index.
     * \return number of rows.
     */
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;

    /**
     * \brief Returns data at specified index.
     * \param index index.
     * \param role data role to return.
     * \return data.
     */
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    /**
     * \brief Removes rows.
     * \param row row index.
     * \param count number of row to delete.
     * \param parent parent index.
     * \return true if removed, false otherwise.
     */
    virtual Q_INVOKABLE bool removeRows(int row, int count,
        const QModelIndex& parent = QModelIndex());

  protected:
    /**
     * \brief Roles for the model.
     */
    QHash<int, QByteArray> roleNames() const;

  private:
    /**
     * \brief List of current QCameraInfos.
     */
    QList<QCameraInfo> m_cameraInfos;

  private slots:
    void updateCameras();
};

#endif /* CAMERA_INFO_MODEL_HPP */

