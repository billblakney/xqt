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

  QPalette getFunkyPalette(QPalette aPalette);
  QPalette getSonarPalette(QPalette aPalette);

  QPushButton *createButtonWithColorGroups();

  QPushButton *createButton(
      QString aName,QStyle *aStyle,bool aIsCheckable = true);

#ifdef QT_V5
  QPushButton *createButton(
      QString aName,QString aStyle,bool aIsCheckable = true);
#endif
};

#endif /* MAINWINDOW_HH_ */
