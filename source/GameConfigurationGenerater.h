#ifndef GAMECONFIGURATIONGENERATER_H
#define GAMECONFIGURATIONGENERATER_H

#include "GameConfiguration.h"
#include "SessionSettings.h"

class KCardInfo;

class GameConfigurationGenerater {
 public:
  GameConfigurationGenerater();
  GameConfiguration generateConfiguration();
  void              setSessionSettings(const SessionSettings& s);
  SessionSettings   getSessionSettings() { return sessionSettings; }

 private:
  SessionSettings sessionSettings;

  Hand generateDealersHand(GameConfiguration::ConfigurationType type);
  Hand generatePlayersHand(GameConfiguration::ConfigurationType type);

  // Players card generators
  Hand generateHardHandPlayer();
  Hand generateSoftHandPlayer();
  Hand generatePairedHandPlayer();

  // Mapping from an index to it's corrosponding number
  QList<int> softHandPlayerNumber;
  QList<int> softHandDealerNumber;
  QList<int> hardHandPlayerNumber;
  QList<int> hardHandDealerNumber;
  QList<int> pairedHandPlayerNumber;
  QList<int> pairedHandDealerNumber;

  KCardInfo::Suit generateSuit();
  KCardInfo::Card generateTen();
  KCardInfo       convertNumberToCardInfo(int num);

  int                                  generateIndex(QList<double> percentages);
  GameConfiguration::ConfigurationType generateConfigurationType();
};

#endif
