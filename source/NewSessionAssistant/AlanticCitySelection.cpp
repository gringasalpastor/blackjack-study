#include "AlanticCitySelection.h"

#include <QtGui>

AlanticCitySelection::AlanticCitySelection(QWidget* parent) : GameRuleSelection("Alantic City", parent) {}
int                            AlanticCitySelection::numDecks() { return 1; }
bool                           AlanticCitySelection::dealerStandsOnSoft17() { return true; }
AlanticCitySelection::DoubleOn AlanticCitySelection::doublingTimes() { return GameRuleSelection::AnyTwoCards; }
bool                           AlanticCitySelection::doubleAfterSplits() { return true; }
bool                           AlanticCitySelection::dealerPeeks() { return true; }
