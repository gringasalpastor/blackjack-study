#ifndef ALANTICCITYSELECTION_H
#define ALANTICCITYSELECTION_H

#include "GameRuleSelection.h"

class AlanticCitySelection : public GameRuleSelection {
  Q_OBJECT
 public:
  AlanticCitySelection(QWidget* parent = 0);
  QString  name() override { return QString("Alantic City"); }
  int      numDecks() override;
  bool     dealerStandsOnSoft17() override;
  DoubleOn doublingTimes() override;
  bool     doubleAfterSplits() override;
  bool     dealerPeeks() override;
};

#endif