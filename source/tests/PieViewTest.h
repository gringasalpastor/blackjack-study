#ifndef PIEVIEWTEST_H
#define PIEVIEWTEST_H

#include <QMainWindow>
#include <QtGui>

#include "PercentModel.h"
#include "PieView.h"

class PieViewTest : public QObject {
  Q_OBJECT

 private:
  PercentModel* model;
  PieView*      pieView;
  QStringList   labels;
  QMainWindow*  window;

  QPoint top_left_quad;
  QPoint top_right_quad;
  QPoint bottom_left_quad;
  QPoint bottom_right_quad;
  QPoint first_label;
  QPoint last_label;

 private Q_SLOTS:
  void init();
  void initTestCase();
  void cleanupTestCase();

  void testVisualRect();
  void testScrollTo();
  void testIndexAt();
  void testMoveCursor();
  void testNumberOfItems();
};

#endif