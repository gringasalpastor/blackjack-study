#include "OverallPage.h"

#include <KLinkItemSelectionModel>
#include <QCheckBox>
#include <QGroupBox>
#include <QLayout>
#include <QVBoxLayout>
#include <QtGui>

#include "PercentModel.h"
#include "PercentTableView.h"
#include "PieView.h"

OverallPage::OverallPage(const QStringList& labels, QWidget* parent)
    : AbstractPage(parent),
      percentTable(new PercentTableView(this)),
      advanced(new QCheckBox("Edit percentages for each of the selected hands (Advanced)")) {
  percentTable->setModel(new PercentModel(labels));
  percentTable->resizeColumnsToContents();
  percentTable->resizeRowsToContents();
  percentTable->setMinimumSize();
  percentTable->setSelectionBehavior(QAbstractItemView::SelectRows);

  setLayout(new QVBoxLayout());
  QWidget* h_widget = new QWidget();
  h_widget->setLayout(new QHBoxLayout());
  QGroupBox* l_box = new QGroupBox("Hands");
  QGroupBox* r_box = new QGroupBox("Summary");
  l_box->setLayout(new QVBoxLayout());
  l_box->layout()->addWidget(percentTable);
  l_box->layout()->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
  r_box->setLayout(new QVBoxLayout());

  PieView* graph = new PieView(this);
  r_box->layout()->addWidget(graph);
  QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel(this);
  proxyModel->setFilterRegExp(QRegExp("^[123456789]\\d*$"));
  proxyModel->setFilterKeyColumn(1);
  proxyModel->setSourceModel(percentTable->percentModel());
  proxyModel->setDynamicSortFilter(true);

  graph->setModel(proxyModel);
  graph->setSelectionModel(new KLinkItemSelectionModel(proxyModel, percentTable->selectionModel()));
  graph->setSelectionBehavior(QAbstractItemView::SelectRows);

  h_widget->layout()->addWidget(l_box);
  h_widget->layout()->addWidget(r_box);

  layout()->addWidget(h_widget);
  layout()->addWidget(advanced);

  connect(percentTable->percentModel(), SIGNAL(percentageChanged(int)), this, SLOT(updateValidity()));
  connect(advanced, SIGNAL(toggled(bool)), this, SLOT(handleAdvancedToggled(bool)));
}

void OverallPage::updateValidity() {
  bool old_validity = pageValidity;
  pageValidity      = (!underOrOverAllocated() && !previouslyMissedAt100());
  if (pageValidity != old_validity) emit pageValidityChanged(this, pageValidity);
}

bool OverallPage::previouslyMissedAt100() {
  PercentModel* model = percentTable->percentModel();
  return (model->percentage(model->rowCount() - 1) == 100.0);
}

bool OverallPage::underOrOverAllocated() { return percentTable->percentModel()->underOrOverAllocated(); }
void OverallPage::handleAdvancedToggled(bool value) { emit advancedSelectionChanged(value); }
bool OverallPage::advancedSelected() { return advanced->isChecked(); }
