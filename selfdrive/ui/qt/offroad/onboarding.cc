#include <QLabel>
<<<<<<< HEAD
#include <QString>
#include <QPainter>
#include <QScroller>
#include <QScrollBar>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QQmlContext>
#include <QQuickWidget>
=======
#include <QPainter>
#include <QVBoxLayout>
#include <QQuickWidget>
#include <QQmlContext>
>>>>>>> upstream/master-ci
#include <QDesktopWidget>

#include "common/params.h"
#include "onboarding.hpp"
#include "home.hpp"
#include "util.h"


void TrainingGuide::mouseReleaseEvent(QMouseEvent *e) {
  QPoint touch = QPoint(e->x(), e->y()) - imageCorner;
  //qDebug() << touch.x() << ", " << touch.y();

  // Check for restart
<<<<<<< HEAD
  if (currentIndex == (boundingBox.size() - 1) && 1050 <= mousex && mousex <= 1500 &&
      773 <= mousey && mousey <= 954) {
    currentIndex = 0;
  } else if (boundingBox[currentIndex][0] <= mousex && mousex <= boundingBox[currentIndex][1] &&
             boundingBox[currentIndex][2] <= mousey && mousey <= boundingBox[currentIndex][3]) {
=======
  if (currentIndex == (boundingBox.size() - 1) && 200 <= touch.x() && touch.x() <= 920 &&
      760 <= touch.y() && touch.y() <= 960) {
    currentIndex = 0;
  } else if (boundingBox[currentIndex][0] <= touch.x() && touch.x() <= boundingBox[currentIndex][1] &&
             boundingBox[currentIndex][2] <= touch.y() && touch.y() <= boundingBox[currentIndex][3]) {
>>>>>>> upstream/master-ci
    currentIndex += 1;
  }

  if (currentIndex >= boundingBox.size()) {
    emit completedTraining();
<<<<<<< HEAD
    return;
  } else {
    image.load("../assets/training/step" + QString::number(currentIndex) + ".jpg");
=======
  } else {
    image.load("../assets/training/step" + QString::number(currentIndex) + ".png");
>>>>>>> upstream/master-ci
    update();
  }
}

<<<<<<< HEAD
TrainingGuide::TrainingGuide(QWidget* parent) : QFrame(parent){
  image.load("../assets/training/step0.jpg");
=======
void TrainingGuide::showEvent(QShowEvent *event) {
  currentIndex = 0;
  image.load("../assets/training/step0.png");
>>>>>>> upstream/master-ci
}

void TrainingGuide::paintEvent(QPaintEvent *event) {
  QPainter painter(this);

<<<<<<< HEAD
  QRect devRect(0, 0, painter.device()->width(), painter.device()->height());
  QBrush bgBrush("#072339");
  painter.fillRect(devRect, bgBrush);

  QRect rect(image.rect());
  rect.moveCenter(devRect.center());
  painter.drawImage(rect.topLeft(), image);
}

TermsPage::TermsPage(QWidget *parent) : QFrame(parent){

=======
  QRect bg(0, 0, painter.device()->width(), painter.device()->height());
  QBrush bgBrush("#000000");
  painter.fillRect(bg, bgBrush);

  QRect rect(image.rect());
  rect.moveCenter(bg.center());
  painter.drawImage(rect.topLeft(), image);
  imageCorner = rect.topLeft();
}

TermsPage::TermsPage(QWidget *parent) : QFrame(parent){
>>>>>>> upstream/master-ci
  QVBoxLayout *main_layout = new QVBoxLayout;
  main_layout->setMargin(40);
  main_layout->setSpacing(40);

<<<<<<< HEAD
  QQuickWidget *text = new QQuickWidget(QUrl::fromLocalFile("qt/offroad/text_view.qml"), this);
=======
  QQuickWidget *text = new QQuickWidget(this);
>>>>>>> upstream/master-ci
  text->setResizeMode(QQuickWidget::SizeRootObjectToView);
  text->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  text->setAttribute(Qt::WA_AlwaysStackOnTop);
  text->setClearColor(Qt::transparent);
<<<<<<< HEAD

  text->rootContext()->setContextProperty("font_size", 55);

  QString text_view = util::read_file("../assets/offroad/tc.html").c_str();
  text->rootContext()->setContextProperty("text_view", text_view);

=======

  text->rootContext()->setContextProperty("font_size", 55);

  QString text_view = util::read_file("../assets/offroad/tc.html").c_str();
  text->rootContext()->setContextProperty("text_view", text_view);

  text->setSource(QUrl::fromLocalFile("qt/offroad/text_view.qml"));

>>>>>>> upstream/master-ci
  main_layout->addWidget(text);

  // TODO: add decline page
  QHBoxLayout* buttons = new QHBoxLayout;
  main_layout->addLayout(buttons);

  buttons->addWidget(new QPushButton("Decline"));
  buttons->addSpacing(50);

  accept_btn = new QPushButton("Scroll to accept");
  accept_btn->setEnabled(false);
  buttons->addWidget(accept_btn);
  QObject::connect(accept_btn, &QPushButton::released, [=]() {
    emit acceptedTerms();
  });

  QObject *obj = (QObject*)text->rootObject();
  QObject::connect(obj, SIGNAL(qmlSignal()), SLOT(enableAccept()));
  setLayout(main_layout);
  setStyleSheet(R"(
    * {
      font-size: 50px;
    }
    QPushButton {
      padding: 50px;
      border-radius: 10px;
      background-color: #292929;
    }
  )");
}

void TermsPage::enableAccept(){
  accept_btn->setText("Accept");
  accept_btn->setEnabled(true);
  return;
}

void OnboardingWindow::updateActiveScreen() {
  bool accepted_terms = params.get("HasAcceptedTerms", false).compare(current_terms_version) == 0;
  bool training_done = params.get("CompletedTrainingVersion", false).compare(current_training_version) == 0;

  if (!accepted_terms) {
    setCurrentIndex(0);
  } else if (!training_done) {
    setCurrentIndex(1);
  } else {
    emit onboardingDone();
  }
}

OnboardingWindow::OnboardingWindow(QWidget *parent) : QStackedWidget(parent) {
  params = Params();
  current_terms_version = params.get("TermsVersion", false);
  current_training_version = params.get("TrainingVersion", false);

  TermsPage* terms = new TermsPage(this);
  addWidget(terms);

  connect(terms, &TermsPage::acceptedTerms, [=](){
<<<<<<< HEAD
    Params().write_db_value("HasAcceptedTerms", current_terms_version);
=======
    Params().put("HasAcceptedTerms", current_terms_version);
>>>>>>> upstream/master-ci
    updateActiveScreen();
  });

  TrainingGuide* tr = new TrainingGuide(this);
  connect(tr, &TrainingGuide::completedTraining, [=](){
    Params().put("CompletedTrainingVersion", current_training_version);
    updateActiveScreen();
  });
  addWidget(tr);


  setStyleSheet(R"(
    * {
      color: white;
      background-color: black;
    }
    QPushButton {
      padding: 50px;
      border-radius: 30px;
      background-color: #292929;
    }
    QPushButton:disabled {
      color: #777777;
      background-color: #222222;
    }
  )");

  updateActiveScreen();
}
