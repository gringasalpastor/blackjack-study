#ifndef PERCENTMODEL_H
#define PERCENTMODEL_H

#include <QStandardItemModel>

class PercentModel : public QStandardItemModel {
  Q_OBJECT
 public:
  PercentModel(const QStringList& labels, QObject* parent = 0);
  double percentage(const int row) const;
  bool   setPercentage(const QModelIndex& index, const double percent);
  bool   setPercentage(const int row, const double percent);
  bool   underOrOverAllocated() { return totalPercentageUsed() != 100.0; }
  bool   setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
  double totalPercentageUsed();
 signals:
  void itemCheckedChanged(const QModelIndex& index);
  void percentageChanged(const int row);

 private:
  bool   setCheckedState(const QModelIndex& index, const QVariant& value);
  double defaultPercent(int row) const;
  double round(const double number) const;
  int    percentColumn;
  int    labelColumn;
  int    numberOfDecimalPlaces;
 private slots:
  void handleItemCheckedChange(const QModelIndex& index);
};
#endif
