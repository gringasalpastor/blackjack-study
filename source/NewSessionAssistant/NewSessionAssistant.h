#ifndef NEWSESSIONASSISTANT_H
#define NEWSESSIONASSISTANT_H

#include <kassistantdialog.h>

#include "SessionSettings.h"
#include "ui_PreviouslyMissedPage.h"

using namespace Ui;

class QTableView;
class PercentModel;
class OverallPage;

class NewSessionAssistant : public KAssistantDialog {
  Q_OBJECT
 public:
  NewSessionAssistant(QWidget* parent = 0);
  SessionSettings getSessionSettings() { return sessionSettings; }

 private:
  void initOverallPage();
  void initTwoTabledPages();
  void copyModelDataToSessionSettings(PercentModel* model, QList<double>& list);

  double round(double num, unsigned decimal_places);

  QList<KPageWidgetItem*>          advancedWidgetItems;
  QMap<QWidget*, KPageWidgetItem*> widgetToItem;
  OverallPage*                     overallPage;

  PreviouslyMissedPage previouslyMissedPage_ui;
  SessionSettings      sessionSettings;

 private slots:
  void handleValidityChange(QWidget* page_widget, bool pageValidity);
  void handleFinishedClicked();
  void updateAdvancedPages();
};

#endif
