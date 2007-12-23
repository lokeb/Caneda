/***************************************************************************
 * Copyright (C) 2006 by Gopala Krishna A <krishna.ggk@gmail.com>          *
 *                                                                         *
 * This is free software; you can redistribute it and/or modify            *
 * it under the terms of the GNU General Public License as published by    *
 * the Free Software Foundation; either version 2, or (at your option)     *
 * any later version.                                                      *
 *                                                                         *
 * This software is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 * GNU General Public License for more details.                            *
 *                                                                         *
 * You should have received a copy of the GNU General Public License       *
 * along with this package; see the file COPYING.  If not, write to        *
 * the Free Software Foundation, Inc., 51 Franklin Street - Fifth Floor,   *
 * Boston, MA 02110-1301, USA.                                             *
 ***************************************************************************/

#ifndef __SIDEBARMODEL_H
#define __SIDEBARMODEL_H

#include <QtCore/QAbstractItemModel>

class CategoryItem;
class Library;

class SidebarModel : public QAbstractItemModel
{
      Q_OBJECT;
   public:
      SidebarModel(QObject *parent=0);
      ~SidebarModel(){};

      int columnCount(const QModelIndex & parent = QModelIndex()) const {Q_UNUSED(parent);return 1;}
      QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
      QModelIndex index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const;
      QModelIndex parent ( const QModelIndex & index ) const;
      int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
      Qt::ItemFlags flags(const QModelIndex& index) const;
      QStringList mimeTypes() const;
      bool isComponent(const QModelIndex& index) const;
      QMimeData* mimeData(const QModelIndexList& indexes) const;

      QPixmap pixmap(const QModelIndex& index) const;
      void plugLibrary(const QString& libraryName);
   private:

      CategoryItem *rootItem;
};

#endif //__SIDEBARMODEL_H
