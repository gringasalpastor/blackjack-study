#include "ManualSelection.h"

#include <assert.h>

#include <QSpinBox>
#include <QtGui>

ManualSelection::ManualSelection(QWidget* parent)
    : GameRuleSelection("Manually Select", parent), ManualInput(new QWidget()) {
  ManualInput->hide();
  manualInputUI.setupUi(ManualInput);
  manualInputUI.numberOfDecksIntSpinBox->setSuffix(" Decks");
  manualInputUI.numberOfDecksIntSpinBox->setSpecialValueText("1 Deck");

  layout()->addWidget(ManualInput);

  // Set up signals/slots to show and hide as needed
  connect(button(), SIGNAL(toggled(bool)), this, SLOT(slotHandleToggle(bool)));

  // Emit signal when data changes
  connect(manualInputUI.dealerPeeksUSStyleCheckBox, SIGNAL(stateChanged(int)), this, SLOT(handleDataChange()));
  connect(manualInputUI.dealerStandsOnSoft17CheckBox, SIGNAL(stateChanged(int)), this, SLOT(handleDataChange()));
  connect(manualInputUI.numberOfDecksIntSpinBox, SIGNAL(valueChanged(int)), this, SLOT(handleDataChange()));
  connect(manualInputUI.playerCanDoubleAfterSplitsCheckBox, SIGNAL(stateChanged(int)), this, SLOT(handleDataChange()));
  connect(manualInputUI.playerCanDoubleOnComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(handleDataChange()));
}

int ManualSelection::numDecks() { return manualInputUI.numberOfDecksIntSpinBox->value(); }

bool ManualSelection::dealerStandsOnSoft17() { return manualInputUI.dealerStandsOnSoft17CheckBox->isChecked(); }

ManualSelection::DoubleOn ManualSelection::doublingTimes() {
  if (manualInputUI.playerCanDoubleOnComboBox->currentText() == "Any 2 Cards") return GameRuleSelection::AnyTwoCards;
  if (manualInputUI.playerCanDoubleOnComboBox->currentText() == "9, 10, or 11 Only")
    return GameRuleSelection::Only_9_10_11;
  if (manualInputUI.playerCanDoubleOnComboBox->currentText() == "10 or 11 Only") return GameRuleSelection::Only_10_11;
  assert(false);
  return GameRuleSelection::AnyTwoCards;
}

bool ManualSelection::doubleAfterSplits() { return manualInputUI.playerCanDoubleAfterSplitsCheckBox->isChecked(); }

bool ManualSelection::dealerPeeks() { return manualInputUI.dealerPeeksUSStyleCheckBox->isChecked(); }

void ManualSelection::slotHandleToggle(bool checked) {
  if (checked)
    ManualInput->show();
  else
    ManualInput->hide();
}