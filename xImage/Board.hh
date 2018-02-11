#ifndef BOARD_HH_
#define BOARD_HH_

#include <string>
#include <QColor>
#include <QImage>
#include <QPixmap>
#include <QPoint>
#include <QRect>
#include <QSize>
#include "Square.hh"

class Board
{
public:

  enum BoardElement {eNone, eDarkSquare, eLiteSquare, eDarkPiece, eLitePiece};

  static const int ROWS = 8;
  static const int COLS = 8;

  static QPoint getSquareCenter(QSize aBoardSize,int aRow,int aCol);
  static QPoint getNeighborSquareCenter(QRect aFromSquare,int aRowOffset,
      int aColOffset);

  static int colorDiff(QColor *aColor1,QColor *aColor2);//TOOD utility

  Board(std::string aImageFilename);//TODO later create copy inside

  virtual ~Board();

  QPixmap *getOriginalPixmap();
  QPixmap *getCopyPixmap();
  QImage *getOriginalImage();
  QImage *getCopyImage();

  void processImage();

protected:

  /* Color of the original image to be processed */
  QColor   *_ODarkSquareColor;
  QColor   *_OLiteSquareColor;
  QColor   *_ODarkPieceColor;
  QColor   *_OLitePieceColor;

  /* Color of the "color normalized" image. */
  QColor   *_NDarkSquareColor;
  QColor   *_NLiteSquareColor;
  QColor   *_NDarkPieceColor;
  QColor   *_NLitePieceColor;

  QColor   *_ContrastColor;

  QImage *_OriginalImage;
  QImage *_CopyImage;
  QPixmap *_OriginalPixmap;
  QPixmap *_CopyPixmap;

  Square _Squares[Board::ROWS][Board::COLS];

  void normalizeColors(QImage &aImage);
  QColor *getNormalizedColor(QColor &aColor);
  void eliminateIslands(QImage &aImage);
  void addSquareAt(int aRow,int aCol,QImage &aImage,QPoint aCenter);
  QRect getSquareAt(QImage &aImage,QPoint aSeed);
  void generateSimilarRowSquares(QImage &aImage,
      int aSeedRow,int aSeedCol,int aOffset,int aNumSquares);
  bool findColorAbove(QColor *aColor,QImage &aImage,int aX,int aY,
      int &aFoundAtY);
  bool findColorBelow(QColor *aColor,QImage &aImage,int aX,int aY,
      int &aFoundAtY);
  bool findColorLeft(QColor *aColor,QImage &aImage,int aX,int aY,
      int &aFoundAtX);
  bool findColorRight(QColor *aColor,QImage &aImage,int aX,int aY,
      int &aFoundAtX);
  void contrastPiece(QImage &aImage,QRect aSquare,
      Board::BoardElement aSquareType);
  void emphasizePoint(QImage &aImage,QPoint aPoint,QColor aColor,
      int aRadius = 1);
  void emphasizePoint(QImage &aImage,int aX,int aY,QColor aColor,
      int aRadius = 1);

  QColor *getPieceColor(QImage &aImage,QRect aSquare,
    QColor *aSquareColor);

};

#endif /* BOARD_HH_ */
