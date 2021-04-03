#pragma once

#include <QLabel>
#include <QString>
#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QVBoxLayout>

#include "keyboard.hpp"

class InputDialog : public QDialog {
  Q_OBJECT

public:
<<<<<<< HEAD
  explicit InputDialog(QString prompt_text, QWidget* parent = 0);
  static QString getText(QString prompt, int minLength = -1);
  QString text();
  void setMessage(QString message, bool clearInputField=true);
=======
  explicit InputDialog(const QString &prompt_text, QWidget* parent = 0);
  static QString getText(const QString &prompt, int minLength = -1);
  QString text();
  void setMessage(const QString &message, bool clearInputField = true);
>>>>>>> upstream/master-ci
  void setMinLength(int length);
  void show();

private:
  int minLength;
  QLineEdit *line;
  Keyboard *k;
  QLabel *label;
  QVBoxLayout *layout;

public slots:
  int exec() override;

private slots:
<<<<<<< HEAD
  void handleInput(QString s);

signals:
  void cancel();
  void emitText(QString text);
=======
  void handleInput(const QString &s);

signals:
  void cancel();
  void emitText(const QString &text);
>>>>>>> upstream/master-ci
};

class ConfirmationDialog : public QDialog {
  Q_OBJECT

public:
<<<<<<< HEAD
  explicit ConfirmationDialog(QString prompt_text, QString confirm_text = "Ok",
                              QString cancel_text = "Cancel", QWidget* parent = 0);
  static bool alert(QString prompt_text);
  static bool confirm(QString prompt_text);
=======
  explicit ConfirmationDialog(const QString &prompt_text, const QString &confirm_text = "Ok",
                              const QString &cancel_text = "Cancel", QWidget* parent = 0);
  static bool alert(const QString &prompt_text);
  static bool confirm(const QString &prompt_text);
>>>>>>> upstream/master-ci

private:
  QLabel *prompt;
  QVBoxLayout *layout;

public slots:
  int exec() override;
};
