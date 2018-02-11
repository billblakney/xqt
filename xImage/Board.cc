#include <iostream>
#include <QRgb>
#include "Board.hh"
#include "ImageUtil.hh"

using namespace imgu;

//-----------------------------------------------------------------------------
// Compute a difference metric between two colors.
// TODO utiity class
//-----------------------------------------------------------------------------
int Board::colorDiff(QColor *aColor1,QColor *aColor2)
{
  return
      (abs(aColor1->red() - aColor2->red()) +
      abs(aColor1->green() - aColor2->green()) +
      abs(aColor1->blue() - aColor2->blue()));
}

//-----------------------------------------------------------------------------
// Estimates the center of a square on a board of specified dimension.
//-----------------------------------------------------------------------------
QPoint Board::getSquareCenter(QSize aBoardSize,int aRow,int aCol)
{
  QPoint tCenter;

  float tX = (2.0*(aRow+1) -1)/(2.0*(float)Board::ROWS);
  float tY = (2.0*(aCol+1) -1)/(2.0*(float)Board::COLS);

  tCenter.setX(tX*aBoardSize.width());
  tCenter.setY(tY*aBoardSize.height());

  return tCenter;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
QPoint Board::getNeighborSquareCenter(QRect aFromSquare,int aRowOffset,
    int aColOffset)
{
  QPoint tCenter = aFromSquare.center();

  tCenter.setY(tCenter.y() + aRowOffset * aFromSquare.height());
  tCenter.setX(tCenter.x() + aColOffset * aFromSquare.width());

  return tCenter;
}

Board::Board(std::string aImageFilename)
 :_ODarkSquareColor(0),
  _OLiteSquareColor(0),
  _ODarkPieceColor(0),
  _OLitePieceColor(0),
  _NDarkSquareColor(0),
  _NLiteSquareColor(0),
  _NDarkPieceColor(0),
  _NLitePieceColor(0),
  _ContrastColor(0),
  _OriginalImage(0),
  _CopyImage(0),
  _OriginalPixmap(0),
  _CopyPixmap(0)
{
  std::cout << "Board ctor" << std::endl;

  _ODarkSquareColor = new QColor(221,145,69);
  _OLiteSquareColor = new QColor(254,206,157);
  _ODarkPieceColor = new QColor(0,0,0);
  _OLitePieceColor = new QColor(255,255,255);

  _NDarkSquareColor = new QColor(72,72,72);
//  _NDarkSquareColor = new QColor(Qt::blue);//TODO rm
  _NLiteSquareColor = new QColor(194,194,194);
  _NDarkPieceColor = new QColor(0,0,0);
  _NLitePieceColor = new QColor(255,255,255);

  _ContrastColor = new QColor(Qt::yellow);

  for (int i = 0; i < Board::ROWS; i++)
    for( int j = 0; j < Board::COLS; j++)
    {
      _Squares[i][j] = Square();
    }

  std::cout << "Loading image " << aImageFilename << std::endl;
  QString tImageFilename(aImageFilename.c_str());
  _OriginalImage = new QImage(tImageFilename);
  //  std::cout << "FORMAT: " << _OriginalImage.format() << std::endl;

  _CopyImage = new QImage(_OriginalImage->copy());
  _OriginalPixmap = new QPixmap();
  _OriginalPixmap->convertFromImage(*_OriginalImage);

  _CopyPixmap = new QPixmap();
  _CopyPixmap->convertFromImage(*_CopyImage);
}

Board::~Board()
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
QPixmap *Board::getOriginalPixmap()
{
  return _OriginalPixmap;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
QPixmap *Board::getCopyPixmap()
{
  return _CopyPixmap;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
QImage *Board::getOriginalImage()
{
  return _OriginalImage;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
QImage *Board::getCopyImage()
{
  return _CopyImage;
}

//-----------------------------------------------------------------------------
// Colorizes the copy image. The "colorize" operation changes each pixel in
// the image to the normalized color that best matches the pixel color.
//-----------------------------------------------------------------------------
void Board::processImage()
{
std::cout << "in processImage" << std::endl;
  // Get a copy of the original image.
  QImage tImage = _OriginalPixmap->toImage();

  normalizeColors(tImage);
  eliminateIslands(tImage);

  QSize tSize = tImage.size();

  /*
   * First, get all the lite squares.
   */
  // Get the initial square at 3,3. Then get the others on the row.
  QPoint tCenter = getSquareCenter(tSize,3,3);
  addSquareAt(3,3,tImage,tCenter);
  generateSimilarRowSquares(tImage,3,3,-2,1);
  generateSimilarRowSquares(tImage,3,3,2,2);

  // Get the square at 2,0, then the others on the row.
  tCenter = getNeighborSquareCenter(_Squares[3][1]._Rect,-1,-1);
  addSquareAt(2,0,tImage,tCenter);
  generateSimilarRowSquares(tImage,2,0,2,3);

  // Get the square at 1,1, then the others on the row.
  tCenter = getNeighborSquareCenter(_Squares[2][0]._Rect,-1,1);
  addSquareAt(1,1,tImage,tCenter);
  generateSimilarRowSquares(tImage,1,1,2,3);

  // Get the square at 0,0, then the others on the row.
  tCenter = getNeighborSquareCenter(_Squares[1][1]._Rect,-1,-1);
  addSquareAt(0,0,tImage,tCenter);
  generateSimilarRowSquares(tImage,0,0,2,3);

  // Get the square at 4,0, then the others on the row.
  tCenter = getNeighborSquareCenter(_Squares[3][1]._Rect,1,-1);
  addSquareAt(4,0,tImage,tCenter);
  generateSimilarRowSquares(tImage,4,0,2,3);

  // Get the square at 5,1, then the others on the row.
  tCenter = getNeighborSquareCenter(_Squares[4][0]._Rect,1,1);
  addSquareAt(5,1,tImage,tCenter);
  generateSimilarRowSquares(tImage,5,1,2,3);

  // Get the square at 6,0, then the others on the row.
  tCenter = getNeighborSquareCenter(_Squares[5][1]._Rect,1,-1);
  addSquareAt(6,0,tImage,tCenter);
  generateSimilarRowSquares(tImage,6,0,2,3);

  // Get the square at 7,1, then the others on the row.
  tCenter = getNeighborSquareCenter(_Squares[6][0]._Rect,1,1);
  addSquareAt(7,1,tImage,tCenter);
  generateSimilarRowSquares(tImage,7,1,2,3);

  /*
   * Contrast the pieces.
   */
contrastPiece(tImage,_Squares[3][3]._Rect,Board::eLiteSquare);

  _CopyPixmap->convertFromImage(tImage);

  std::cout << "Done processing image" << std::endl;
}

//-----------------------------------------------------------------------------
// Sets the color of each pixel image to the closest normalizing color.
//-----------------------------------------------------------------------------
void Board::normalizeColors(QImage &aImage)
{
  QSize tSize = aImage.size();

  for (int i = 0; i < tSize.width(); i++)
    for (int j = 0; j < tSize.height(); j++)
    {
      QRgb tRgb = _OriginalImage->pixel(i,j);
      QColor tOriginalColor = QColor(tRgb);

      QColor *tNormalizedColor = getNormalizedColor(tOriginalColor);

      aImage.setPixel(i,j,tNormalizedColor->rgb());
    }
}

//-----------------------------------------------------------------------------
// Get the normalized color that best matches a specified color.
//-----------------------------------------------------------------------------
QColor *Board::getNormalizedColor(QColor &aColor)
{
  QColor *tColor = _NDarkSquareColor;
  int tMinDiff = colorDiff(&aColor,_ODarkSquareColor);

  int tDiff = colorDiff(&aColor,_OLiteSquareColor);
  if (tDiff < tMinDiff)
  {
    tColor = _NLiteSquareColor;
    tMinDiff = tDiff;
  }

  tDiff = colorDiff(&aColor,_ODarkPieceColor);
  if (tDiff < tMinDiff)
  {
    tColor = _NDarkPieceColor;
    tMinDiff = tDiff;
  }

  tDiff = colorDiff(&aColor,_OLitePieceColor);
  if (tDiff < tMinDiff)
  {
    tColor = _NLitePieceColor;
    tMinDiff = tDiff;
  }

//if (tMinDiff > 30)//TODO
if (tMinDiff > 100)
{
//  std::cout << "tMinDiff: " << tMinDiff << std::endl;//TODO count'em?
  return _ContrastColor;
}

  return tColor;
}

//-----------------------------------------------------------------------------
// Sets the color of pixel islands to the surrounding color.
// Note: Doesn't bother with the edge pixels.
//-----------------------------------------------------------------------------
void Board::eliminateIslands(QImage &aImage)
{
  QSize tSize = aImage.size();

  int tNumIslands = 0;

  for (int i = 1; i < tSize.width()-1; i++)
    for (int j = 1; j < tSize.height()-1; j++)
    {
      QRgb tRgb = aImage.pixel(i,j);

      QRgb tLeftRgb = aImage.pixel(i-1,j);
      QRgb tRightRgb = aImage.pixel(i+1,j);
      QRgb tAboveRgb = aImage.pixel(i,j-1);
      QRgb tBelowRgb = aImage.pixel(i,j+1);

      if ((tRgb != tLeftRgb)
       && (tRgb != tRightRgb)
       && (tRgb != tAboveRgb)
       && (tRgb != tBelowRgb)
       && (tLeftRgb == tRightRgb)
       && (tLeftRgb == tAboveRgb)
       && (tLeftRgb == tBelowRgb))
      {
        std::cout << "Found island pixel at " << i << "," << j << std::endl;
        tNumIslands++;
        aImage.setPixel(i,j,tLeftRgb);
      }
    }

  std::cout << "Number of island pixel removed: " << tNumIslands << std::endl;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Board::addSquareAt(int aRow,int aCol,QImage &aImage,QPoint aCenter)
{
  QRect tRect = getSquareAt(aImage,aCenter);
  _Squares[aRow][aCol] = Square(aRow,aCol,tRect);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
QRect Board::getSquareAt(QImage &aImage,QPoint aSeed)
{
  QRect tRect;

  int tSeedX = aSeed.x();
  int tSeedY = aSeed.y();
std::cout << "square seed " << tSeedX << "," << tSeedY << std::endl;

  bool tFoundIt = false;

  int tUpperY = -1;
  int tLowerY = -1;
  int tLeftX = -1;
  int tRightX = -1;

  // above
  tFoundIt = findColorAbove(
      _NLiteSquareColor,aImage,tSeedX,tSeedY,tUpperY);
  if (!tFoundIt)
  {
    std::cout << "ERROR: findColorAbove failed for Lite square" << std::endl;
  }
  tFoundIt = findColorAbove(
      _NDarkSquareColor,aImage,tSeedX,tSeedY,tUpperY);
  if (!tFoundIt)
  {
    std::cout << "ERROR: findColorAbove failed for Dark square" << std::endl;
  }
  tUpperY++;

  // below
  tFoundIt = findColorBelow(
      _NLiteSquareColor,aImage,tSeedX,tSeedY,tLowerY);
  if (!tFoundIt)
  {
    std::cout << "ERROR: findColorBelow failed for Lite square" << std::endl;
  }
  tFoundIt = findColorBelow(
      _NDarkSquareColor,aImage,tSeedX,tSeedY,tLowerY);
  if (!tFoundIt)
  {
    std::cout << "ERROR: findColorBelow failed for Dark square" << std::endl;
  }
  tLowerY--;

  // left
  tFoundIt = findColorLeft(
      _NLiteSquareColor,aImage,tSeedX,tSeedY,tLeftX);
  if (!tFoundIt)
  {
    std::cout << "ERROR: findColorLeft failed for Lite square" << std::endl;
  }
  tFoundIt = findColorLeft(
      _NDarkSquareColor,aImage,tSeedX,tSeedY,tLeftX);
  if (!tFoundIt)
  {
    std::cout << "ERROR: findColorLeft failed for Dark square" << std::endl;
  }
  tLeftX++;

  // right
  tFoundIt = findColorRight(
      _NLiteSquareColor,aImage,tSeedX,tSeedY,tRightX);
  if (!tFoundIt)
  {
    std::cout << "ERROR: findColorRight failed for Lite square" << std::endl;
  }
  tFoundIt = findColorRight(
      _NDarkSquareColor,aImage,tSeedX,tSeedY,tRightX);
  if (!tFoundIt)
  {
    std::cout << "ERROR: findColorRight failed for Dark square" << std::endl;
  }
  tRightX--;

  int tShowDebugPoints = true;
  if( tShowDebugPoints)
  {
    QColor tColor(Qt::blue);

    emphasizePoint(aImage,aSeed,tColor,3);

    QPoint tStartAbove(tSeedX,tUpperY);
    QPoint tStartBelow(tSeedX,tLowerY);
    QPoint tStartLeft(tLeftX,tSeedY);
    QPoint tStartRight(tRightX,tSeedY);

    emphasizePoint(aImage,tStartAbove,tColor);
    emphasizePoint(aImage,tStartBelow,tColor);
    emphasizePoint(aImage,tStartLeft,tColor);
    emphasizePoint(aImage,tStartRight,tColor);
  }

  QPoint tTopLeft(tLeftX,tUpperY);
  QPoint tBottomRight(tRightX,tLowerY);
  QRect tSquare(tTopLeft,tBottomRight);

  if( tShowDebugPoints)
  {
    QColor tYellow(Qt::yellow);
    emphasizePoint(aImage,tSquare.topLeft(),tYellow);
    emphasizePoint(aImage,tSquare.bottomRight(),tYellow);
  }

  return tSquare;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Board::generateSimilarRowSquares(QImage &aImage,
    int aSeedRow,int aSeedCol,int aOffset,int aNumSquares)
{
  int tCol = aSeedCol;

  for (int i = 0; i < aNumSquares; i++)
  {
    QPoint tCenter = getNeighborSquareCenter(
        _Squares[aSeedRow][tCol]._Rect,0,aOffset);
    tCol += aOffset;
    addSquareAt(aSeedRow,tCol,aImage,tCenter);
  }
}

//-----------------------------------------------------------------------------
// Finds the first square color along the YAxis from specified start point.
//-----------------------------------------------------------------------------
bool Board::findColorAbove(QColor *aColor,QImage &aImage,int aX,int aY,
    int &aFoundAtY)
{
  aFoundAtY = aY;

  while (aFoundAtY >= 0)
  {
    QColor tColor = QColor(aImage.pixel(aX,aFoundAtY));

    if (tColor == *aColor)
    {
      return true;
    }
    aFoundAtY--;
  }

  return false;
}

//-----------------------------------------------------------------------------
// Finds the first square color along the YAxis from specified start point.
//-----------------------------------------------------------------------------
bool Board::findColorBelow(QColor *aColor,QImage &aImage,int aX,int aY,
    int &aFoundAtY)
{
  aFoundAtY = aY;

  while (aFoundAtY <= aImage.height()-1)
  {
    QColor tColor = QColor(aImage.pixel(aX,aFoundAtY));

    if (tColor == *aColor)
    {
      return true;
    }
    aFoundAtY++;
  }

  return false;
}

//-----------------------------------------------------------------------------
// Finds the first square color along the XAxis from specified start point.
//-----------------------------------------------------------------------------
bool Board::findColorLeft(QColor *aColor,QImage &aImage,int aX,int aY,
    int &aFoundAtX)
{
  aFoundAtX = aX;

  while (aFoundAtX >= 0)
  {
    QColor tColor = QColor(aImage.pixel(aFoundAtX,aY));
    if (tColor == *aColor)
    {
      return true;
    }
    aFoundAtX--;
  }

  return false;
}

//-----------------------------------------------------------------------------
// Finds the first square color along the XAxis from specified start point.
//-----------------------------------------------------------------------------
bool Board::findColorRight(QColor *aColor,QImage &aImage,int aX,int aY,
    int &aFoundAtX)
{
  aFoundAtX = aX;

  while (aFoundAtX <= aImage.width()-1)
  {
    QColor tColor = QColor(aImage.pixel(aFoundAtX,aY));
    if (tColor == *aColor)
    {
      return true;
    }
    aFoundAtX++;
  }

  return false;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Board::contrastPiece(QImage &aImage,QRect aSquare,
    Board::BoardElement aSquareType)
{
  QColor *tSquareColor = ((aSquareType == Board::eLiteSquare)?
      _NLiteSquareColor:_NDarkSquareColor);

  QColor *tPieceColor = getPieceColor(aImage,aSquare,tSquareColor);

  int tStartX = aSquare.topLeft().x();
  int tStartY = aSquare.topLeft().y();
  int tWidth = aSquare.width();
  int tHeight = aSquare.height();

  for (int i = 0; i < tWidth; i++)
    for (int j = 0; j < tHeight; j++)
    {
      int tX = tStartX + i;
      int tY = tStartY + j;

      QColor tColor = QColor(aImage.pixel(tX,tY));

      if (tColor != *tSquareColor)
      {
        aImage.setPixel(tX,tY,tPieceColor->rgb());
      }
    }
}

//-----------------------------------------------------------------------------
// TODO  implement
//-----------------------------------------------------------------------------
QColor *Board::getPieceColor(QImage &aImage,QRect aSquare,
    QColor *aSquareColor)
{
  Q_UNUSED(aImage);
  Q_UNUSED(aSquare);
  Q_UNUSED(aSquareColor);
  return _NDarkPieceColor;
}

