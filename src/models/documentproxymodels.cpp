/***************************************************************************
        latestdocmodel  - the latest documents model
                             -------------------
    begin                : 2010-01-11
    copyright            : (C) 2010 by Thomas Richard
    email                : thomas.richard@proan.be
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

//QT includes
#include <QSortFilterProxyModel>
#include <QAbstractProxyModel>
#include <QtGlobal>
#include <QModelIndex>
#include <QVector>
#include <QObject>
#include <QVariant>
#include <QDate>
#include <QLocale>
#include <QDebug>

//Kraft includes
#include "datemodel.h"
#include "documentmodel.h"
#include "defaultprovider.h"
#include "docdigest.h"

#include "documentproxymodels.h"

DocumentFilterModel::DocumentFilterModel(int maxRows, QObject *parent)
        : QSortFilterProxyModel(parent),
          _enableTreeView(false),
          _treeModel(0),
          _tableModel(0)
{
    m_MaxRows = maxRows;
    this->setFilterCaseSensitivity(Qt::CaseInsensitive);
}

void DocumentFilterModel::setMaxRows( int max )
{
  m_MaxRows = max;
  invalidateFilter(); // refreshes the model
}

void DocumentFilterModel::setEnableTreeview( bool treeview )
{
    _enableTreeView = treeview;
    DocBaseModel *model;

    if(_enableTreeView) {
        if( _treeModel.isNull() ) {
            _treeModel.reset(new DateModel);
            _treeModel->loadFromTable();
        }
        model = _treeModel.data();
    } else {
        if( _tableModel.isNull()) {
            _tableModel.reset(new DocumentModel);
            _tableModel->loadFromTable();
        }
        model = _tableModel.data();
    }

    setSourceModel(model);
}

bool DocumentFilterModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
    if( !index.isValid()) {
        return false;
    }

    // filter works on the document ID, the client name and the document type.
    const QRegExp filter = filterRegExp();
    const QModelIndex index0 = sourceModel()->index(sourceRow, DocumentModel::Document_Ident, sourceParent);
    const QString idStr = sourceModel()->data(index0).toString();

    const QModelIndex index1 = sourceModel()->index(sourceRow, DocumentModel::Document_Type, sourceParent);
    const QString typeStr = sourceModel()->data(index1).toString();

    const QModelIndex index2 = sourceModel()->index(sourceRow, DocumentModel::Document_ClientName, sourceParent);
    const QString clientNameStr = sourceModel()->data(index2).toString();

    const QModelIndex index3 = sourceModel()->index(sourceRow, DocumentModel::Document_Whiteboard, sourceParent);
    const QString whiteboardStr = sourceModel()->data(index3).toString();

    const QModelIndex index4 = sourceModel()->index(sourceRow, DocumentModel::Document_ProjectLabel, sourceParent);
    const QString projectStr = sourceModel()->data(index4).toString();

    if( idStr.contains(filter) || typeStr.contains(filter) || clientNameStr.contains(filter)
           || whiteboardStr.contains(filter) || projectStr.contains(filter)) {
        return true;
    }

    // for the treeview, check all the children
    if( _enableTreeView ) {
        int rows = sourceModel()->rowCount(index);
        for (int row = 0; row < rows; row++)
            if (filterAcceptsRow(row, index)) {
                return true;
            }
    }

    return false;
}

