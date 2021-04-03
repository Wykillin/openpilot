#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
<<<<<<< HEAD
#include <QLabel>
#include <QStackedLayout>
=======
>>>>>>> upstream/master-ci
#include <QVBoxLayout>

#include "api.hpp"
#include "common/params.h"
#include "drive_stats.hpp"

const double MILE_TO_KM = 1.60934;

<<<<<<< HEAD
void clearLayouts(QLayout* layout) {
  while (QLayoutItem* item = layout->takeAt(0)) {
    if (QWidget* widget = item->widget()) {
      widget->deleteLater();
    }
    if (QLayout* childLayout = item->layout()) {
      clearLayouts(childLayout);
    }
    delete item;
  }
}

QLayout* build_stat(QString name, int stat) {
  QVBoxLayout* layout = new QVBoxLayout;
  layout->setMargin(0);

  QLabel* metric = new QLabel(QString("%1").arg(stat));
  metric->setStyleSheet(R"(
    font-size: 80px;
    font-weight: 600;
  )");
  layout->addWidget(metric, 0, Qt::AlignLeft);
=======
static QLayout* build_stat_layout(QLabel** metric, const QString& name) {
  QVBoxLayout* layout = new QVBoxLayout;
  layout->setMargin(0);
  *metric = new QLabel("0");
  (*metric)->setStyleSheet("font-size: 80px; font-weight: 600;");
  layout->addWidget(*metric, 0, Qt::AlignLeft);
>>>>>>> upstream/master-ci

  QLabel* label = new QLabel(name);
  label->setStyleSheet("font-size: 45px; font-weight: 500;");
  layout->addWidget(label, 0, Qt::AlignLeft);
  return layout;
}

<<<<<<< HEAD
void DriveStats::parseError(QString response) {
  clearLayouts(vlayout);
  vlayout->addWidget(new QLabel("No Internet connection"), 0, Qt::AlignCenter);
}

=======
>>>>>>> upstream/master-ci
void DriveStats::parseResponse(QString response) {
  response = response.trimmed();
  QJsonDocument doc = QJsonDocument::fromJson(response.toUtf8());
  if (doc.isNull()) {
    qDebug() << "JSON Parse failed on getting past drives statistics";
    return;
  }

<<<<<<< HEAD
  bool metric = Params().read_db_bool("IsMetric");
=======
  auto update = [](const QJsonObject &obj, StatsLabels& labels, bool metric) {
    labels.routes->setText(QString::number((int)obj["routes"].toDouble()));
    labels.distance->setText(QString::number(int(obj["distance"].toDouble() * (metric ? MILE_TO_KM : 1))));
    labels.hours->setText(QString::number((int)(obj["minutes"].toDouble() / 60)));
  };
>>>>>>> upstream/master-ci

  bool metric = Params().getBool("IsMetric");
  QJsonObject json = doc.object();
  update(json["all"].toObject(), all_, metric);
  update(json["week"].toObject(), week_, metric);
}

<<<<<<< HEAD
  QGridLayout* gl = new QGridLayout();
  gl->setMargin(0);
=======
DriveStats::DriveStats(QWidget* parent) : QWidget(parent) {
  setStyleSheet("QLabel {font-size: 48px; font-weight: 500;}");
>>>>>>> upstream/master-ci

  auto add_stats_layouts = [&](QGridLayout* gl, StatsLabels& labels, int row, const char* distance_unit) {
    gl->addLayout(build_stat_layout(&labels.routes, "DRIVES"), row, 0, 3, 1);
    gl->addLayout(build_stat_layout(&labels.distance, distance_unit), row, 1, 3, 1);
    gl->addLayout(build_stat_layout(&labels.hours, "HOURS"), row, 2, 3, 1);
  };

  const char* distance_unit = Params().getBool("IsMetric") ? "KM" : "MILES";
  QGridLayout* gl = new QGridLayout();
  gl->setMargin(0);
  gl->addWidget(new QLabel("ALL TIME"), 0, 0, 1, 3);
  add_stats_layouts(gl, all_, 1, distance_unit);
  gl->addWidget(new QLabel("PAST WEEK"), 6, 0, 1, 3);
  add_stats_layouts(gl, week_, 7, distance_unit);

<<<<<<< HEAD
  QWidget* q = new QWidget;
  q->setLayout(gl);
  vlayout->addWidget(q);
}

DriveStats::DriveStats(QWidget* parent) : QWidget(parent) {
  vlayout = new QVBoxLayout(this);
  vlayout->setMargin(0);
  setLayout(vlayout);
  setStyleSheet(R"(
    QLabel {
      font-size: 48px;
      font-weight: 500;
    }
  )");
=======
  QVBoxLayout* vlayout = new QVBoxLayout(this);
  vlayout->addLayout(gl);
>>>>>>> upstream/master-ci

  // TODO: do we really need to update this frequently?
  QString dongleId = QString::fromStdString(Params().get("DongleId"));
  QString url = "https://api.commadotai.com/v1.1/devices/" + dongleId + "/stats";
  RequestRepeater* repeater = new RequestRepeater(this, url, 13, "ApiCache_DriveStats");
  QObject::connect(repeater, SIGNAL(receivedResponse(QString)), this, SLOT(parseResponse(QString)));
<<<<<<< HEAD
  QObject::connect(repeater, SIGNAL(failedResponse(QString)), this, SLOT(parseError(QString)));
=======
>>>>>>> upstream/master-ci
}
