#ifndef GAME_RULES_SELECTOR_H
#define GAME_RULES_SELECTOR_H

#include <QWidget>

class QButtonGroup;
class QVBoxLayout;
class QGroupBox;
class GameRuleSelection;
class QLabel;

class GameRulesSelector : public QWidget {
  Q_OBJECT
 public:
  GameRulesSelector(QWidget* parent = 0);
  GameRuleSelection* getCurrentSelection() { return currentSelection; }

 private:
  void               setupSelections();
  void               setupWidgets();
  QButtonGroup*      buttonGroup;
  QVBoxLayout*       vLayout;
  QGroupBox*         leftBox;
  QGroupBox*         rightBox;
  QLabel*            summaryLabel;
  GameRuleSelection* currentSelection;
 private slots:
  void handleSelectionChange(GameRuleSelection* selection);
};

#endif
