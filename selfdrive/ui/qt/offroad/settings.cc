#include <string>
#include <iostream>
#include <sstream>
#include <cassert>

#ifndef QCOM
#include "networking.hpp"
#endif
#include "settings.hpp"
#include "widgets/input.hpp"
#include "widgets/toggle.hpp"
#include "widgets/offroad_alerts.hpp"
<<<<<<< HEAD
=======
#include "widgets/scrollview.hpp"
>>>>>>> upstream/master-ci
#include "widgets/controls.hpp"
#include "widgets/ssh_keys.hpp"
#include "common/params.h"
#include "common/util.h"
#include "selfdrive/hardware/hw.h"
<<<<<<< HEAD
=======
#include "home.hpp"
>>>>>>> upstream/master-ci


QWidget * toggles_panel() {
  QVBoxLayout *toggles_list = new QVBoxLayout();

<<<<<<< HEAD
  toggles_list->setMargin(50);
=======
>>>>>>> upstream/master-ci
  toggles_list->addWidget(new ParamControl("OpenpilotEnabledToggle",
                                            "Enable openpilot",
                                            "Use the openpilot system for adaptive cruise control and lane keep driver assistance. Your attention is required at all times to use this feature. Changing this setting takes effect when the car is powered off.",
                                            "../assets/offroad/icon_openpilot.png"
                                              ));
  toggles_list->addWidget(horizontal_line());
  toggles_list->addWidget(new ParamControl("IsLdwEnabled",
                                            "Enable Lane Departure Warnings",
                                            "Receive alerts to steer back into the lane when your vehicle drifts over a detected lane line without a turn signal activated while driving over 31mph (50kph).",
                                            "../assets/offroad/icon_warning.png"
                                              ));
  toggles_list->addWidget(horizontal_line());
  toggles_list->addWidget(new ParamControl("IsRHD",
                                            "Enable Right-Hand Drive",
                                            "Allow openpilot to obey left-hand traffic conventions and perform driver monitoring on right driver seat.",
                                            "../assets/offroad/icon_openpilot_mirrored.png"
                                            ));
  toggles_list->addWidget(horizontal_line());
  toggles_list->addWidget(new ParamControl("IsMetric",
                                            "Use Metric System",
                                            "Display speed in km/h instead of mp/h.",
                                            "../assets/offroad/icon_metric.png"
                                            ));
  toggles_list->addWidget(horizontal_line());
  toggles_list->addWidget(new ParamControl("CommunityFeaturesToggle",
                                            "Enable Community Features",
                                            "Use features from the open source community that are not maintained or supported by comma.ai and have not been confirmed to meet the standard safety model. These features include community supported cars and community supported hardware. Be extra cautious when using these features",
                                            "../assets/offroad/icon_shell.png"
                                            ));
  toggles_list->addWidget(horizontal_line());
  ParamControl *record_toggle = new ParamControl("RecordFront",
                                            "Record and Upload Driver Camera",
                                            "Upload data from the driver facing camera and help improve the driver monitoring algorithm.",
                                            "../assets/offroad/icon_network.png");
  toggles_list->addWidget(record_toggle);
  toggles_list->addWidget(horizontal_line());
  toggles_list->addWidget(new ParamControl("EndToEndToggle",
<<<<<<< HEAD
                                           "Ignore lanelines (Experimental)",
                                           "In this mode openpilot will ignore lanelines and just drive how it thinks a human would.",
                                           "../assets/offroad/icon_road.png"));

  bool record_lock = Params().read_db_bool("RecordFrontLock");
=======
                                           "\U0001f96c Disable use of lanelines (Alpha) \U0001f96c",
                                           "In this mode openpilot will ignore lanelines and just drive how it thinks a human would.",
                                           "../assets/offroad/icon_road.png"));

  bool record_lock = Params().getBool("RecordFrontLock");
>>>>>>> upstream/master-ci
  record_toggle->setEnabled(!record_lock);

  QWidget *widget = new QWidget;
  widget->setLayout(toggles_list);
  return widget;
}

DevicePanel::DevicePanel(QWidget* parent) : QWidget(parent) {
  QVBoxLayout *device_layout = new QVBoxLayout;
<<<<<<< HEAD
  device_layout->setMargin(100);
=======
>>>>>>> upstream/master-ci

  Params params = Params();

  QString dongle = QString::fromStdString(params.get("DongleId", false));
  device_layout->addWidget(new LabelControl("Dongle ID", dongle));
  device_layout->addWidget(horizontal_line());

  QString serial = QString::fromStdString(params.get("HardwareSerial", false));
  device_layout->addWidget(new LabelControl("Serial", serial));

  // offroad-only buttons
  QList<ButtonControl*> offroad_btns;

<<<<<<< HEAD
  for (auto &l : labels) {
    device_layout->addWidget(new LabelControl(QString::fromStdString(l.first),
                             QString::fromStdString(l.second)));
  }

  device_layout->addWidget(horizontal_line());

  device_layout->addWidget(new ButtonControl("Driver Camera", "PREVIEW",
                                             "Preview the driver facing camera to help optimize device mounting position for best driver monitoring experience. (vehicle must be off)",
                                             [=]() { Params().write_db_value("IsDriverViewEnabled", "1", 1); }));

  device_layout->addWidget(horizontal_line());

  // TODO: show current calibration values
  device_layout->addWidget(new ButtonControl("Reset Calibration", "RESET",
                                             "openpilot requires the device to be mounted within 4° left or right and within 5° up or down. openpilot is continuously calibrating, resetting is rarely required.",
                                             [=]() {
                                               if (ConfirmationDialog::confirm("Are you sure you want to reset calibration?")) {
                                                 Params().delete_db_value("CalibrationParams");
                                               }
                                             }));

  device_layout->addWidget(horizontal_line());

  QString brand = params.read_db_bool("Passive") ? "dashcam" : "openpilot";
  device_layout->addWidget(new ButtonControl("Uninstall " + brand, "UNINSTALL",
                                             "",
                                             [=]() {
                                               if (ConfirmationDialog::confirm("Are you sure you want to uninstall?")) {
                                                 Params().write_db_value("DoUninstall", "1");
                                               }
                                             }));

=======
  offroad_btns.append(new ButtonControl("Driver Camera", "PREVIEW",
                                   "Preview the driver facing camera to help optimize device mounting position for best driver monitoring experience. (vehicle must be off)",
                                   [=]() { 
                                      Params().putBool("IsDriverViewEnabled", true);
                                      GLWindow::ui_state.scene.driver_view = true; }
                                    ));

  offroad_btns.append(new ButtonControl("Reset Calibration", "RESET",
                                   "openpilot requires the device to be mounted within 4° left or right and within 5° up or down. openpilot is continuously calibrating, resetting is rarely required.", [=]() {
    if (ConfirmationDialog::confirm("Are you sure you want to reset calibration?")) {
      Params().remove("CalibrationParams");
    }
  }));

  offroad_btns.append(new ButtonControl("Review Training Guide", "REVIEW",
                                        "Review the rules, features, and limitations of openpilot", [=]() {
    if (ConfirmationDialog::confirm("Are you sure you want to review the training guide?")) {
      Params().remove("CompletedTrainingVersion");
      emit reviewTrainingGuide();
    }
  }));

  QString brand = params.getBool("Passive") ? "dashcam" : "openpilot";
  offroad_btns.append(new ButtonControl("Uninstall " + brand, "UNINSTALL", "", [=]() {
    if (ConfirmationDialog::confirm("Are you sure you want to uninstall?")) {
      Params().putBool("DoUninstall", true);
    }
  }));

  for(auto &btn : offroad_btns){
    device_layout->addWidget(horizontal_line());
    QObject::connect(parent, SIGNAL(offroadTransition(bool)), btn, SLOT(setEnabled(bool)));
    device_layout->addWidget(btn);
  }

>>>>>>> upstream/master-ci
  // power buttons
  QHBoxLayout *power_layout = new QHBoxLayout();
  power_layout->setSpacing(30);

  QPushButton *reboot_btn = new QPushButton("Reboot");
  power_layout->addWidget(reboot_btn);
  QObject::connect(reboot_btn, &QPushButton::released, [=]() {
    if (ConfirmationDialog::confirm("Are you sure you want to reboot?")) {
      Hardware::reboot();
    }
  });

  QPushButton *poweroff_btn = new QPushButton("Power Off");
  poweroff_btn->setStyleSheet("background-color: #E22C2C;");
  power_layout->addWidget(poweroff_btn);
  QObject::connect(poweroff_btn, &QPushButton::released, [=]() {
    if (ConfirmationDialog::confirm("Are you sure you want to power off?")) {
      Hardware::poweroff();
    }
  });

  device_layout->addLayout(power_layout);

  setLayout(device_layout);
  setStyleSheet(R"(
    QPushButton {
      padding: 0;
      height: 120px;
      border-radius: 15px;
      background-color: #393939;
    }
  )");
}

DeveloperPanel::DeveloperPanel(QWidget* parent) : QFrame(parent) {
  QVBoxLayout *main_layout = new QVBoxLayout(this);
<<<<<<< HEAD
  main_layout->setMargin(100);
=======
>>>>>>> upstream/master-ci
  setLayout(main_layout);
  setStyleSheet(R"(QLabel {font-size: 50px;})");
}

void DeveloperPanel::showEvent(QShowEvent *event) {
  Params params = Params();
<<<<<<< HEAD
  std::string brand = params.read_db_bool("Passive") ? "dashcam" : "openpilot";
  QList<QPair<QString, std::string>> dev_params = {
    {"Version", brand + " v" + params.get("Version", false)},
=======
  std::string brand = params.getBool("Passive") ? "dashcam" : "openpilot";
  QList<QPair<QString, std::string>> dev_params = {
    {"Version", brand + " v" + params.get("Version", false).substr(0, 14)},
>>>>>>> upstream/master-ci
    {"Git Branch", params.get("GitBranch", false)},
    {"Git Commit", params.get("GitCommit", false).substr(0, 10)},
    {"Panda Firmware", params.get("PandaFirmwareHex", false)},
    {"OS Version", Hardware::get_os_version()},
  };

  for (int i = 0; i < dev_params.size(); i++) {
    const auto &[name, value] = dev_params[i];
    QString val = QString::fromStdString(value).trimmed();
    if (labels.size() > i) {
      labels[i]->setText(val);
    } else {
      labels.push_back(new LabelControl(name, val));
      layout()->addWidget(labels[i]);
      if (i < (dev_params.size() - 1)) {
        layout()->addWidget(horizontal_line());
      }
    }
  }
}

QWidget * network_panel(QWidget * parent) {
#ifdef QCOM
  QVBoxLayout *layout = new QVBoxLayout;
<<<<<<< HEAD
  layout->setMargin(100);
  layout->setSpacing(30);

  // simple wifi + tethering buttons
  const char* launch_wifi = "am start -n com.android.settings/.wifi.WifiPickerActivity \
                             -a android.net.wifi.PICK_WIFI_NETWORK \
                             --ez extra_prefs_show_button_bar true \
                             --es extra_prefs_set_next_text ''";
  layout->addWidget(new ButtonControl("WiFi Settings", "OPEN", "",
                                      [=]() { std::system(launch_wifi); }));

  layout->addWidget(horizontal_line());

  const char* launch_tethering = "am start -n com.android.settings/.TetherSettings \
                                  --ez extra_prefs_show_button_bar true \
                                  --es extra_prefs_set_next_text ''";
  layout->addWidget(new ButtonControl("Tethering Settings", "OPEN", "",
                                      [=]() { std::system(launch_tethering); }));

=======
  layout->setSpacing(30);

  // wifi + tethering buttons
  layout->addWidget(new ButtonControl("WiFi Settings", "OPEN", "",
                                      [=]() { HardwareEon::launch_wifi(); }));
  layout->addWidget(horizontal_line());

  layout->addWidget(new ButtonControl("Tethering Settings", "OPEN", "",
                                      [=]() { HardwareEon::launch_tethering(); }));
>>>>>>> upstream/master-ci
  layout->addWidget(horizontal_line());

  // SSH key management
  layout->addWidget(new SshToggle());
  layout->addWidget(horizontal_line());
  layout->addWidget(new SshControl());
<<<<<<< HEAD

  layout->addStretch(1);

  QWidget *w = new QWidget;
  w->setLayout(layout);
#else
  Networking *w = new Networking(parent);
#endif
  return w;
}

=======

  layout->addStretch(1);

  QWidget *w = new QWidget;
  w->setLayout(layout);
#else
  Networking *w = new Networking(parent);
#endif
  return w;
}

>>>>>>> upstream/master-ci
SettingsWindow::SettingsWindow(QWidget *parent) : QFrame(parent) {
  // setup two main layouts
  QVBoxLayout *sidebar_layout = new QVBoxLayout();
  sidebar_layout->setMargin(0);
  panel_widget = new QStackedWidget();
<<<<<<< HEAD
=======
  panel_widget->setStyleSheet(R"(
    border-radius: 30px;
    background-color: #292929;
  )");
>>>>>>> upstream/master-ci

  // close button
  QPushButton *close_btn = new QPushButton("X");
  close_btn->setStyleSheet(R"(
    font-size: 90px;
    font-weight: bold;
    border 1px grey solid;
    border-radius: 100px;
    background-color: #292929;
  )");
  close_btn->setFixedSize(200, 200);
  sidebar_layout->addSpacing(45);
  sidebar_layout->addWidget(close_btn, 0, Qt::AlignCenter);
  QObject::connect(close_btn, SIGNAL(released()), this, SIGNAL(closeSettings()));

  // setup panels
<<<<<<< HEAD
  QPair<QString, QWidget *> panels[] = {
    {"Device", new DevicePanel(this)},
=======
  DevicePanel *device = new DevicePanel(this);
  QObject::connect(device, SIGNAL(reviewTrainingGuide()), this, SIGNAL(reviewTrainingGuide()));

  QPair<QString, QWidget *> panels[] = {
    {"Device", device},
>>>>>>> upstream/master-ci
    {"Network", network_panel(this)},
    {"Toggles", toggles_panel()},
    {"Developer", new DeveloperPanel()},
  };

  sidebar_layout->addSpacing(45);
  nav_btns = new QButtonGroup();
  for (auto &[name, panel] : panels) {
    QPushButton *btn = new QPushButton(name);
    btn->setCheckable(true);
    btn->setStyleSheet(R"(
      QPushButton {
        color: grey;
        border: none;
        background: none;
        font-size: 65px;
        font-weight: 500;
        padding-top: 35px;
        padding-bottom: 35px;
      }
      QPushButton:checked {
        color: white;
      }
    )");

    nav_btns->addButton(btn);
    sidebar_layout->addWidget(btn, 0, Qt::AlignRight);

<<<<<<< HEAD
    panel_widget->addWidget(panel);
    QObject::connect(btn, &QPushButton::released, [=, w = panel]() {
=======
    panel->setContentsMargins(50, 25, 50, 25);

    ScrollView *panel_frame = new ScrollView(panel, this);
    panel_widget->addWidget(panel_frame);

    QObject::connect(btn, &QPushButton::released, [=, w = panel_frame]() {
>>>>>>> upstream/master-ci
      panel_widget->setCurrentWidget(w);
    });
  }
  qobject_cast<QPushButton *>(nav_btns->buttons()[0])->setChecked(true);
  sidebar_layout->setContentsMargins(50, 50, 100, 50);

  // main settings layout, sidebar + main panel
  QHBoxLayout *settings_layout = new QHBoxLayout();

  sidebar_widget = new QWidget;
  sidebar_widget->setLayout(sidebar_layout);
  sidebar_widget->setFixedWidth(500);
  settings_layout->addWidget(sidebar_widget);
<<<<<<< HEAD

  panel_frame = new QScrollArea;
  panel_frame->setWidget(panel_widget);
  panel_frame->setWidgetResizable(true);
  panel_frame->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  panel_frame->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  panel_frame->setStyleSheet(R"(
    border-radius: 30px;
    background-color: #292929;
  )");
  settings_layout->addWidget(panel_frame);
=======
  settings_layout->addWidget(panel_widget);
>>>>>>> upstream/master-ci

  // setup panel scrolling
  QScroller *scroller = QScroller::scroller(panel_frame);
  auto sp = scroller->scrollerProperties();
  sp.setScrollMetric(QScrollerProperties::FrameRate, QVariant::fromValue<QScrollerProperties::FrameRates>(QScrollerProperties::Fps30));
  sp.setScrollMetric(QScrollerProperties::VerticalOvershootPolicy, QVariant::fromValue<QScrollerProperties::OvershootPolicy>(QScrollerProperties::OvershootAlwaysOff));
  scroller->setScrollerProperties(sp);
  scroller->grabGesture(panel_frame->viewport(), QScroller::LeftMouseButtonGesture);

  setLayout(settings_layout);
  setStyleSheet(R"(
    * {
      color: white;
      font-size: 50px;
    }
    SettingsWindow {
      background-color: black;
    }
  )");
}
