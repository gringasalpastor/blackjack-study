#include "settings.h"

#include <kglobal.h>

#include <QtCore/QFile>

class SettingsHelper {
 public:
  SettingsHelper() : q(0) {}
  ~SettingsHelper() { delete q; }
  Settings* q;
};
K_GLOBAL_STATIC(SettingsHelper, s_globalSettings)
Settings* Settings::self() {
  if (!s_globalSettings->q) {
    new Settings;
    s_globalSettings->q->readConfig();
  }

  return s_globalSettings->q;
}

Settings::Settings() : KConfigSkeleton() {
  Q_ASSERT(!s_globalSettings->q);
  s_globalSettings->q = this;
  setCurrentGroup(QLatin1String("dealer"));

  QList<int> defaultCard_Occurences;
  defaultCard_Occurences.append(1);
  defaultCard_Occurences.append(1);
  defaultCard_Occurences.append(1);
  defaultCard_Occurences.append(1);
  defaultCard_Occurences.append(1);
  defaultCard_Occurences.append(1);
  defaultCard_Occurences.append(1);
  defaultCard_Occurences.append(1);
  defaultCard_Occurences.append(1);
  defaultCard_Occurences.append(1);

  KConfigSkeleton::ItemIntList* itemCard_Occurences;
  itemCard_Occurences = new KConfigSkeleton::ItemIntList(currentGroup(), QLatin1String("Card_Occurences"),
                                                         mCard_Occurences, defaultCard_Occurences);
  addItem(itemCard_Occurences, QLatin1String("Card_Occurences"));

  setCurrentGroup(QLatin1String("player"));

  QList<int> defaultNoc_Occurences;
  defaultNoc_Occurences.append(1);
  defaultNoc_Occurences.append(1);
  defaultNoc_Occurences.append(1);
  defaultNoc_Occurences.append(1);

  KConfigSkeleton::ItemIntList* itemNoc_Occurences;
  itemNoc_Occurences = new KConfigSkeleton::ItemIntList(currentGroup(), QLatin1String("Noc_Occurences"),
                                                        mNoc_Occurences, defaultNoc_Occurences);
  addItem(itemNoc_Occurences, QLatin1String("Noc_Occurences"));
  QList<int> defaultOcd_Occurences;
  defaultOcd_Occurences.append(1);
  defaultOcd_Occurences.append(1);
  defaultOcd_Occurences.append(1);
  defaultOcd_Occurences.append(1);

  KConfigSkeleton::ItemIntList* itemOcd_Occurences;
  itemOcd_Occurences = new KConfigSkeleton::ItemIntList(currentGroup(), QLatin1String("Ocd_Occurences"),
                                                        mOcd_Occurences, defaultOcd_Occurences);
  addItem(itemOcd_Occurences, QLatin1String("Ocd_Occurences"));
  QList<int> defaultPh_Occurences;
  defaultPh_Occurences.append(1);
  defaultPh_Occurences.append(1);
  defaultPh_Occurences.append(1);
  defaultPh_Occurences.append(1);
  defaultPh_Occurences.append(1);
  defaultPh_Occurences.append(1);
  defaultPh_Occurences.append(1);
  defaultPh_Occurences.append(1);
  defaultPh_Occurences.append(1);
  defaultPh_Occurences.append(1);

  KConfigSkeleton::ItemIntList* itemPh_Occurences;
  itemPh_Occurences = new KConfigSkeleton::ItemIntList(currentGroup(), QLatin1String("Ph_Occurences"), mPh_Occurences,
                                                       defaultPh_Occurences);
  addItem(itemPh_Occurences, QLatin1String("Ph_Occurences"));
  QList<int> defaultHh_Occurences;
  defaultHh_Occurences.append(1);
  defaultHh_Occurences.append(1);
  defaultHh_Occurences.append(1);
  defaultHh_Occurences.append(1);
  defaultHh_Occurences.append(1);
  defaultHh_Occurences.append(1);
  defaultHh_Occurences.append(1);
  defaultHh_Occurences.append(1);
  defaultHh_Occurences.append(1);
  defaultHh_Occurences.append(1);

  KConfigSkeleton::ItemIntList* itemHh_Occurences;
  itemHh_Occurences = new KConfigSkeleton::ItemIntList(currentGroup(), QLatin1String("Hh_Occurences"), mHh_Occurences,
                                                       defaultHh_Occurences);
  addItem(itemHh_Occurences, QLatin1String("Hh_Occurences"));
  QList<int> defaultSh_Occurences;
  defaultSh_Occurences.append(1);
  defaultSh_Occurences.append(1);
  defaultSh_Occurences.append(1);
  defaultSh_Occurences.append(1);
  defaultSh_Occurences.append(1);
  defaultSh_Occurences.append(1);
  defaultSh_Occurences.append(1);

  KConfigSkeleton::ItemIntList* itemSh_Occurences;
  itemSh_Occurences = new KConfigSkeleton::ItemIntList(currentGroup(), QLatin1String("Sh_Occurences"), mSh_Occurences,
                                                       defaultSh_Occurences);
  addItem(itemSh_Occurences, QLatin1String("Sh_Occurences"));
  QList<int> defaultDh_Occurences;
  defaultDh_Occurences.append(1);
  defaultDh_Occurences.append(1);
  defaultDh_Occurences.append(1);
  defaultDh_Occurences.append(1);

  KConfigSkeleton::ItemIntList* itemDh_Occurences;
  itemDh_Occurences = new KConfigSkeleton::ItemIntList(currentGroup(), QLatin1String("Dh_Occurences"), mDh_Occurences,
                                                       defaultDh_Occurences);
  addItem(itemDh_Occurences, QLatin1String("Dh_Occurences"));
  KConfigSkeleton::ItemBool* itemIdiot_hands;
  itemIdiot_hands = new KConfigSkeleton::ItemBool(currentGroup(), QLatin1String("idiot_hands"), mIdiot_hands, false);
  addItem(itemIdiot_hands, QLatin1String("idiot_hands"));
}

Settings::~Settings() {
  if (!s_globalSettings.isDestroyed()) {
    s_globalSettings->q = 0;
  }
}
