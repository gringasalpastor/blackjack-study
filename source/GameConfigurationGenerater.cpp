#include "GameConfigurationGenerater.h"

#include <cardcache.h>

#include <QList>
#include <QtAlgorithms>
#include <cstdlib>
#include <ctime>

#include "HandDisplay.h"
#include "SessionSettings.h"

GameConfigurationGenerater::GameConfigurationGenerater() {
  sessionSettings = SessionSettings::generateDefaultSession();
  srand(time(nullptr));

  // Initialize lists that map indexes to their corrosponding number

  // Player
  softHandPlayerNumber << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10;
  hardHandPlayerNumber << 8 << 9 << 10 << 11 << 12 << 13 << 14 << 15 << 16 << 17;
  pairedHandPlayerNumber << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10;
  // Dealer
  softHandDealerNumber << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10;
  hardHandDealerNumber << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10;
  pairedHandDealerNumber << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10;
}

GameConfiguration GameConfigurationGenerater::generateConfiguration() {
  GameConfiguration config;
  // Skip PreviouslyMissed hands for now
  do {
    config.type = generateConfigurationType();
  } while (config.type == GameConfiguration::PreviouslyMissed);

  if (config.type != GameConfiguration::PreviouslyMissed) {
    config.dealersHand = generateDealersHand(config.type);
    config.playersHand = generatePlayersHand(config.type);
  } else {
    // TODO: handle previously missed
  }
  return config;
}
void GameConfigurationGenerater::setSessionSettings(const SessionSettings& s) { sessionSettings = s; }

Hand GameConfigurationGenerater::generateDealersHand(GameConfiguration::ConfigurationType type) {
  QList<int>    numArray;
  QList<double> percentages;

  switch (type) {
    case GameConfiguration::Hard:
      numArray    = hardHandDealerNumber;
      percentages = sessionSettings.hardHandDealerPercentages;
      break;
    case GameConfiguration::Soft:
      numArray    = softHandDealerNumber;
      percentages = sessionSettings.softHandDealerPercentages;
      break;
    case GameConfiguration::Paired:
      numArray    = pairedHandDealerNumber;
      percentages = sessionSettings.pairedHandDealerPercentages;
      break;
    default:
      return Hand();
  }
  Hand hand;
  int  num = numArray[generateIndex(percentages)];
  hand.cards << convertNumberToCardInfo(num);
  hand.sum = num;
  return hand;
}

Hand GameConfigurationGenerater::generatePlayersHand(GameConfiguration::ConfigurationType type) {
  switch (type) {
    case GameConfiguration::Hard:
      return generateHardHandPlayer();
    case GameConfiguration::Soft:
      return generateSoftHandPlayer();
    case GameConfiguration::Paired:
      return generatePairedHandPlayer();
    default:
      return Hand();
  }
}
Hand GameConfigurationGenerater::generateHardHandPlayer() { return generatePlayersHand(GameConfiguration::Paired); }

Hand GameConfigurationGenerater::generateSoftHandPlayer() {
  Hand hand;
  int  num = softHandPlayerNumber[generateIndex(sessionSettings.softHandPlayerPercentages)];
  hand.cards << KCardInfo(generateSuit(), KCardInfo::Ace) << convertNumberToCardInfo(num);
  hand.sum = num + 1;
  return hand;
}

Hand GameConfigurationGenerater::generatePairedHandPlayer() {
  Hand hand;
  int  num = pairedHandPlayerNumber[generateIndex(sessionSettings.pairedHandPlayerPercentages)];
  hand.sum = 2 * num;

  // Make sure 10's have the same 2 cards
  if (num == 10) {
    KCardInfo info1 = KCardInfo(generateSuit(), generateTen());
    KCardInfo info2 = KCardInfo(generateSuit(), info1.card());
    hand.cards << info1 << info2;
  } else {
    hand.cards << convertNumberToCardInfo(num) << convertNumberToCardInfo(num);
  }
  return hand;
}

KCardInfo GameConfigurationGenerater::convertNumberToCardInfo(int num) {
  switch (num) {
    case 1:
      return KCardInfo(generateSuit(), KCardInfo::Ace);
    case 2:
      return KCardInfo(generateSuit(), KCardInfo::Two);
    case 3:
      return KCardInfo(generateSuit(), KCardInfo::Three);
    case 4:
      return KCardInfo(generateSuit(), KCardInfo::Four);
    case 5:
      return KCardInfo(generateSuit(), KCardInfo::Five);
    case 6:
      return KCardInfo(generateSuit(), KCardInfo::Six);
    case 7:
      return KCardInfo(generateSuit(), KCardInfo::Seven);
    case 8:
      return KCardInfo(generateSuit(), KCardInfo::Eight);
    case 9:
      return KCardInfo(generateSuit(), KCardInfo::Nine);
    case 10:
      return KCardInfo(generateSuit(), generateTen());
    default:
      return KCardInfo(KCardInfo::None, KCardInfo::Joker);
  }
}

GameConfiguration::ConfigurationType GameConfigurationGenerater::generateConfigurationType() {
  switch (generateIndex(sessionSettings.handType)) {
    case 0:
      return GameConfiguration::Soft;
    case 1:
      return GameConfiguration::Hard;
    case 2:
      return GameConfiguration::Paired;
    case 3:
      return GameConfiguration::PreviouslyMissed;
    default:
      return GameConfiguration::ConfigurationType();
  }
}

// Index in the range of (1,n) based on the list of percentages given distrbution given
int GameConfigurationGenerater::generateIndex(QList<double> percentages) {
  double random = 100.0 * (rand() / static_cast<double>(RAND_MAX));
  double sum    = 0;
  int    i      = 0;
  for (; sum <= random; i++) {
    sum += percentages[i];
  }
  return i - 1;
}
KCardInfo::Suit GameConfigurationGenerater::generateSuit() {
  switch (rand() % 4) {
    case 0:
      return KCardInfo::Heart;
    case 1:
      return KCardInfo::Spade;
    case 2:
      return KCardInfo::Diamond;
    case 3:
      return KCardInfo::Club;
    default:
      return KCardInfo::None;
  }
}

KCardInfo::Card GameConfigurationGenerater::generateTen() {
  switch (rand() % 4) {
    case 0:
      return KCardInfo::Ten;
    case 1:
      return KCardInfo::Jack;
    case 2:
      return KCardInfo::Queen;
    case 3:
      return KCardInfo::King;
    default:
      return KCardInfo::Joker;
  }
}
