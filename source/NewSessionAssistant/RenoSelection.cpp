#include "RenoSelection.h"

#include <QtGui>

RenoSelection::RenoSelection(QWidget* parent) : GameRuleSelection("Reno", parent) {}
int                     RenoSelection::numDecks() { return 1; }
bool                    RenoSelection::dealerStandsOnSoft17() { return true; }
RenoSelection::DoubleOn RenoSelection::doublingTimes() { return GameRuleSelection::AnyTwoCards; }
bool                    RenoSelection::doubleAfterSplits() { return true; }
bool                    RenoSelection::dealerPeeks() { return true; }
