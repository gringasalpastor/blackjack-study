#include "PieViewTest.h"

#include <QScrollBar>
#include <QTest>

void PieViewTest::initTestCase() {
  window = new QMainWindow();
  labels << "a"
         << "b"
         << "c"
         << "d"
         << "e";
  model   = new PercentModel(labels, this);
  pieView = new PieView();
  pieView->setModel(model);
  // No scroll bars to make calulations easier
  pieView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  pieView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  int frame_size = pieView->frameWidth();
  window->resize(pieView->pieDiameter() + frame_size * 2, pieView->pieDiameter() + frame_size * 2);

  top_left_quad     = QPoint(60, 15);
  top_right_quad    = QPoint(145, 15);
  bottom_left_quad  = QPoint(60, 140);
  bottom_right_quad = QPoint(145, 140);
  int x             = pieView->legendOrigin().x();
  // Use -1 to be on last pixle that is ok
  int y       = pieView->legendOrigin().y() + pieView->legendHeight() - 1;
  last_label  = QPoint(x, y);
  first_label = pieView->legendOrigin();

  window->setCentralWidget(pieView);
  window->show();
  std::ignore = QTest::qWaitForWindowExposed(window);
}

void PieViewTest::init() {}
void PieViewTest::cleanupTestCase() {
  delete pieView;
  delete model;
}

// Item's rect relative to the viewport
void PieViewTest::testVisualRect() {
  // Test a label item
  int   item_index  = 1;
  QRect actual_rect = pieView->visualRect(model->index(item_index, 0));
  QRect expected_rect =
      QRect(pieView->legendOrigin().x(), pieView->legendOrigin().y() + pieView->labelHeight() * item_index,
            pieView->labelWidth(), pieView->labelHeight());
  QCOMPARE(actual_rect, expected_rect);

  // Test a data item
  actual_rect   = pieView->visualRect(model->index(item_index, 1));
  expected_rect = QRect(0, 0, pieView->pieDiameter(), pieView->pieDiameter());
  QCOMPARE(actual_rect, expected_rect);

  // Scroll down 10 pixles
  pieView->verticalScrollBar()->setValue(10);
  actual_rect = pieView->visualRect(model->index(item_index, 0));
  expected_rect =
      QRect(pieView->legendOrigin().x(), pieView->legendOrigin().y() + pieView->labelHeight() * item_index - 10,
            pieView->labelWidth(), pieView->labelHeight());
  QCOMPARE(actual_rect, expected_rect);
}

void PieViewTest::testScrollTo() {
  int row = 1;
  int col = 0;
  // Scroll to a labeled item
  pieView->scrollTo(model->index(row, col));
  // Scrollbar offset will be the same as the height of 2 items
  QCOMPARE(pieView->verticalScrollBar()->value(), pieView->labelHeight() * (row + 1));

  // Scroll to a data item (top left corner)
  row = 2;
  col = 1;
  pieView->scrollTo(model->index(row, col));

  QCOMPARE(pieView->verticalScrollBar()->value(), 0);

  // Test invalid index
  pieView->scrollTo(model->index(999, 999));
  QCOMPARE(pieView->verticalScrollBar()->value(), 0);
}

void PieViewTest::testIndexAt() {
  // Bad points
  QCOMPARE(pieView->indexAt(QPoint(0, 0)), QModelIndex());
  QCOMPARE(pieView->indexAt(QPoint(160, 15)), QModelIndex());

  // Pie points
  QCOMPARE(pieView->indexAt(top_left_quad), model->index(1, 1));
  QCOMPARE(pieView->indexAt(top_right_quad), model->index(0, 1));
  QCOMPARE(pieView->indexAt(bottom_left_quad), model->index(3, 1));
  QCOMPARE(pieView->indexAt(bottom_right_quad), model->index(4, 1));

  // Legend points
  QCOMPARE(pieView->indexAt(first_label), model->index(0, 0));
  QCOMPARE(pieView->indexAt(last_label), model->index(4, 0));
}

void PieViewTest::testMoveCursor() {
  window->resize(window->width(), first_label.y() + 15);
  // Click on the first label
  // Add 5 so it is detected as clicking on the first label
  QTest::mousePress(window, Qt::LeftButton, 0, QPoint(first_label.x() + 5, first_label.y() + 5), 50);
  // Test clicking up one time
  QTest::keyClick(pieView, Qt::Key_Up, Qt::NoModifier, 50);
  QCOMPARE(pieView->currentIndex(), model->index(4, 0));
  // Click up one more time
  QTest::keyClick(pieView, Qt::Key_Up, Qt::NoModifier, 50);
  QCOMPARE(pieView->currentIndex(), model->index(3, 0));
}

void PieViewTest::testNumberOfItems() { QCOMPARE(pieView->numberOfItems(), labels.size()); }

QTEST_MAIN(PieViewTest)
