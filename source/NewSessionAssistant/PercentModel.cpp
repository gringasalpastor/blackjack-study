#include "PercentModel.h"

#include <math.h>

PercentModel::PercentModel(const QStringList& labels, QObject* parent)
    : QStandardItemModel(labels.size(), 2, parent), percentColumn(1), labelColumn(0), numberOfDecimalPlaces(2) {
  setHeaderData(0, Qt::Horizontal, "");
  setHeaderData(percentColumn, Qt::Horizontal, "Percentage");

  for (int row = 0; row < labels.size(); ++row) {
    setData(index(row, labelColumn), labels[row]);
    setPercentage(row, defaultPercent(row));
    setData(index(row, labelColumn),
            QColor(255 / (row + 1), (10 * (row + 1) * (row + 1)) % 255, 255 - (255 / (row + 1)), 127),
            Qt::DecorationRole);
    item(row, percentColumn)->setCheckable(true);
    item(row, percentColumn)->setCheckState(Qt::Checked);
  }

  connect(this, SIGNAL(itemCheckedChanged(const QModelIndex&)), this,
          SLOT(handleItemCheckedChange(const QModelIndex&)));
}

void PercentModel::handleItemCheckedChange(const QModelIndex& index) {
  QStandardItem* this_item = item(index.row(), index.column());

  if (this_item->checkState() == Qt::Unchecked) setPercentage(index, 0.0);
  if (this_item->checkState() == Qt::Checked) setData(index, defaultPercent(index.row()));
}

double PercentModel::round(const double number) const {
  return floor(number * pow(10.0, numberOfDecimalPlaces) + .5) / pow(10.0, numberOfDecimalPlaces);
}

// Returns the default percent that is used by the given row
double PercentModel::defaultPercent(int row) const {
  double avg = round(100.0 / rowCount());
  if (row == rowCount() - 1) avg = round(avg + (100 - (avg * rowCount())));
  return avg;
}

bool PercentModel::setData(const QModelIndex& index, const QVariant& value, int role) {
  if (index.column() == percentColumn && role == Qt::EditRole) return setPercentage(index, value.toDouble());

  if (role == Qt::CheckStateRole) return setCheckedState(index, value);

  return QStandardItemModel::setData(index, value, role);
}

bool PercentModel::setCheckedState(const QModelIndex& index, const QVariant& value) {
  bool set_successfully = QStandardItemModel::setData(index, value, Qt::CheckStateRole);
  if (set_successfully) emit itemCheckedChanged(index);
  return set_successfully;
}

bool PercentModel::setPercentage(const QModelIndex& index, const double percent) {
  if (!index.isValid() || index.column() != percentColumn) return false;

  double old_percent      = round(index.data().toDouble());
  double new_percent      = round(percent);
  bool   set_successfully = QStandardItemModel::setData(index, round(percent));
  if (new_percent != old_percent) {
    if (new_percent == 0.0)
      item(index.row(), percentColumn)->setCheckState(Qt::Unchecked);
    else
      item(index.row(), percentColumn)->setCheckState(Qt::Checked);

    emit percentageChanged(index.row());
  }
  return set_successfully;
}

bool PercentModel::setPercentage(const int row, const double percent) {
  return setPercentage(index(row, percentColumn), percent);
}

double PercentModel::percentage(const int row) const { return data(index(row, percentColumn)).toDouble(); }

double PercentModel::totalPercentageUsed() {
  double sum = 0.0;
  for (int row = 0; row < rowCount(); row++) {
    sum += percentage(row);
  }
  return sum;
}