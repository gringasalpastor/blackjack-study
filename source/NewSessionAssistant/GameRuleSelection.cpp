#include "GameRuleSelection.h"

#include <QButtonGroup>

GameRuleSelection::GameRuleSelection(const QString& text, QWidget* parent)
    : QWidget(parent), my_button(new QRadioButton(text)) {
  QLayout* layout = new QVBoxLayout();
  layout->addWidget(button());
  setLayout(layout);
  connect(button(), SIGNAL(clicked(bool)), this, SLOT(handleButtonSelection()));
}