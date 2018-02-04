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
//-----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MainWindow::setupConnections()
{
  std::cout << "Setting up connections" << std::endl;

  connect(_Slider, SIGNAL(valueChanged(int)),
      this, SLOT(onSliderValueChanged(int)));
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MainWindow::loadOriginalImage()
{
  static int _first = true;

  if (_first)
  {
    /*
     * Load the image.
     */
    //QImage tImage("/cygdrive/m/workspace/xqt/xImange/images/unnamed.jpg");
    //QImage tImage("/cygdrive/m/workspace/xqt/xImage/images/unnamed.jpg");
    _OriginalImage = new QImage(
        "M://workspace/xqt/xImage/images/unnamed.jpg");
  }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MainWindow::onSliderValueChanged(int aValue)
{
  updateCopyImage(aValue);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int MainWindow::colorDiff(QColor *aColor1,QColor *aColor2)
{
  return
      (abs(aColor1->red() - aColor2->red()) +
      abs(aColor1->green() - aColor2->green()) +
      abs(aColor1->blue() - aColor2->blue()));
}

//-----------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
void MainWindow::updateCopyImage(int aValue)
{
  // Get a copy of the original image, which will be "normalized".
  QImage tImage = _OriginalPixmap->toImage();
  std::cout << "FORMAT: " << tImage.format() << std::endl;

//  QSize tSize = _OriginalImage->size();
  QSize tSize = tImage.size();

  for (int i = 0; i < tSize.width(); i++)
    for (int j = 0; j < tSize.height(); j++)
    {
      QRgb tRgb = _OriginalImage->pixel(i,j);
      QColor tOriginalColor = QColor(tRgb);

      QColor *tNormalizedColor = getNormalizedColor(tOriginalColor);

      tImage.setPixel(i,j,tNormalizedColor->rgb());

#if 0
      int tGray = qGray(tColor);
      if ( tGray <= aValue)
      {
//std::cout << "BLACK" << std::endl;
        tImage.setPixel(i,j,qRgb(0,99,99));
//        tImage.setPixel(i,j,qRgb(Qt::blue));
//        tImage.setPixel(i,j,2);
      }
      else
      {
//std::cout << "WHITE" << std::endl;
//        tImage.setPixel(i,j,qRgb(Qt::gray));
        tImage.setPixel(i,j,qRgb(99,255,0));
      }
#endif
    }

  *_CopyPixmap = _CopyPixmap->fromImage(tImage);
  _Label2->setPixmap(*_CopyPixmap);
}

#if 0
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MainWindow::updateCopyImage(int aValue)
{
  QImage tImage = _OriginalPixmap->toImage();
  std::cout << "FORMAT: " << tImage.format() << std::endl;

//  QSize tSize = _OriginalImage->size();
  QSize tSize = tImage.size();

  for (int i = 0; i < tSize.width(); i++)
    for (int j = 0; j < tSize.height(); j++)
    {
      QRgb tColor = _OriginalImage->pixel(i,j);
      int tGray = qGray(tColor);
      if ( tGray <= aValue)
      {
//std::cout << "BLACK" << std::endl;
        tImage.setPixel(i,j,qRgb(0,99,99));
//        tImage.setPixel(i,j,qRgb(Qt::blue));
//        tImage.setPixel(i,j,2);
      }
      else
      {
//std::cout << "WHITE" << std::endl;
//        tImage.setPixel(i,j,qRgb(Qt::gray));
        tImage.setPixel(i,j,qRgb(99,255,0));
      }
    }

  *_CopyPixmap = _CopyPixmap->fromImage(tImage);
  _Label2->setPixmap(*_CopyPixmap);
}
#endif

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MainWindow::setupView()
{
  std::cout << "setupView" << std::endl;

  /*
   * Load the original image, and make a copy.
   */
  loadOriginalImage();
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
