#include "PercentTableView.h"

#include <QHeaderView>

#include "PercentDelegate.h"
#include "PercentModel.h"

PercentTableView::PercentTableView(QWidget* parent) : QTableView(parent) {
  setItemDelegateForColumn(1, new PercentDelegate());
  setSelectionMode(QAbstractItemView::SingleSelection);
  verticalHeader()->hide();
}

PercentModel* PercentTableView::percentModel() const { return static_cast<PercentModel*>(model()); }

void PercentTableView::setMinimumSize() {
  int frame      = frameWidth() * 2;
  int min_height = rowHeight(0) * (model()->rowCount()) + horizontalHeader()->height() + frame;
  int min_width  = horizontalHeader()->length() + verticalHeader()->width() + frame;

  setMinimumWidth(min_width);
  setMinimumHeight(min_height);
}