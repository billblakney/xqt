#ifndef BOARD_HH
#define BOARD_HH

#include <QPalette>
#include <QVBoxLayout>
#include <QWidget>
#include "Square.hh"

#include "GridCoord.hh"

class Board: public QWidget
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

  Board(QWidget *aParent);
  virtual ~Board();
  void setup();
  void setPerspective(Perspective aPerspective);
  void showSquareColors(bool aShow);

public slots:

  void onSquareClick(int aRank,int aFile,bool aIsLeft);

protected:

  QPalette _WhitePalette;
  QPalette _BlackPalette;
  Square *_Squares[8][8];
  QVBoxLayout *_SquareHolders[8][8];

  Perspective _Perspective;
  Square::Coord _LastClickedSquare;

  GridCoord mapSquareToGrid(Square::Coord aSquare);
  Square::Coord mapGridToSquare(GridCoord aGridCoord);

  void configurePalettes();
  bool isLightSquare(Square::Coord aSquare);
  void loadPerspective();
  void loadWhitePerspective();
  void loadBlackPerspective();
  void highlightFrame(GridCoord aGridCoord);

};

#endif //BOARD_HH
