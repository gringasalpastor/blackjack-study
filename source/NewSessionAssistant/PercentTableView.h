#ifndef PERCENTTABLEVIEW_H
#define PERCENTTABLEVIEW_H

#include <QTableView>

class PercentModel;

class PercentTableView : public QTableView {
  Q_OBJECT
 public:
  PercentTableView(QWidget* parent = 0);
  PercentModel* percentModel() const;
  void          setMinimumSize();
};

#endif