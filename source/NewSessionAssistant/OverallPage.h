#ifndef OVERALLPAGE_H
#define OVERALLPAGE_H

#include "AbstractPage.h"

class QCheckBox;
class PercentTableView;
class QModelIndex;

class OverallPage : public AbstractPage {
  Q_OBJECT
 public:
  OverallPage(const QStringList& headers, QWidget* parent = 0);
  PercentTableView* table() { return percentTable; }
  bool              previouslyMissedAt100();
  bool              underOrOverAllocated();
  bool              advancedSelected();
 private slots:
  void updateValidity();
  void handleAdvancedToggled(bool value);
 signals:
  void advancedSelectionChanged(bool value);

 private:
  PercentTableView* percentTable;
  QCheckBox*        advanced;
};

#endif