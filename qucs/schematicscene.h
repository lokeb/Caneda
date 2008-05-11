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

#ifndef __SCHEMATICSCENE_H
#define __SCHEMATICSCENE_H

#include <QtGui/QGraphicsScene>
#include <QtCore/QList>
#include <QtCore/QPair>
#include <QtCore/QVarLengthArray>

#include <QtGui/QGraphicsItem>

#include "undocommands.h"

class QUndoStack;
class QucsItem;
class Diagram;
class Painting;
class SvgPainter;
class QUndoCommand;

namespace Qucs
{
   enum Mode {
      SchematicMode,
      SymbolMode
   };
}

class Component;
class Wire;
class SchematicView;

typedef QGraphicsSceneMouseEvent MouseActionEvent;

/*! SchematicScene 
    class provides a surface for managing a large number of schematic element
*/
class SchematicScene : public QGraphicsScene
{
      Q_OBJECT;
   public:
      /*!\brief The different mouse action possible */
      enum MouseAction {
	/*!Wire action */
	Wiring,
	/*! Delete */
	Deleting,
	/*! Mark 
	  \todo What is */
	Marking,
	/*!Rotate */
	Rotating,
	/*!Mirror X */
	MirroringX,
	/*! Mirror Y */
	MirroringY,
	/*! Change status ie short, open */
	ChangingActiveStatus,
	/*! Set on grid */
	SettingOnGrid,
	/*! Zoom at point */
	ZoomingAtPoint,
	/*! \todo describe */
	PaintingDrawEvent,
	/*! insert an item */
	InsertingItems,
	/*! insert a wire label */
	InsertingWireLabel,
	/*! Normal (ie select) */
	Normal
      };

      SchematicScene(QObject *parent =0);
      SchematicScene(qreal x, qreal y, qreal width, qreal height, QObject * parent = 0);
      ~SchematicScene();

      void test();

      bool areItemsMoving() const { return m_areItemsMoving; }

      //toggle action methods.
      void mirrorXItems(QList<QucsItem*> &items, const Qucs::UndoOption);
      void mirrorYItems(QList<QucsItem*> &items, const Qucs::UndoOption);
      void rotateItems(QList<QucsItem*> &items, const Qucs::UndoOption);
      void deleteItems(QList<QucsItem*> &items, const Qucs::UndoOption);
      void setItemsOnGrid(QList<QucsItem*> &items, const Qucs::UndoOption);
      void toggleActiveStatus(QList<QucsItem*> &components, const Qucs::UndoOption);

      //these aren't toggle actions.
      void cutItems(QList<QucsItem*> &items, const Qucs::UndoOption = Qucs::PushUndoCmd);
      void copyItems(QList<QucsItem*> &items);
      void paste();

      QString fileName() const { return m_fileName; }
      void setFileName(const QString& fn);

      bool isModified() const { return m_modified; }

      QPointF nearingGridPoint(const QPointF &pos);

      QUndoStack* undoStack() { return m_undoStack; }

      uint gridWidth() const { return m_gridWidth; }
      void setGridWidth(uint width) { setGridSize(width, gridHeight()); }

      uint gridHeight() const { return m_gridHeight; }
      void setGridHeight(uint height) { setGridSize(gridWidth(), height); }

      void setGridSize(uint width, uint height);

      bool isGridVisible() const { return m_gridVisible; }
      void setGridVisible(bool visibility);

      QString dataSet() const { return m_dataSet; }
      void setDataSet(const QString& str);

      QString dataDisplay() const { return m_dataDisplay; }
      void setDataDisplay(const QString& disp);

      bool opensDataDisplay() const { return m_opensDataDisplay; }
      void setOpensDataDisplay(bool b);

      bool isFrameVisible() const { return m_frameVisible; }
      void setFrameVisible(bool vis);

      QStringList frameTexts() const { return m_frameTexts; }
      void setFrameTexts(const QStringList& texts);

      Qucs::Mode currentMode() const { return m_currentMode; }
      void setMode(const Qucs::Mode mode);

      MouseAction currentMouseAction() const { return m_currentMouseAction; }
      void setCurrentMouseAction(const MouseAction ma);

      SchematicView* activeView() const;

      void resetState();
      void beginInsertingItems(const QList<QucsItem*> &items);

      bool alignElements(const Qt::Alignment alignment);
      bool distributeElements(Qt::Orientation orientation);

      bool eventFilter(QObject *object, QEvent *event);

      bool shortcutsBlocked() const { return m_shortcutsBlocked; }
      void blockShortcuts(bool block);

   public slots:
      void setModified(bool m = true);
      bool sidebarItemClicked(const QString &item, const QString& category);

   signals:
      void modificationChanged(bool changed);
      void fileNameChanged(const QString& file);
      void titleToBeUpdated();

   protected:
      void drawBackground(QPainter *p, const QRectF& r);

      bool event(QEvent *event);

      void contextMenuEvent(QGraphicsSceneContextMenuEvent *e);

      void dragEnterEvent(QGraphicsSceneDragDropEvent * event);
      void dragMoveEvent(QGraphicsSceneDragDropEvent * event);
      void dropEvent(QGraphicsSceneDragDropEvent * event);

      void mousePressEvent(QGraphicsSceneMouseEvent *e);
      void mouseMoveEvent(QGraphicsSceneMouseEvent *e);
      void mouseReleaseEvent(QGraphicsSceneMouseEvent *e);
      void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *e);

      // Custom handlers
      void wiringEvent(MouseActionEvent *e);
      void deletingEvent(MouseActionEvent *e);
      void markingEvent(MouseActionEvent *e);
      void rotatingEvent(MouseActionEvent *e);
      void mirroringXEvent(MouseActionEvent *e);
      void mirroringYEvent(MouseActionEvent *e);
      void changingActiveStatusEvent(MouseActionEvent *e);
      void settingOnGridEvent(MouseActionEvent *e);
      void zoomingAtPointEvent(MouseActionEvent *e);
      void paintingDrawEvent(MouseActionEvent *e);
      void insertingItemsEvent(MouseActionEvent *e);
      void insertingWireLabelEvent(MouseActionEvent *event);
      void normalEvent(MouseActionEvent *e);

   private:
      void init();
      void sendMouseActionEvent(QGraphicsSceneMouseEvent *e);

      void processForSpecialMove(QList<QGraphicsItem*> _items);
      void disconnectDisconnectibles();
      void specialMove(qreal dx, qreal dy);
      void endSpecialMove();

      QucsItem* itemForName(const QString& name, const QString& category);
      void placeItem(QucsItem *item, QPointF pos, Qucs::UndoOption opt);
      int componentLabelSuffix(const QString& labelPrefix) const;

      int unusedPortNumber();
      bool isPortNumberUsed(int num) const;
      void setNumberUnused(int num);

      void disconnectItems(const QList<QucsItem*> &qItems, Qucs::UndoOption opt);
      void connectItems(const QList<QucsItem*> &qItems, Qucs::UndoOption opt);

      void placeAndDuplicatePainting();

      //These are helper variables (aka state holders)
      bool m_areItemsMoving;
      QList<Component*> disconnectibles;
      QList<Wire*> movingWires, grabMovingWires;
      QPointF lastPos;

      QPointF m_insertActionMousePos;
      QList<QucsItem*> m_insertibles;

      bool m_isWireCmdAdded;
      Wire *m_currentWiringWire;

      Painting *m_paintingDrawItem;
      int m_paintingDrawClicks;

      QRubberBand * m_zoomBand;
      QRectF m_zoomRect;

      QList<int> m_usedPortNumbers;
      QList<int> m_usablePortNumbers;

      //Document properties
      /*! Undo stack state */
      QUndoStack *m_undoStack;
      /*! Current mouse action */
      MouseAction m_currentMouseAction;
      Qucs::Mode m_currentMode;

      /*! Grid width in pixel */
      uint m_gridWidth;
      /*! Grid height in pixel */
      uint m_gridHeight;
      /*! Grid is visible */
      bool m_gridVisible;

      /*! Data Set file name */ 
      QString m_dataSet;
      /*! Data display file name */
      QString m_dataDisplay;
      /*! File name */
      QString m_fileName;
      QStringList m_frameTexts;

      bool m_modified;
      bool m_opensDataDisplay;
      bool m_frameVisible;
      /*! Snap component to grid */
      bool m_snapToGrid;
      bool m_macroProgress;
      bool m_shortcutsBlocked;
};

#endif //__SCHEMATICSCENE_H
