#include "NewSessionAssistant.h"

#include <QMap>
#include <QtGui>

#include "GameRulesSelector.h"
#include "OverallPage.h"
#include "PercentModel.h"
#include "PercentTableView.h"
#include "SessionSettings.h"
#include "TwoTabledPage.h"

NewSessionAssistant::NewSessionAssistant(QWidget* parent) : KAssistantDialog(parent) {
  addPage(new GameRulesSelector(), "Blackjack Rules");
  initOverallPage();
  initTwoTabledPages();
  connect(this, SIGNAL(user1Clicked()), this, SLOT(handleFinishedClicked()));

  updateAdvancedPages();
}

void NewSessionAssistant::initOverallPage() {
  QStringList vertical_headers;
  vertical_headers << "Hard"
                   << "Soft"
                   << "Paired"
                   << "Missed";
  overallPage           = new OverallPage(vertical_headers, this);
  KPageWidgetItem* item = addPage(overallPage, "Setup Overall Percentages");
  widgetToItem.insert(overallPage, item);

  connect(overallPage, SIGNAL(pageValidityChanged(QWidget*, bool)), this, SLOT(handleValidityChange(QWidget*, bool)));
  connect(overallPage, SIGNAL(advancedSelectionChanged(bool)), this, SLOT(updateAdvancedPages()));
  connect(overallPage->table()->percentModel(), SIGNAL(itemCheckedChanged(const QModelIndex&)), this,
          SLOT(updateAdvancedPages()));
}

void NewSessionAssistant::initTwoTabledPages() {
  QList<QStringList> player_headers;
  QStringList        dealer_headers, discriptions, hard_hand_player_headers, soft_hand_player_headers,
      paired_hand_player_headers;

  hard_hand_player_headers << "Eight"
                           << "Nine"
                           << "Ten"
                           << "Eleven"
                           << "Twelve"
                           << "Thirteen"
                           << "Fourteen"
                           << "Fifteen"
                           << "Sixteen"
                           << "Seventeen";

  soft_hand_player_headers << "Twos"
                           << "Threes"
                           << "Fours"
                           << "Fives"
                           << "Sixes"
                           << "Sevens"
                           << "Eights"
                           << "Nines"
                           << "Tens";

  paired_hand_player_headers << "Aces"
                             << "Twos"
                             << "Threes"
                             << "Fours"
                             << "Fives"
                             << "Sixes"
                             << "Sevens"
                             << "Eights"
                             << "Nines"
                             << "Tens";

  player_headers << soft_hand_player_headers << hard_hand_player_headers << paired_hand_player_headers;

  dealer_headers << "Aces"
                 << "Twos"
                 << "Threes"
                 << "Fours"
                 << "Fives"
                 << "Sixes"
                 << "Sevens"
                 << "Eights"
                 << "Nines"
                 << "Tens";

  discriptions << "Setup Hard Hands Percentages"
               << "Setup Soft Hands Percentages"
               << "Setup Paired Hands Percentages";

  for (int i = 0; i < player_headers.count(); ++i) {
    TwoTabledPage* page;
    page = new TwoTabledPage(player_headers[i], dealer_headers, this);
    advancedWidgetItems << addPage(page, discriptions[i]);
    widgetToItem.insert(page, advancedWidgetItems.last());
    connect(page, SIGNAL(pageValidityChanged(QWidget*, bool)), this, SLOT(handleValidityChange(QWidget*, bool)));
  }
}

void NewSessionAssistant::handleValidityChange(QWidget* page_widget, bool pageValidity) {
  setValid(widgetToItem.value(page_widget), pageValidity);
}

void NewSessionAssistant::updateAdvancedPages() {
  bool selected = overallPage->advancedSelected();
  for (int i = 0; i < advancedWidgetItems.count(); ++i) {
    bool checked = (static_cast<PercentModel*>(overallPage->table()->model())->item(i)->checkState()) == Qt::Checked
                       ? true
                       : false;
    setAppropriate(advancedWidgetItems[i], selected && checked);
  }
}

void NewSessionAssistant::copyModelDataToSessionSettings(PercentModel* model, QList<double>& list) {
  list.clear();
  for (int i = 0; i < model->rowCount(); i++) {
    list << model->data(model->index(i, 0, QModelIndex())).toDouble();
  }
}

void NewSessionAssistant::handleFinishedClicked() {
  copyModelDataToSessionSettings((PercentModel*)(overallPage->table()->model()), sessionSettings.handType);
}
