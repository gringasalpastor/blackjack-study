#include "TwoTabledPage.h"

// #include <kdebug.h>
// #include <ktabwidget.h>
#include <QGroupBox>
#include <QLayout>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QtGui>

#include "PercentModel.h"
#include "PercentTableView.h"

TwoTabledPage::TwoTabledPage(const QStringList& player_labels, const QStringList& dealer_labels, QWidget* parent)
    : AbstractPage(parent),
      tabWidget(new QTabWidget()),
      playerWidget(new QWidget()),
      dealerWidget(new QWidget()),
      playerTableView(new PercentTableView(this)),
      dealerTableView(new PercentTableView(this)),
      pageValid(true)

{
  playerTableView->setModel(new PercentModel(dealer_labels));
  playerTableView->resizeColumnsToContents();
  playerTableView->resizeRowsToContents();
  playerTableView->setMinimumSize();
  dealerTableView->setModel(new PercentModel(player_labels));
  dealerTableView->resizeColumnsToContents();
  dealerTableView->resizeRowsToContents();
  dealerTableView->setMinimumSize();

  // setup UI
  setLayout(new QVBoxLayout());
  layout()->addWidget(tabWidget);
  tabWidget->addTab(playerWidget, "Player's Hand");
  // payer's tab
  QGroupBox* playerGroupBox = new QGroupBox("Overall Percentages");
  playerWidget->setLayout(new QVBoxLayout());
  playerWidget->layout()->addWidget(playerGroupBox);
  playerGroupBox->setLayout(new QVBoxLayout());
  playerGroupBox->layout()->addWidget(playerTableView);
  connect(playerTableView->percentModel(), SIGNAL(percentageChanged(int)), this, SLOT(handlePlayerPercentageChange()));

  // player's tab
  tabWidget->addTab(dealerWidget, "Dealer's Hand");
  QGroupBox* dealerGroupBox = new QGroupBox("Overall Percentages");
  dealerWidget->setLayout(new QVBoxLayout());
  dealerWidget->layout()->addWidget(dealerGroupBox);
  dealerGroupBox->setLayout(new QVBoxLayout());
  dealerGroupBox->layout()->addWidget(dealerTableView);
  connect(dealerTableView->percentModel(), SIGNAL(percentageChanged(int)), this, SLOT(handleDealerPercentageChange()));
}

void TwoTabledPage::handlePlayerPercentageChange() {
  bool mis_allocated = playerTableView->percentModel()->underOrOverAllocated();
  tabWidget->tabBar()->setTabTextColor(tabWidget->indexOf(playerWidget),
                                       mis_allocated ? QColor("red") : QColor("black"));
  // tabWidget->setTabTextColor(tabWidget->indexOf(playerWidget), mis_allocated ? QColor("red") : QColor("black"));
  updateValidity();
}

void TwoTabledPage::handleDealerPercentageChange() {
  bool mis_allocated = dealerTableView->percentModel()->underOrOverAllocated();
  tabWidget->tabBar()->setTabTextColor(tabWidget->indexOf(dealerWidget),
                                       mis_allocated ? QColor("red") : QColor("black"));
  updateValidity();
}

void TwoTabledPage::updateValidity() {
  bool player_mis_allocated = playerTableView->percentModel()->underOrOverAllocated();
  bool dealer_mis_allocated = dealerTableView->percentModel()->underOrOverAllocated();
  bool new_validity         = (!player_mis_allocated && !dealer_mis_allocated);
  bool old_validity         = pageValid;

  pageValid = new_validity;
  if (new_validity != old_validity) emit pageValidityChanged(this, new_validity);
}