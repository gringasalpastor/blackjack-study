#include "GameRulesSelector.h"

#include <QButtonGroup>
#include <QGroupBox>
#include <QList>
#include <QtGui>

#include "AlanticCitySelection.h"
#include "LasVegasSelection.h"
#include "LasVegasStripSelection.h"
#include "ManualSelection.h"
#include "RenoSelection.h"

GameRulesSelector::GameRulesSelector(QWidget* parent)
    : QWidget(parent),
      buttonGroup(new QButtonGroup()),
      vLayout(new QVBoxLayout()),
      leftBox(new QGroupBox("Blackjack rules")),
      rightBox(new QGroupBox("Summary of rules")),
      summaryLabel(new QLabel()) {
  setupSelections();
  setupWidgets();
}

void GameRulesSelector::setupWidgets() {
  // Put the vertical layout inside of a gridlayout to keep it from expanding vertically too much
  QGridLayout* g_layout = new QGridLayout();
  g_layout->addLayout(vLayout, 0, 0, Qt::AlignTop);
  leftBox->setLayout(g_layout);

  // Right
  rightBox->setLayout(new QGridLayout());
  rightBox->layout()->addWidget(summaryLabel);
  rightBox->layout()->setAlignment(Qt::AlignTop);

  // Set up main
  QHBoxLayout* h_layout = new QHBoxLayout();
  h_layout->addWidget(leftBox);
  h_layout->addWidget(rightBox);

  setLayout(h_layout);
}

void GameRulesSelector::setupSelections() {
  QList<GameRuleSelection*> selections = QList<GameRuleSelection*>();
  selections << new LasVegasStripSelection() << new LasVegasSelection() << new RenoSelection()
             << new AlanticCitySelection() << new ManualSelection();

  QList<GameRuleSelection*>::const_iterator i;
  for (i = selections.constBegin(); i != selections.constEnd(); ++i) {
    connect(*i, SIGNAL(selected(GameRuleSelection*)), this, SLOT(handleSelectionChange(GameRuleSelection*)));
    connect(*i, SIGNAL(dataChanged(GameRuleSelection*)), this, SLOT(handleSelectionChange(GameRuleSelection*)));
    buttonGroup->addButton((*i)->button());
    vLayout->addWidget(*i);
  }

  // Make the first selection selected by default
  currentSelection = selections.at(0);
  currentSelection->button()->setChecked(true);
  handleSelectionChange(currentSelection);
}

void GameRulesSelector::handleSelectionChange(GameRuleSelection* selection) {
  currentSelection = selection;

  QString doubling_times("");
  switch (selection->doublingTimes()) {
    case GameRuleSelection::AnyTwoCards:
      doubling_times.append("any 2 cards");
      break;
    case GameRuleSelection::Only_9_10_11:
      doubling_times.append("9, 10, or 11");
      break;
    case GameRuleSelection::Only_10_11:
      doubling_times.append("10 or 11");
      break;
  }

  summaryLabel->setText("Decks: " + QVariant(selection->numDecks()).toString() + "\n\n" +
                        "Stands on Soft 17: " + (selection->dealerStandsOnSoft17() ? "True" : "False") + "\n\n" +
                        "Double on: " + doubling_times + "\n\n" +
                        "Double after splits: " + (selection->doubleAfterSplits() ? "True" : "False") + "\n\n" +
                        "Dealer peeks: " + (selection->dealerPeeks() ? "True" : "False"));
}
