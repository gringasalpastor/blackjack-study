#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KXmlGuiWindow>

#include "HandValidator.h"
#include "ui_CentralWidget.h"
#include "ui_History.h"

class KConfigGroup;
class QWidget;
class KConfigGroup;
class Hand_display;
class KCardCache;
class HandValidator;
class QStandardItemModel;
class GameConfigurationGenerater;

class MainWindow : public KXmlGuiWindow {
  Q_OBJECT
 public:
  MainWindow(QWidget* parent = 0);

 private slots:
  void slotSelectDeck();
  void slotHandleHit();
  void slotHandleStand();
  void slotHandleDouble();
  void slotHandleSplit();
  void slotHandleNewTrainingAction();
 signals:
  void themeChanged();

 private:
  void setupHandActionsAndConnection();
  void initCardTheme();
  void updateCardTheme(const KConfigGroup& config);
  void handlePlay(HandValidator::Action a);

  KCardCache* myCardCache;

  Ui::central_widget         ui;
  Ui::History                historyUi;
  QStandardItemModel*        historyModel;
  GameConfigurationGenerater configurationGenerater;
  GameConfiguration          configuration;
};

#endif
