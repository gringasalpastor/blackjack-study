#ifndef GAMERULESELECTION_H
#define GAMERULESELECTION_H

#include <QAbstractButton>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QWidget>

class GameRuleSelection : public QWidget {
  Q_OBJECT
 public:
  enum DoubleOn { AnyTwoCards, Only_9_10_11, Only_10_11 };

  GameRuleSelection(const QString& text, QWidget* parent = 0);
  virtual int      numDecks()             = 0;
  virtual bool     dealerStandsOnSoft17() = 0;
  virtual DoubleOn doublingTimes()        = 0;
  virtual bool     doubleAfterSplits()    = 0;
  virtual bool     dealerPeeks()          = 0;
  virtual QString  name()                 = 0;
  QAbstractButton* button() { return my_button; }
 signals:
  void selected(GameRuleSelection* selection);
  void dataChanged(GameRuleSelection* selection);

 protected:
  QAbstractButton* my_button;
 private slots:
  void handleButtonSelection() { emit selected(this); }
  void handleDataChange() { emit dataChanged(this); }
};

#endif  // GAMERULESELECTION_H
