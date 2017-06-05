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

  MainWindow(QWidget *aParent);

  virtual ~MainWindow();

	void setupView();

public slots:

//  void onSend();

protected:

//  QCheckBox *_checkBox;
//  QLabel *_label1;
//  QLabel *_label2;
//  QLineEdit *_lineEdit1;
//  QLineEdit *_lineEdit2;
//  QPushButton *_startButton;

  QPushButton *_BasicButton;
  QPushButton *_BasicCheckableButton;
  QPushButton *_StylizedButton;
  QPushButton *_button1;
  QPushButton *_button3;

  QPalette getFunkyPalette(QPalette aPalette);
  QPalette getSteelPalette(QPalette aPalette);

  QPushButton *createStylizedButton();
  QPushButton *createButton1();
  QPushButton *createButton3();
};

#endif /* MAINWINDOW_HH_ */
