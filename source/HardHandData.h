#ifndef HARDHANDDATA_H
#define HARDHANDDATA_H
#include <QVector>
class HardHandData {
 public:
  HardHandData();
  QVector<QVector<int> > eights;
  QVector<QVector<int> > nines;
  QVector<QVector<int> > tens;
  QVector<QVector<int> > elevens;
  QVector<QVector<int> > twelves;
  QVector<QVector<int> > thirteens;
  QVector<QVector<int> > fourteens;
  QVector<QVector<int> > fifthteens;
  QVector<QVector<int> > sixteens;
  QVector<QVector<int> > seventeens;
};
#endif
