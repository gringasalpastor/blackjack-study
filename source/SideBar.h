#ifndef SIDE_BAR_H
#define SIDE_BAR_H

#include <kmultitabbar.h>

class KMultiTabBar;
class QHBoxLayout;
class KMultitabBar;
class QHBoxLayout;
class QStackedWidget;
class QGridLayout;
class QWidget;
class SideBar_Item;

class SideBar : public QWidget {
  Q_OBJECT
 public:
  SideBar(QWidget* parent = 0, KMultiTabBar::KMultiTabBarPosition ori = KMultiTabBar::Right);
  void append_tab(QPixmap Icon, QString Text, QWidget* Widget);

 private:
  KMultiTabBar*   myTabBar;
  QStackedWidget* stack;
  QGridLayout*    grid;
  bool            active;
  int             currentTabIndex;
  int             numberOfTabs;
 private slots:
  void slotTabClicked(int id);
};

#endif
