#ifndef LASVEGASSELECTION_H
#define LASVEGASSELECTION_H

#include "GameRuleSelection.h"

class LasVegasSelection : public GameRuleSelection {
  Q_OBJECT
 public:
  LasVegasSelection(QWidget* parent = 0);
  QString  name() override { return QString("Las Vegas"); }
  int      numDecks() override;
  bool     dealerStandsOnSoft17() override;
  DoubleOn doublingTimes() override;
  bool     doubleAfterSplits() override;
  bool     dealerPeeks() override;
};

#endif