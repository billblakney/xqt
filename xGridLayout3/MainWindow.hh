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
#include "Square.hh"

class MainWindow: public QWidget
{
  Q_OBJECT
public:

  const int RANKS = 8;
  const int FILES = 8;

  QString _FileNames[8] = {"a", "b", "c", "d", "e", "f", "g", "h"};
  QString _RankNames[8] = {"1", "2", "3", "4", "5", "6", "7", "8"};

  MainWindow(QWidget *aParent);

  virtual ~MainWindow();

	void setupView();

public slots:

void onFlipBoardToggled(bool aChecked);
void onSquareClick(int aRank,int aFile,bool aIsLeft);

protected:

  QPushButton *_FlipBoardToggle;
  Square *_Squares[8][8];
  QVBoxLayout *_SquareHolders[8][8];

  int _LastClickedRank;
  int _LastClickedFile;

  void loadWhitePerspective();
  void loadBlackPerspective();
  void highlightFrame(int aRow, int aCol);
};

#endif /* MAINWINDOW_HH_ */
