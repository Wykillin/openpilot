#pragma once
#include <map>

#include <QFrame>
#include <QPushButton>
<<<<<<< HEAD
#include <QStringList>
=======
#include <QLabel>
>>>>>>> upstream/master-ci

#include "common/params.h"
#include "widgets/scrollview.hpp"

class OffroadAlert : public QFrame {
  Q_OBJECT

public:
  explicit OffroadAlert(QWidget *parent = 0);
<<<<<<< HEAD
  QVector<Alert> alerts;
  QStringList alert_keys;
=======
  int alertCount = 0;
>>>>>>> upstream/master-ci
  bool updateAvailable;

private:
  Params params;
  QLabel releaseNotes;
  std::map<std::string, QLabel*> alerts;
  QPushButton rebootBtn;
  void updateAlerts();

  ScrollView *releaseNotesScroll;
  ScrollView *alertsScroll;

signals:
  void closeAlerts();

public slots:
  void refresh();
};
