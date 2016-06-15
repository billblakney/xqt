#ifndef MAINWINDOW_HH_
#define MAINWINDOW_HH_

#include <string>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class MainWindow: public QWidget
{
  Q_OBJECT
public:

  MainWindow(QWidget *aParent);

  virtual ~MainWindow();

	void setupView();

public slots:

  void onSend();

protected:

  QLabel *_label1;
  QLabel *_label2;
  QLineEdit *_lineEdit1;
  QLineEdit *_lineEdit2;
  QPushButton *_sendButton;

};

#endif /* MAINWINDOW_HH_ */
