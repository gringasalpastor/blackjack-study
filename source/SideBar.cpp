#include "SideBar.h"

#include <kmultitabbar.h>

#include <QGridLayout>
#include <QStackedWidget>
#include <QtGui>

SideBar::SideBar(QWidget* parent, KMultiTabBar::KMultiTabBarPosition ori)
    : QWidget(parent), active(false), currentTabIndex(-1), numberOfTabs(0) {
  myTabBar = new KMultiTabBar(ori, this);
  myTabBar->setStyle(KMultiTabBar::KDEV3ICON);
  stack = new QStackedWidget(this);
  stack->hide();
  grid = new QGridLayout();
  if (ori == KMultiTabBar::Right) {
    grid->addWidget(stack, 0, 0);
    grid->addWidget(myTabBar, 0, 1);
  }
  setLayout(grid);
}

void SideBar::append_tab(QPixmap Icon, QString Text, QWidget* Widget) {
  stack->insertWidget(numberOfTabs, Widget);
  myTabBar->appendTab(QIcon(Icon), numberOfTabs, Text);
  connect(myTabBar->tab(numberOfTabs), SIGNAL(clicked(int)), this, SLOT(slotTabClicked(int)));
  numberOfTabs++;
}

void SideBar::slotTabClicked(int id) {
  // Switch tabs
  if (active && id != currentTabIndex) {
    currentTabIndex = id;
    stack->setCurrentWidget(stack->widget(id));
    return;
  }
  // Hide tab
  if (active && id == currentTabIndex) {
    currentTabIndex = -1;
    active          = !active;
    stack->hide();
    grid->update();
    return;
  }
  // Activate tab
  if (!active) {
    currentTabIndex = id;
    stack->setCurrentWidget(stack->widget(id));
    stack->show();
    active = !active;
    return;
  }
}
