#include "LasVegasStripSelection.h"

#include <QtGui>

LasVegasStripSelection::LasVegasStripSelection(QWidget* parent) : GameRuleSelection("Las Vegas Strip", parent) {}
int                              LasVegasStripSelection::numDecks() { return 1; }
bool                             LasVegasStripSelection::dealerStandsOnSoft17() { return true; }
LasVegasStripSelection::DoubleOn LasVegasStripSelection::doublingTimes() { return GameRuleSelection::AnyTwoCards; }
bool                             LasVegasStripSelection::doubleAfterSplits() { return true; }
bool                             LasVegasStripSelection::dealerPeeks() { return true; }
