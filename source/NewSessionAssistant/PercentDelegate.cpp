#include "PercentDelegate.h"

#include <PercentModel.h>

#include <QDoubleSpinBox>

PercentDelegate::PercentDelegate(QObject* parent) : QStyledItemDelegate(parent) {}
// NOTE: Index and option are marked unused since it must match the prototype
QWidget* PercentDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option __attribute__((unused)),
                                       const QModelIndex& index __attribute__((unused))) const {
  QDoubleSpinBox* box = new QDoubleSpinBox(parent);
  box->setRange(0, 100);
  box->setDecimals(2);
  box->setSuffix(" %");
  return box;
}

void PercentDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const {
  QDoubleSpinBox* spin_box = static_cast<QDoubleSpinBox*>(editor);
  spin_box->interpretText();
  model->setData(index, spin_box->value());
}

void PercentDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const {
  QDoubleSpinBox* spin_box = static_cast<QDoubleSpinBox*>(editor);
  spin_box->setValue(index.data().toDouble());
}

QString PercentDelegate::displayText(const QVariant& value, const QLocale& /*locale*/) const {
  return value.toString() + " %";
}