#ifndef ABSTRACTPAGE_H
#define ABSTRACTPAGE_H

#include <QWidget>

class AbstractPage : public QWidget {
  Q_OBJECT
 public:
  AbstractPage(QWidget* parent = 0);
  virtual bool validity() { return pageValidity; }

 protected:
  bool pageValidity;
 signals:
  void pageValidityChanged(QWidget* page_widget, bool pageValidity);
};

#endif
