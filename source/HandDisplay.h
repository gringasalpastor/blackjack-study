#ifndef HAND_DISPLAY_H
#define HAND_DISPLAY_H

#include <QWidget>

#include "GameConfigurationGenerater.h"

class KCardCache;
class QString;
class QVBoxLayout;
class QGraphicsItemGroup;
class QGraphicsScene;
class QGraphicsView;
class QSize;
class KCardInfo;
class HandGenerater;
class Hand;

template <typename T>
class QList;

class HandDisplay : public QWidget {
  Q_OBJECT
 public:
  HandDisplay(QWidget* parent = 0);
  void init(QString player, KCardCache* card_cache, bool dealer);
  void setCards(const QList<KCardInfo>& cards);

 private slots:
  void slotRedrawCards();

 private:
  KCardCache*  myCardCache;
  QVBoxLayout* layout;

  QString          playerStr;
  bool             isDealer;
  QList<KCardInfo> myCards;

  QGraphicsItemGroup* cardGroup;
  QGraphicsScene*     scene;
  QGraphicsView*      view;
};

#endif
