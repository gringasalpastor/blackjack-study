#include "MainWindow.h"

#include <cardcache.h>
#include <carddeckinfo.h>
#include <kcarddialog.h>
#include <kconfiggroup.h>
#include <ktoggleaction.h>

#include <KActionCollection>
#include <KSharedConfig>
#include <KStandardAction>
#include <KXmlGuiWindow>
#include <QAction>
#include <QApplication>
#include <QIcon>
#include <QKeySequence>
#include <QWebView>
#include <QtGui>

#include "HandDisplay.h"
#include "NewSessionAssistant.h"
#include "SessionSettings.h"
#include "SideBar.h"

MainWindow::MainWindow(QWidget* parent) : KXmlGuiWindow(parent), myCardCache(0) {
  initCardTheme();

  // Set up central widget
  QWidget* central_widget = new QWidget;
  ui.setupUi(central_widget);
  setCentralWidget(central_widget);

  // Set up hand displays
  ui.Dealers_hand_display->init("Dealers's Hand", myCardCache, true);
  ui.Players_hand_display->init("Player's Hand", myCardCache, false);
  connect(this, SIGNAL(themeChanged()), ui.Players_hand_display, SLOT(slotRedrawCards()));
  connect(this, SIGNAL(themeChanged()), ui.Dealers_hand_display, SLOT(slotRedrawCards()));

  // set up configurationGeneration
  configuration = configurationGenerater.generateConfiguration();

  // Set up hands
  ui.Dealers_hand_display->setCards(configuration.dealersHand.cards);
  ui.Players_hand_display->setCards(configuration.playersHand.cards);

  // charts sidebar
  QPixmap   p("/home/mike/Desktop/img_6305.jpg");
  QWebView* view = new QWebView(this);
  view->load(QUrl("https://wizardofodds.com/blackjack/images/bj_4d_s17.gif"));
  view->show();

  // History side bar
  QWidget* hist = new QWidget;
  historyUi.setupUi(hist);

  historyModel = new QStandardItemModel(0, 3, this);
  historyModel->setHeaderData(0, Qt::Horizontal, tr("Dealer"));
  historyModel->setHeaderData(1, Qt::Horizontal, tr("Player"));
  historyModel->setHeaderData(2, Qt::Horizontal, tr("Response"));

  historyUi.history_table->setModel(historyModel);
  // Save a little vertical space
  historyUi.history_table->resizeColumnToContents(0);
  historyUi.history_table->resizeColumnToContents(1);
  historyUi.history_table->resizeColumnToContents(2);
  // Don't let it get too small
  historyUi.history_table->setMinimumSize(QSize(270, 270));
  // Select only rows
  historyUi.history_table->setSelectionBehavior(QAbstractItemView::SelectRows);

  ui.side_bar->append_tab(p, "Charts", view);
  ui.side_bar->append_tab(p, "History", hist);

  setupHandActionsAndConnection();
  setupGUI();
}

void MainWindow::setupHandActionsAndConnection() {
  // New training session
  QAction* new_training_Action = new QAction(this);
  new_training_Action->setText("New Session");
  new_training_Action->setIcon(QIcon::fromTheme("document-new"));

  actionCollection()->addAction("new_training_session", new_training_Action);
  connect(new_training_Action, SIGNAL(triggered(bool)), this, SLOT(slotHandleNewTrainingAction()));

  QAction* load_Action = new QAction(this);
  load_Action->setText("Load Session");
  load_Action->setIcon(QIcon::fromTheme("document-open"));
  actionCollection()->addAction("load_training_session", load_Action);
  QAction* save_Action = new QAction(this);
  save_Action->setText("Save Session");
  save_Action->setIcon(QIcon::fromTheme("document-save"));
  actionCollection()->addAction("save_training_session", save_Action);

  KStandardAction::quit(qApp, SLOT(quit()), actionCollection());
  QAction* select_deck_action = new QAction(this);
  select_deck_action->setText("Select Deck");
  select_deck_action->setShortcut(QKeySequence(Qt::Key_F10));
  actionCollection()->addAction("select_deck", select_deck_action);
  connect(select_deck_action, SIGNAL(triggered(bool)), SLOT(slotSelectDeck()));

  // Connect buttons with the slots to handle clicks
  connect(ui.Hit, SIGNAL(clicked()), this, SLOT(slotHandleHit()));
  connect(ui.Stand, SIGNAL(clicked()), this, SLOT(slotHandleStand()));
  connect(ui.Double, SIGNAL(clicked()), this, SLOT(slotHandleDouble()));
  connect(ui.Split, SIGNAL(clicked()), this, SLOT(slotHandleSplit()));
}

void MainWindow::slotSelectDeck() {
  KSharedConfig::Ptr shared_config = KSharedConfig::openConfig();
  KConfigGroup       config_group(shared_config, "General Settings");
  KCardWidget*       card_widget = new KCardWidget();
  card_widget->readSettings(config_group);

  KCardDialog dlg(card_widget);
  if (dlg.exec() == QDialog::Accepted) {
    card_widget->saveSettings(config_group);
    config_group.sync();
    updateCardTheme(config_group);
    emit themeChanged();
  }
}

void MainWindow::initCardTheme() {
  myCardCache               = new KCardCache();
  KSharedConfig::Ptr config = KSharedConfig::openConfig();
  KConfigGroup       config_group(config, "General Settings");
  myCardCache->setSize(QSize(50 * 1.5, 75 * 1.5));

  updateCardTheme(config_group);
}

void MainWindow::updateCardTheme(const KConfigGroup& config_group) {
  myCardCache->setDeckName(CardDeckInfo::deckName(config_group));
  myCardCache->loadTheme();
  myCardCache->invalidateCache();
}

void MainWindow::slotHandleHit() { handlePlay(HandValidator::Hit); }
void MainWindow::slotHandleStand() { handlePlay(HandValidator::Stand); }
void MainWindow::slotHandleDouble() { handlePlay(HandValidator::Double); }
void MainWindow::slotHandleSplit() { handlePlay(HandValidator::Split); }

void MainWindow::handlePlay(HandValidator::Action a) {
  // Only show status after first action
  ui.Status->setHidden(false);

  ui.Status->setText("<font color='green'>correct</font>");

  // Update history
  int row = historyModel->rowCount();
  historyModel->insertRow(row, QModelIndex());
  historyModel->setData(historyModel->index(row, 0, QModelIndex()), configuration.dealersHand.sum);
  historyModel->setData(historyModel->index(row, 1, QModelIndex()), configuration.playersHand.sum);
  historyModel->setData(historyModel->index(row, 2, QModelIndex()), HandValidator::actionToString(a));
  // Save horzontal space
  historyUi.history_table->resizeRowToContents(row);

  // Set new configuration
  configuration = configurationGenerater.generateConfiguration();
  ui.Dealers_hand_display->setCards(configuration.dealersHand.cards);
  ui.Players_hand_display->setCards(configuration.playersHand.cards);
}

void MainWindow::slotHandleNewTrainingAction() {
  NewSessionAssistant* dialog = new NewSessionAssistant(this);
  dialog->setWindowTitle("Configure New Session");
  dialog->exec();

  if (dialog->result() == QDialog::Accepted) {
    configurationGenerater.setSessionSettings(dialog->getSessionSettings());
  }
}
