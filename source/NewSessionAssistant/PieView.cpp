#include <math.h>

#include <QScrollBar>
#include <QtGui>

const double PI = 2 * acos(0.0);

#include "PercentModel.h"
#include "PieView.h"

PieView::PieView(QWidget* parent) : QAbstractItemView(parent), myLabelColumn(0), myDataColumn(1) {
  myPieDiameter  = 200;
  myMargin       = 0;
  myLegendOrigin = QPoint(0, pieDiameter());
  myPieOrigin    = QPoint(0, 0);
}

int PieView::labelHeight() const { return int(QFontMetrics(viewOptions().font).height()); }

// Item's rect relative to the viewport
QRect PieView::visualRect(const QModelIndex& index) const {
  QRect item_rect = itemRect(index);
  if (item_rect.isValid()) {
    return QRect(item_rect.left() - horizontalOffset(), item_rect.top() - verticalOffset(), item_rect.width(),
                 item_rect.height());
  }
  return item_rect;
}

// Returns the rect of the item at position index in the model. The rectangle is relative to the whole space
QRect PieView::itemRect(const QModelIndex& index) const {
  if (!index.isValid()) return QRect();
  if (index.column() == dataColumn()) return pieRect();
  if (index.column() == labelColumn()) return labelItemRect(index);
  return QRect();
}

QRect PieView::pieRect() const {
  QRect pie_rect;
  pie_rect.setX(pieOrigin().x());
  pie_rect.setY(pieOrigin().y());
  pie_rect.setWidth(pieDiameter());
  pie_rect.setHeight(pieDiameter());
  return pie_rect;
}

QRect PieView::labelItemRect(const QModelIndex& index) const {
  QRect item_rect;
  item_rect.setX(legendOrigin().x());
  item_rect.setY(legendOrigin().y() + index.row() * labelHeight());
  item_rect.setWidth(labelWidth());
  item_rect.setHeight(labelHeight());
  return item_rect;
}

void PieView::scrollTo(const QModelIndex& index, QAbstractItemView::ScrollHint /*hint*/) {
  if (!index.isValid()) {
    verticalScrollBar()->setValue(0);
    horizontalScrollBar()->setValue(0);
    update();
    return;
  }
  scrollHorizontally(index);
  scrollVertically(index);
  update();
}

void PieView::scrollVertically(const QModelIndex& index) {
  if (visualRect(index).top() < viewportRect().top())
    verticalScrollBar()->setValue(verticalOffset() + visualRect(index).top());
  else if (visualRect(index).bottom() > viewportRect().bottom())
    verticalScrollBar()->setValue(
        verticalOffset() +
        // Min used to make it top aligned if vertically small
        qMin(visualRect(index).bottom() - viewportRect().bottom(), visualRect(index).top() - viewportRect().top()));
}

void PieView::scrollHorizontally(const QModelIndex& index) {
  if (visualRect(index).left() < viewportRect().left())
    horizontalScrollBar()->setValue(horizontalOffset() + visualRect(index).left() - viewportRect().left());
  else if (visualRect(index).right() > viewportRect().right())
    horizontalScrollBar()->setValue(
        horizontalOffset() +
        // Min used so that it is left aligned in the case of very small viewport
        qMin(visualRect(index).right() - viewportRect().right(), visualRect(index).left() - viewportRect().left()));
}

// Returns the item that covers the coordinate given in the view.
QModelIndex PieView::indexAt(const QPoint& point) const {
  if (numberOfItems() == 0) return QModelIndex();

  // Transform point to be relative to whole entire space
  QPoint w_point = QPoint(point.x() + horizontalOffset(), point.y() + verticalOffset());

  if (pointIsOnPieSlice(w_point)) return findSlice(w_point);

  if (pointIsOnlegend(w_point)) {
    int row = int((w_point.y() - legendOrigin().y()) / labelHeight());
    return model()->index(row, labelColumn());
  }
  return QModelIndex();
}

double PieView::distanceFromPieCenter(const QPoint& point) const {
  return sqrt(pow(pieCenter().x() - point.x(), 2) + pow(pieCenter().y() - point.y(), 2));
}

bool PieView::pointIsOnPieSlice(const QPoint& point) const {
  return (distanceFromPieCenter(point) < pieRadius()) && (point != pieCenter());
}

bool PieView::pointIsOnlegend(const QPoint& point) const {
  return point.x() >= legendOrigin().x() && point.x() <= legendOrigin().x() + labelWidth() &&
         point.y() >= legendOrigin().y() && point.y() <= legendOrigin().y() + legendHeight();
}

double PieView::angleFormed(const QPoint& point) const {
  int    d_x   = point.x() - pieCenter().x();
  double angle = (180 / PI) * acos(d_x / distanceFromPieCenter(point));

  if (point.y() > pieCenter().y()) angle = 360 - angle;
  return angle;
}

QModelIndex PieView::findSlice(const QPoint& point) const {
  double sum_of_angles = 0.0;
  for (int row = 0; row < numberOfItems(); row++) {
    if (angleFormed(point) >= sum_of_angles && angleFormed(point) < (sum_of_angles + itemAngle(row)))
      return model()->index(row, dataColumn());
    sum_of_angles += itemAngle(row);
  }
  return QModelIndex();
}

double PieView::itemAngle(const int row) const {
  return 360 * model()->index(row, dataColumn()).data().toDouble() / 100;
}

QPoint PieView::pieCenter() const { return QPoint(pieOrigin().x() + pieRadius(), pieOrigin().y() + pieRadius()); }

QModelIndex PieView::moveCursor(QAbstractItemView::CursorAction cursorAction, Qt::KeyboardModifiers /*modifiers*/) {
  int row = currentIndex().row();
  if (cursorAction == MoveUp) {
    row = (row - 1 + numberOfItems()) % numberOfItems();
  } else if (cursorAction == MoveDown) {
    row = (row + 1) % numberOfItems();
  }
  viewport()->update();
  return model()->index(row, currentIndex().column());
}

int  PieView::horizontalOffset() const { return horizontalScrollBar()->value(); }
int  PieView::verticalOffset() const { return verticalScrollBar()->value(); }
bool PieView::isIndexHidden(const QModelIndex& /*index*/) const { return false; }
int  PieView::numberOfItems() const { return model()->rowCount(); }

// Find the indices corresponding to the extent of the selection.
void PieView::setSelection(const QRect& /*rect*/, QItemSelectionModel::SelectionFlags /*command*/) { update(); }

QRegion PieView::visualRegionForSelection(const QItemSelection& /*selection*/) const { return QRegion(); }

void PieView::updateGeometries() {
  horizontalScrollBar()->setPageStep(viewport()->width());
  horizontalScrollBar()->setRange(0, qMax(0, (int)pieDiameter() - viewport()->width()));
  verticalScrollBar()->setPageStep(viewport()->height());
  verticalScrollBar()->setRange(0, qMax(0, (int)pieDiameter() * 2 - viewport()->height()));
}

void PieView::mousePressEvent(QMouseEvent* event) { QAbstractItemView::mousePressEvent(event); }

void PieView::mouseMoveEvent(QMouseEvent* event) { QAbstractItemView::mouseMoveEvent(event); }

void PieView::mouseReleaseEvent(QMouseEvent* event) {
  QAbstractItemView::mouseReleaseEvent(event);
  viewport()->update();
}

void PieView::paintEvent(QPaintEvent* event) {
  QItemSelectionModel* selections = selectionModel();
  QStyleOptionViewItem option     = viewOptions();

  QBrush background = option.palette.base();
  QPen   foreground(option.palette.color(QPalette::WindowText));
  QPen   textPen(option.palette.color(QPalette::Text));
  QPen   highlightedPen(option.palette.color(QPalette::HighlightedText));

  QPainter painter(viewport());
  painter.setRenderHint(QPainter::Antialiasing);

  painter.fillRect(event->rect(), background);
  painter.setPen(foreground);

  // Viewport rectangles
  QRect pieRect = QRect(margin(), margin(), pieDiameter(), pieDiameter());

  if (numberOfItems() > 0) {
    painter.save();
    painter.translate(pieRect.x() - horizontalScrollBar()->value(), pieRect.y() - verticalScrollBar()->value());
    painter.drawEllipse(0, 0, pieDiameter(), pieDiameter());
    double startAngle = 0.0;
    int    row;

    for (row = 0; row < model()->rowCount(rootIndex()); ++row) {
      QModelIndex index = model()->index(row, 1, rootIndex());
      double      value = model()->data(index).toDouble();

      if (value > 0.0) {
        double angle = 360.0 * value / 100.0;

        QModelIndex colorIndex = model()->index(row, 0, rootIndex());
        QColor      color      = QColor(model()->data(colorIndex, Qt::DecorationRole).toString());

        if (currentIndex() == index)
          painter.setBrush(QBrush(color, Qt::Dense4Pattern));
        else if (selections->isSelected(index))
          painter.setBrush(QBrush(color, Qt::Dense3Pattern));
        else
          painter.setBrush(QBrush(color));

        painter.drawPie(0, 0, pieDiameter(), pieDiameter(), int(startAngle * 16), int(angle * 16));

        startAngle += angle;
      }
    }
    painter.restore();

    int keyNumber = 0;

    for (row = 0; row < model()->rowCount(rootIndex()); ++row) {
      QModelIndex index = model()->index(row, 1, rootIndex());
      double      value = model()->data(index).toDouble();

      if (value > 0.0) {
        QModelIndex labelIndex = model()->index(row, 0, rootIndex());

        QStyleOptionViewItem option = viewOptions();
        option.rect                 = visualRect(labelIndex);
        if (selections->isSelected(labelIndex)) option.state |= QStyle::State_Selected;
        if (currentIndex() == labelIndex) option.state |= QStyle::State_HasFocus;
        itemDelegate()->paint(&painter, option, labelIndex);

        keyNumber++;
      }
    }
  }
}
