#ifndef PIEVIEW_H
#define PIEVIEW_H

#include <qcoreevent.h>

#include <QAbstractItemView>

class PercentModel;

class PieView : public QAbstractItemView {
  Q_OBJECT
 public:
  PieView(QWidget* parent = 0);
  void        scrollTo(const QModelIndex& index, ScrollHint hint = EnsureVisible) override;
  QRect       visualRect(const QModelIndex& index) const override;
  QModelIndex indexAt(const QPoint& point) const override;

  QPoint legendOrigin() const { return myLegendOrigin; }
  // Top left point that defines where to draw the pie graph
  QPoint pieOrigin() const { return myPieOrigin; }
  int    labelHeight() const;
  int    labelWidth() const { return 100; }
  int    legendHeight() const { return labelHeight() * numberOfItems(); }
  double pieDiameter() const { return myPieDiameter; }
  int    numberOfItems() const;

 protected:
  QModelIndex moveCursor(QAbstractItemView::CursorAction cursorAction, Qt::KeyboardModifiers modifiers) override;

  void    mousePressEvent(QMouseEvent* event) override;
  void    mouseMoveEvent(QMouseEvent* event) override;
  void    mouseReleaseEvent(QMouseEvent* event) override;
  int     horizontalOffset() const override;
  int     verticalOffset() const override;
  bool    isIndexHidden(const QModelIndex& index) const override;
  void    setSelection(const QRect&, QItemSelectionModel::SelectionFlags command) override;
  QRegion visualRegionForSelection(const QItemSelection& selection) const override;
  void    paintEvent(QPaintEvent* event) override;

 private:
  QRect itemRect(const QModelIndex& item) const;
  QRect viewportRect() const { return viewport()->rect(); }
  QRect pieRect() const;
  QRect labelItemRect(const QModelIndex& index) const;
  void  scrollHorizontally(const QModelIndex& index);
  void  scrollVertically(const QModelIndex& index);

  double      pieRadius() const { return pieDiameter() / 2; }
  int         margin() const { return myMargin; }
  int         dataColumn() const { return myDataColumn; }
  int         labelColumn() const { return myLabelColumn; }
  double      distanceFromPieCenter(const QPoint& point) const;
  QPoint      pieCenter() const;
  void        updateGeometries() override;
  QModelIndex findSlice(const QPoint& point) const;
  double      angleFormed(const QPoint& point) const;
  double      itemAngle(const int row) const;
  bool        pointIsOnlegend(const QPoint& point) const;
  bool        pointIsOnPieSlice(const QPoint& point) const;
  void        drawDebugPoint(const QPoint& point, QPainter& painter);
  int         myLabelColumn;
  int         myDataColumn;
  int         myMargin;
  double      myPieDiameter;
  QPoint      myLegendOrigin;
  QPoint      myPieOrigin;
};

#endif
