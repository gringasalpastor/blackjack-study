#ifndef RENOSELECTION_H
#define RENOSELECTION_H

#include "GameRuleSelection.h"

class RenoSelection : public GameRuleSelection {
  Q_OBJECT
 public:
  RenoSelection(QWidget* parent = 0);

  QString  name() override { return QString("Reno"); }
  int      numDecks() override;
  bool     dealerStandsOnSoft17() override;
  DoubleOn doublingTimes() override;
  bool     doubleAfterSplits() override;
  bool     dealerPeeks() override;
};

#endif