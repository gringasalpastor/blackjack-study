#include "SessionSettings.h"

SessionSettings SessionSettings::generateDefaultSession() {
  SessionSettings session;
  session.handType << 25 << 25 << 25 << 25;
  session.previouslyMissed << 33.34 << 33.33 << 33.33;
  session.softHandPlayerPercentages << 11.12 << 11.11 << 11.11 << 11.11 << 11.11 << 11.11 << 11.11 << 11.11 << 11.11;
  session.softHandDealerPercentages << 10 << 10 << 10 << 10 << 10 << 10 << 10 << 10 << 10 << 10;
  session.hardHandPlayerPercentages << 10 << 10 << 10 << 10 << 10 << 10 << 10 << 10 << 10 << 10;
  session.hardHandDealerPercentages << 10 << 10 << 10 << 10 << 10 << 10 << 10 << 10 << 10 << 10;
  session.pairedHandPlayerPercentages << 10 << 10 << 10 << 10 << 10 << 10 << 10 << 10 << 10 << 10;
  session.pairedHandDealerPercentages << 10 << 10 << 10 << 10 << 10 << 10 << 10 << 10 << 10 << 10;
  return session;
}
