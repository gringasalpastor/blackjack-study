#ifndef LASVEGASSTRIPSELECTION_H
#define LASVEGASSTRIPSELECTION_H

#include "GameRuleSelection.h"

class LasVegasStripSelection : public GameRuleSelection {
  Q_OBJECT
 public:
  LasVegasStripSelection(QWidget* parent = 0);

  QString  name() override { return QString("Las Vegas Strip"); }
  int      numDecks() override;
  bool     dealerStandsOnSoft17() override;
  DoubleOn doublingTimes() override;
  bool     doubleAfterSplits() override;
  bool     dealerPeeks() override;
};

#endif