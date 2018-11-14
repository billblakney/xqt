#ifndef MAINWINDOW_HH_
#define MAINWINDOW_HH_

#include <string>
#include <QCheckBox>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include "Board.hh"
#include "Square.hh"
#include "GridCoord.hh"

class MainWindow: public QWidget
{
  Q_OBJECT
public:

  MainWindow(QWidget *aParent);

  virtual ~MainWindow();

	void setup();

public slots:

  void onFlipBoardToggled(bool aChecked);

protected:

  QPushButton *_FlipBoardToggle;
  QLabel *_FindLabel;
  Board *_Board;

	void setupView();
	void setupConnections();
};

#endif /* MAINWINDOW_HH_ */
