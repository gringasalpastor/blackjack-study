#ifndef GAMECONFIGURATION_H
#define GAMECONFIGURATION_H

#include <cardcache.h>

#include <QList>

struct Hand {
  QList<KCardInfo> cards;
  int              sum;
};

struct GameConfiguration {
  enum ConfigurationType { Hard, Soft, Paired, PreviouslyMissed };

  ConfigurationType type;
  Hand              playersHand;
  Hand              dealersHand;
};

#endif