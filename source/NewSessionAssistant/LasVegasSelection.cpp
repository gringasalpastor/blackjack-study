#include "LasVegasSelection.h"

#include <QtGui>

LasVegasSelection::LasVegasSelection(QWidget* parent) : GameRuleSelection("Las Vegas", parent) {}
int                         LasVegasSelection::numDecks() { return 1; }
bool                        LasVegasSelection::dealerStandsOnSoft17() { return true; }
LasVegasSelection::DoubleOn LasVegasSelection::doublingTimes() { return GameRuleSelection::AnyTwoCards; }
bool                        LasVegasSelection::doubleAfterSplits() { return true; }
bool                        LasVegasSelection::dealerPeeks() { return true; }
