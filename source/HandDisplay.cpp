#include "HandDisplay.h"

#include <cardcache.h>
#include <carddeckinfo.h>
#include <kconfiggroup.h>

#include <KSharedConfig>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QtGui>

#include "GameConfigurationGenerater.h"

HandDisplay::HandDisplay(QWidget* parent) : QWidget(parent) {}
void HandDisplay::init(QString player, KCardCache* card_cache, bool dealer) {
  myCardCache = card_cache;
  playerStr   = player;
  isDealer    = dealer;

  cardGroup = NULL;
  scene     = new QGraphicsScene();
  view      = new QGraphicsView(scene);
  view->setMaximumSize(QSize(200, 200));
  view->setMinimumSize(QSize(200, 200));

  layout = new QVBoxLayout();
  layout->setAlignment(Qt::AlignCenter);
  layout->addWidget(new QLabel(player));
  layout->addWidget(view);
  setLayout(layout);

  scene->setSceneRect(0, 0, 200 - 2 * (view->frameWidth()), 200 - 2 * (view->frameWidth()));
}

void HandDisplay::setCards(const QList<KCardInfo>& cards) {
  int space = 15;  // Space between cards
  myCards   = cards;

  // Remove old cards from graphics scene and make a new group for the new cards
  scene->removeItem(cardGroup);
  delete cardGroup;
  cardGroup = new QGraphicsItemGroup();
  scene->addItem(cardGroup);

  // Draw the dealers down card if this is a display for the dealer
  int x = 1;
  if (isDealer) {
    QPixmap              p    = myCardCache->backside();
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(p);
    item->setPos(x * space, x * space);
    item->setZValue(x);  // Make it overlap the previous item
    cardGroup->addToGroup(item);
    x++;
  }
  // Draw the cards in myCards
  QList<KCardInfo>::const_iterator i;
  for (i = myCards.begin(); i != myCards.end(); ++i, x++) {
    QPixmap pix = myCardCache->frontside(*i);  // *i is a pointer and **i is the pointer dereferanced

    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pix);
    item->setPos(x * space, x * space);
    item->setZValue(x);  // Make it overlap the previous item
    cardGroup->addToGroup(item);
  }
}

void HandDisplay::slotRedrawCards() {
  for (int i = 0; i != myCards.size(); i++) {
    myCards[i] = KCardInfo(myCards[i].suit(), myCards[i].card());
  }
  setCards(myCards);
}
