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
  _NLitePieceColor(0)
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

  return tColor;
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

  QSize tSize = tImage.size();

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

      tImage.setPixel(i,j,tNormalizedColor->rgb());
    }

  /*
   * If a pixel is surrounded by pixels of some other color, change its color
   * to that of those surrounding pixels. Don't bother with the edge cases.
   */
  for (int i = 1; i < tSize.width()-1; i++)
    for (int j = 1; j < tSize.height()-1; j++)
    {
      QRgb tRgb = tImage.pixel(i,j);

      QRgb tLeftRgb = tImage.pixel(i-1,j);
      QRgb tRightRgb = tImage.pixel(i+1,j);
      QRgb tAboveRgb = tImage.pixel(i,j-1);
      QRgb tBelowRgb = tImage.pixel(i,j+1);

      if ((tRgb != tLeftRgb)
       && (tRgb != tRightRgb)
       && (tRgb != tAboveRgb)
       && (tRgb != tBelowRgb)
       && (tLeftRgb == tRightRgb)
       && (tLeftRgb == tAboveRgb)
       && (tLeftRgb == tBelowRgb))
      {
        std::cout << "Found island pixel at " << i << "," << j << std::endl;
        tImage.setPixel(i,j,tLeftRgb);
      }
    }

  /*
   * Find square boundaries.
   */
  int tStartX = ((float)7/(float)16)*(float)tSize.width();
  int tStartY = ((float)7/(float)16)*(float)tSize.height();

  int tX = tStartX;
  int tY = tStartY;
std::cout << "start x,y: " << tStartX << "," << tStartY << std::endl;

  QColor tColor = findSquareColorOnYAxis(tImage,false,tX,tY);

  if (tY < 0)
  {
    std::cout << "ERROR: Couldn't find square color" << std::endl;
    exit(0);
  }
  else if (tColor == *_NDarkSquareColor)
  {
    std::cout << "Start point is DarkSquare" << std::endl;
  }
  else if (tColor == *_NLiteSquareColor)
  {
    std::cout << "Start point is LiteSquare!!" << std::endl;
  }
  else
  {
    std::cout << "ERROR Bad start point!!" << std::endl;
  }

  /*
   * Display the modified image.
   */
  *_CopyPixmap = _CopyPixmap->fromImage(tImage);
  _Label2->setPixmap(*_CopyPixmap);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
QColor MainWindow::findSquareColorOnYAxis(QImage &aImage,bool aSearchBelow,
    int aX, int &aY)
{
  int tIncrement = ((aSearchBelow==true)?1:-1);
  int tBound = ((aSearchBelow==true)?aImage.height()-1:0);

  std::cout << "tIncr,tBound: " << tIncrement << "," << tBound << std::endl;

  if (aSearchBelow)
  {
    while (aY <= tBound)
    {
      QColor tColor = QColor(aImage.pixel(aX,aY));
      if (tColor == *_NDarkSquareColor || tColor == *_NLiteSquareColor)
      {
        return tColor;
      }
      aY += tIncrement;
std:: cout << "below aY: " << aY << std::endl;
    }
  }
  else
  {
    while (aY >= tBound)
    {
      QColor tColor = QColor(aImage.pixel(aX,aY));
      if (tColor == *_NDarkSquareColor || tColor == *_NLiteSquareColor)
      {
        return tColor;
      }
      aY += tIncrement;
std:: cout << "above aY: " << aY << std::endl;
    }
  }
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

  setMinimumSize(800,1000);
}
