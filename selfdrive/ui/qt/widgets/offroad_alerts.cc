#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QJsonObject>
#include <QJsonDocument>

#include "offroad_alerts.hpp"
<<<<<<< HEAD
#include "common/params.h"
#include "selfdrive/hardware/hw.h"

void cleanStackedWidget(QStackedWidget* swidget) {
  while(swidget->count() > 0) {
    QWidget *w = swidget->widget(0);
    swidget->removeWidget(w);
    w->deleteLater();
=======
#include "selfdrive/hardware/hw.h"
#include "selfdrive/common/util.h"

OffroadAlert::OffroadAlert(QWidget* parent) : QFrame(parent) {
  QVBoxLayout *layout = new QVBoxLayout();
  layout->setMargin(50);
  layout->setSpacing(30);

  QWidget *alerts_widget = new QWidget;
  QVBoxLayout *alerts_layout = new QVBoxLayout;
  alerts_layout->setMargin(0);
  alerts_layout->setSpacing(30);
  alerts_widget->setLayout(alerts_layout);
  alerts_widget->setStyleSheet("background-color: transparent;");

  // setup labels for each alert
  QString json = QString::fromStdString(util::read_file("../controls/lib/alerts_offroad.json"));
  QJsonObject obj = QJsonDocument::fromJson(json.toUtf8()).object();
  for (auto &k : obj.keys()) {
    QLabel *l = new QLabel(this);
    alerts[k.toStdString()] = l;
    int severity = obj[k].toObject()["severity"].toInt();

    l->setMargin(60);
    l->setWordWrap(true);
    l->setStyleSheet("background-color: " + QString(severity ? "#E22C2C" : "#292929"));
    l->setVisible(false);
    alerts_layout->addWidget(l);
>>>>>>> upstream/master-ci
  }

  alerts_layout->addStretch(1);

  // release notes
  releaseNotes.setWordWrap(true);
  releaseNotes.setVisible(false);
  releaseNotes.setStyleSheet("font-size: 48px;");
  releaseNotes.setAlignment(Qt::AlignTop);

  releaseNotesScroll = new ScrollView(&releaseNotes, this);
  layout->addWidget(releaseNotesScroll);

  alertsScroll = new ScrollView(alerts_widget, this);
  layout->addWidget(alertsScroll);

  // bottom footer, dismiss + reboot buttons
  QHBoxLayout *footer_layout = new QHBoxLayout();
  layout->addLayout(footer_layout);

  QPushButton *dismiss_btn = new QPushButton("Dismiss");
  dismiss_btn->setFixedSize(400, 125);
  footer_layout->addWidget(dismiss_btn, 0, Qt::AlignBottom | Qt::AlignLeft);
  QObject::connect(dismiss_btn, SIGNAL(released()), this, SIGNAL(closeAlerts()));
<<<<<<< HEAD
  QObject::connect(reboot_btn, &QPushButton::released, [=]() { Hardware::reboot(); });
=======
>>>>>>> upstream/master-ci

  rebootBtn.setText("Reboot and Update");
  rebootBtn.setFixedSize(600, 125);
  rebootBtn.setVisible(false);
  footer_layout->addWidget(&rebootBtn, 0, Qt::AlignBottom | Qt::AlignRight);
  QObject::connect(&rebootBtn, &QPushButton::released, [=]() { Hardware::reboot(); });

  setLayout(layout);
  setStyleSheet(R"(
    * {
      font-size: 48px;
      color: white;
    }
    QFrame {
      border-radius: 30px;
      background-color: #393939;
    }
    QPushButton {
      color: black;
      font-weight: 500;
      border-radius: 30px;
      background-color: white;
    }
  )");
<<<<<<< HEAD
  main_layout->setMargin(50);

  QFile inFile("../controls/lib/alerts_offroad.json");
  bool ret = inFile.open(QIODevice::ReadOnly | QIODevice::Text);
  assert(ret);
  QJsonDocument doc = QJsonDocument::fromJson(inFile.readAll());
  assert(!doc.isNull());
  alert_keys = doc.object().keys();
=======

>>>>>>> upstream/master-ci
}

void OffroadAlert::refresh() {
  updateAlerts();

<<<<<<< HEAD
  updateAvailable = Params().read_db_bool("UpdateAvailable");
  reboot_btn->setVisible(updateAvailable);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->setSpacing(20);

  if (updateAvailable) {
    QLabel *body = new QLabel(QString::fromStdString(Params().get("ReleaseNotes")));
    body->setStyleSheet(R"(font-size: 48px;)");
    layout->addWidget(body, 0, Qt::AlignLeft | Qt::AlignTop);
  } else {
    for (const auto &alert : alerts) {
      QLabel *l = new QLabel(alert.text);
      l->setMargin(60);
      l->setWordWrap(true);
      l->setStyleSheet("background-color: " + QString(alert.severity ? "#E22C2C" : "#292929"));
      layout->addWidget(l, 0, Qt::AlignTop);
    }
  }

  QWidget *w = new QWidget();
  w->setLayout(layout);
  alerts_stack->addWidget(w);
}

void OffroadAlert::parse_alerts() {
  alerts.clear();
  for (const QString &key : alert_keys) {
    std::vector<char> bytes = Params().read_db_bytes(key.toStdString().c_str());
=======
  rebootBtn.setVisible(updateAvailable);
  releaseNotesScroll->setVisible(updateAvailable);
  releaseNotes.setText(QString::fromStdString(params.get("ReleaseNotes")));

  alertsScroll->setVisible(!updateAvailable);
  for (const auto& [k, label] : alerts) {
    label->setVisible(!label->text().isEmpty());
  }
}

void OffroadAlert::updateAlerts() {
  alertCount = 0;
  updateAvailable = params.getBool("UpdateAvailable");
  for (const auto& [key, label] : alerts) {
    auto bytes = params.get(key.c_str());
>>>>>>> upstream/master-ci
    if (bytes.size()) {
      QJsonDocument doc_par = QJsonDocument::fromJson(QByteArray(bytes.data(), bytes.size()));
      QJsonObject obj = doc_par.object();
      label->setText(obj.value("text").toString());
      alertCount++;
    } else {
      label->setText("");
    }
  }
}
