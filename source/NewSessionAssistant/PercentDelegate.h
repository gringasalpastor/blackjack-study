#ifndef PERCENTDELEGATE_H
#define PERCENTDELEGATE_H

#include <QStyledItemDelegate>

class PercentDelegate : public QStyledItemDelegate {
 public:
  PercentDelegate(QObject* parent = 0);
  void     setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;
  QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
  void     setEditorData(QWidget* editor, const QModelIndex& index) const override;
  QString  displayText(const QVariant& value, const QLocale& locale) const override;
};

#endif
