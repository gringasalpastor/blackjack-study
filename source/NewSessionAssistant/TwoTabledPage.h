#ifndef TWOTABLEDPAGE_H
#define TWOTABLEDPAGE_H

#include "AbstractPage.h"

class QTableView;
class QTabWidget;
class PercentTableView;

class TwoTabledPage : public AbstractPage {
  Q_OBJECT
 public:
  TwoTabledPage(const QStringList& player_vertical_headers, const QStringList& dealer_vertical_headers,
                QWidget* parent = 0);

 private:
  QTabWidget*       tabWidget;
  QWidget*          playerWidget;
  QWidget*          dealerWidget;
  PercentTableView* playerTableView;
  PercentTableView* dealerTableView;
  bool              pageValid;

 private slots:
  void updateValidity();
  void handlePlayerPercentageChange();
  void handleDealerPercentageChange();
};

#endif