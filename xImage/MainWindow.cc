#include <cstdio>
#include <iostream>
#include <map>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QRgb>
#include "MainWindow.hh"

//  std::cout << "_checkBox: " << qPrintable(tChecked) << std::endl;

//-----------------------------------------------------------------------------
// constructor
//-----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *aParent)
: QWidget(aParent),
  _OriginalImage(0),
  _CopyImage(0),
  _OriginalPixmap(0),
  _CopyPixmap(0),
  _Slider(0),
  _Label2(0),
  _ODarkSquareColor(0),
  _OLiteSquareColor(0),
  _ODarkPieceColor(0),
  _OLitePieceColor(0),
  _NDarkSquareColor(0),
  _NLiteSquareColor(0),
  _NDarkPieceColor(0),
  _NLitePieceColor(0),
  _ContrastColor(0)
{
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
}

//-----------------------------------------------------------------------------
// Destructor.
//-----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
}

//-----------------------------------------------------------------------------
// Setup connections.
//-----------------------------------------------------------------------------
void MainWindow::setupConnections()
{
  std::cout << "Setting up connections" << std::endl;

  connect(_Slider, SIGNAL(valueChanged(int)),
      this, SLOT(onSliderValueChanged(int)));
}

//-----------------------------------------------------------------------------
// Load the image to be processed.
//-----------------------------------------------------------------------------
void MainWindow::loadImage(std::string aFilename)
{
  static int _first = true;

  if (_first)
  {
    QString tFilename(aFilename.c_str());
    _OriginalImage = new QImage(tFilename);
  }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MainWindow::onSliderValueChanged(int aValue)
{
  colorizeCopyImage(aValue);
}

//-----------------------------------------------------------------------------
// Compute a difference metric between two colors.
//-----------------------------------------------------------------------------
int MainWindow::colorDiff(QColor *aColor1,QColor *aColor2)
{
  return
      (abs(aColor1->red() - aColor2->red()) +
      abs(aColor1->green() - aColor2->green()) +
      abs(aColor1->blue() - aColor2->blue()));
}

//-----------------------------------------------------------------------------
// Get the normalized color that best matches a specified color.
//-----------------------------------------------------------------------------
QColor *MainWindow::getNormalizedColor(QColor &aColor)
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

//if (tMinDiff > 30)
if (tMinDiff > 100)
{
  std::cout << "tMinDiff: " << tMinDiff << std::endl;
  return _ContrastColor;
}

  return tColor;
}

//-----------------------------------------------------------------------------
// Sets the color of each pixel image to the closest normalizing color.
//-----------------------------------------------------------------------------
void MainWindow::normalizeColors(QImage &aImage)
{
  QSize tSize = aImage.size();

  /*
   * If a pixel's color is not a normalized color, set it's color to the
   * closest normalized color.
   */
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
// Sets the color of pixel islands to the surrounding color.
// Note: Doesn't bother with the edge pixels.
//-----------------------------------------------------------------------------
void MainWindow::eliminateIslands(QImage &aImage)
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
// Estimates the center of a square on a board of specified dimension.
//-----------------------------------------------------------------------------
QPoint MainWindow::getSquareCenter(QSize aBoardSize,int aRow,int aCol)
{
  QPoint tCenter;

  float tX = (2.0*(aRow+1) -1)/(2.0*(float)ROWS);
  float tY = (2.0*(aCol+1) -1)/(2.0*(float)COLS);

  tCenter.setX(tX*aBoardSize.width());
  tCenter.setY(tY*aBoardSize.height());

  return tCenter;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
QRect MainWindow::getSquareAt(QImage &aImage,QPoint aSeed)
{
  QRect tRect;

  int tSeedX = aSeed.x();
  int tSeedY = aSeed.y();

  int tX = tSeedX;
  int tY = tSeedY;
std::cout << "square seed" << tSeedX << "," << tSeedY << std::endl;

  tX = tSeedX;
  tY = tSeedY;

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

    emphasizePoint(aImage,aSeed,tColor);

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

  return tSquare;
}

//-----------------------------------------------------------------------------
// Colorizes the copy image. The "colorize" operation changes each pixel in
// the image to the normalized color that best matches the pixel color.
//-----------------------------------------------------------------------------
void MainWindow::colorizeCopyImage(int /*aValue*/)
{
  // Get a copy of the original image, which will be "normalized".
  QImage tImage = _OriginalPixmap->toImage();
//  std::cout << "FORMAT: " << tImage.format() << std::endl;

  normalizeColors(tImage);
  eliminateIslands(tImage);

  QSize tSize = tImage.size();

  /*
   * Get estimate of the center of square 3,3.
   */
  QPoint tCenterAt33 = getSquareCenter(tSize,3,3);

  /*
   * Get the rectangle for square 3,3.
   */
  QRect tSquareAt33 = getSquareAt(tImage,tCenterAt33);

  QColor tYellow(Qt::yellow);

  emphasizePoint(tImage,tSquareAt33.topLeft(),tYellow);
  emphasizePoint(tImage,tSquareAt33.bottomRight(),tYellow);

  /*
   * Display the modified image.
   */
  *_CopyPixmap = _CopyPixmap->fromImage(tImage);
  _Label2->setPixmap(*_CopyPixmap);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MainWindow::emphasizePoint(QImage &aImage,QPoint aPoint,QColor aColor)
{
  emphasizePoint(aImage,aPoint.x(),aPoint.y(),aColor);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MainWindow::emphasizePoint(QImage &aImage,int aX,int aY,QColor aColor)
{
  QRgb tRgb = aColor.rgb();
  aImage.setPixel(aX,aY,tRgb);
  aImage.setPixel(aX-1,aY-1,tRgb);
  aImage.setPixel(aX-1,aY,tRgb);
  aImage.setPixel(aX-1,aY+1,tRgb);
  aImage.setPixel(aX+1,aY-1,tRgb);
  aImage.setPixel(aX+1,aY,tRgb);
  aImage.setPixel(aX+1,aY+1,tRgb);
  aImage.setPixel(aX,aY-1,tRgb);
  aImage.setPixel(aX,aY+1,tRgb);
}

//-----------------------------------------------------------------------------
// Finds the first square color along the YAxis from specified start point.
//-----------------------------------------------------------------------------
bool MainWindow::findColorAbove(QColor *aColor,QImage &aImage,int aX,int aY,
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
bool MainWindow::findColorBelow(QColor *aColor,QImage &aImage,int aX,int aY,
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
bool MainWindow::findColorRight(QColor *aColor,QImage &aImage,int aX,int aY,
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
// Finds the first square color along the XAxis from specified start point.
//-----------------------------------------------------------------------------
bool MainWindow::findColorLeft(QColor *aColor,QImage &aImage,int aX,int aY,
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
//-----------------------------------------------------------------------------
void MainWindow::setupView(std::string aFilename)
{
  std::cout << "setupView" << std::endl;

  /*
   * Load the original image, and make a copy.
   */
  loadImage(aFilename);
  _CopyImage = new QImage(_OriginalImage->copy());

  /*
   * Create the images widget.
   */
  QWidget *tImagesWidget = new QWidget(this);

  QHBoxLayout *tImagesLayout = new QHBoxLayout(tImagesWidget);

  _OriginalPixmap = new QPixmap();
  _OriginalPixmap->convertFromImage(*_OriginalImage);
  QLabel *tLabel1 = new QLabel(this);
  tLabel1->setPixmap(*_OriginalPixmap);
  tImagesLayout->addWidget(tLabel1);

  _CopyPixmap = new QPixmap;
  _CopyPixmap->convertFromImage(*_CopyImage);
  _Label2 = new QLabel(this);
  _Label2->setPixmap(*_CopyPixmap);
  tImagesLayout->addWidget(_Label2);

  /*
   * Create the controls widget.
   */
  QWidget *tControlsWidget = new QWidget(this);

  QHBoxLayout *tControlsLayout = new QHBoxLayout(tControlsWidget);

  _Slider = new QSlider(Qt::Horizontal,tControlsWidget);
  _Slider->setMinimum(0);
  _Slider->setMaximum(255);
  _Slider->setTracking(true);
  _Slider->setTickInterval(16);
  _Slider->setTickPosition(QSlider::TicksBothSides);
  tControlsLayout->addWidget(_Slider);

//  tControlsWidget->setLayout(tControlsLayout);

  QVBoxLayout *tLayout = new QVBoxLayout(this);
  tLayout->addWidget(tImagesWidget);
  tLayout->addWidget(tControlsWidget);

  QLabel *t3 = new QLabel("test label3",tControlsWidget);
  tLayout->addWidget(t3);

  setLayout(tLayout);

  QSize tSize = _OriginalImage->size();
  std::cout << "Image size: " << tSize.width() << "," << tSize.height() << std::endl;

  std::map<int,int>::iterator tIter;
  std::map<int,int> tColorCounts; // key qGray, value count

  for (int i = 0; i < tSize.width(); i++)
    for (int j = 0; j < tSize.height(); j++)
    {
      QRgb tColor = _OriginalImage->pixel(i,j);
      int tGray = qGray(tColor);

      tIter = tColorCounts.find(tGray);

      if (tIter != tColorCounts.end())
      {
        tColorCounts[tGray]++;
      }
      else
      {
        tColorCounts[tGray] = 1;
      }
    }

std::cout << "Color count: " << tColorCounts.size() << std::endl;

#if 0
  for (tIter = tColorCounts.begin(); tIter != tColorCounts.end(); tIter++)
  {
    std::cout << "Color/count: "
        << tIter->first << "/"
        << tIter->second << std::endl;
  }
#endif

  std::cout << "Saving altered image..." << std::endl;

  setMinimumSize(1000,800);
}
