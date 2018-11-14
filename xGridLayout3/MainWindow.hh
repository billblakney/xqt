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
#include "GridCoord.hh"

class MainWindow: public QWidget
{
  Q_OBJECT
public:

  enum Perspective {eWhite, eBlack};

  const int RANKS = 8;
  const int FILES = 8;
  const int ROWS = 8;
  const int COLS = 8;

  QString _FileNames[8] = {"a", "b", "c", "d", "e", "f", "g", "h"};
  QString _RankNames[8] = {"1", "2", "3", "4", "5", "6", "7", "8"};

  MainWindow(QWidget *aParent);

  virtual ~MainWindow();

	void setupView();

  GridCoord mapSquareToGrid(Square::Coord aSquare);
  Square::Coord mapGridToSquare(GridCoord aGridCoord);

public slots:

void onFlipBoardToggled(bool aChecked);
void onSquareClick(int aRank,int aFile,bool aIsLeft);

protected:

  QPalette _WhitePalette;
  QPalette _BlackPalette;
  QPushButton *_FlipBoardToggle;
  QLabel *_FindLabel;
  Square *_Squares[8][8];
  QVBoxLayout *_SquareHolders[8][8];

  Perspective _Perspective;
  Square::Coord _LastClickedSquare;

  void configurePalettes();
  bool isLightSquare(Square::Coord aSquare);
  void showSquareColors(bool aShow);
  void loadPerspective();
  void loadWhitePerspective();
  void loadBlackPerspective();
  void highlightFrame(GridCoord aGridCoord);
};

#endif /* MAINWINDOW_HH_ */
