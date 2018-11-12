#ifndef MAINWINDOW_HH_
#define MAINWINDOW_HH_

#include <string>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

class MainWindow: public QWidget
{
  Q_OBJECT
public:

  const int ROWS = 8;
  const int COLS = 8;

  QString _RowNames[8] = {"a", "b", "c", "d", "e", "f", "g", "h"};
  QString _ColNames[8] = {"1", "2", "3", "4", "5", "6", "7", "8"};

  MainWindow(QWidget *aParent);

  virtual ~MainWindow();

	void setupView();

public slots:

  void onSend();

protected:

  QCheckBox *_checkBox;
  QLabel *_label1;
  QLabel *_label2;
  QLineEdit *_lineEdit1;
  QLineEdit *_lineEdit2;
  QPushButton *_startButton;
};

#endif /* MAINWINDOW_HH_ */
