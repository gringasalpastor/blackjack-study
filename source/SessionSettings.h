#ifndef SESSIONSETTINGS_H
#define SESSIONSETTINGS_H

#include <QList>

#include "GameRuleSelection.h"

class SessionSettings {
 public:
  static SessionSettings      generateDefaultSession();
  QString                     rule_name;
  int                         numDecks;
  bool                        dealerStandsOnSoft17;
  GameRuleSelection::DoubleOn doublingTimes;
  bool                        doubleAfterSplits;
  bool                        dealerPeeks;
  // Frequency data
  QList<double> handType;
  QList<double> previouslyMissed;
  QList<double> softHandPlayerPercentages;
  QList<double> softHandDealerPercentages;
  QList<double> hardHandPlayerPercentages;
  QList<double> hardHandDealerPercentages;
  QList<double> pairedHandPlayerPercentages;
  QList<double> pairedHandDealerPercentages;
};

#endif  // SESSIONSETTINGS_H
