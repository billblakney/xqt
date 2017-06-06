#ifndef MAINWINDOW_HH_
#define MAINWINDOW_HH_

#include <string>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QStyle>

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
  QPushButton *_SonarButton1;
  QPushButton *_SonarButton2;
  QPushButton *_button1;
  QPushButton *_button3;

  QPalette getFunkyPalette(QPalette aPalette);
  QPalette getSonarPalette(QPalette aPalette);

  QPushButton *createButton1();
  QPushButton *createButton3();

#ifndef QT_V5
  QPushButton *createSonarButton(
      QString aName,QStyle *aStyle,bool aIsCheckable = true);
#else
  QPushButton *createSonarButton(
      QString aName,QString aStyle,bool aIsCheckable = true);
#endif
};

#endif /* MAINWINDOW_HH_ */
