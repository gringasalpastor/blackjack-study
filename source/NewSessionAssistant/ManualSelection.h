#ifndef MANUALSELECTION_H
#define MANUALSELECTION_H

#include "GameRuleSelection.h"
#include "ui_ManualInput.h"

class ManualSelection : public GameRuleSelection {
  Q_OBJECT
 public:
  ManualSelection(QWidget* parent = 0);

  QString  name() override { return QString("Manual"); }
  int      numDecks() override;
  bool     dealerStandsOnSoft17() override;
  DoubleOn doublingTimes() override;
  bool     doubleAfterSplits() override;
  bool     dealerPeeks() override;
 private slots:
  void slotHandleToggle(bool checked);

 private:
  QWidget*        ManualInput;
  Ui::ManualInput manualInputUI;
};

#endif