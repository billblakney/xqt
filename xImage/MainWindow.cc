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
  _Label2(0)
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MainWindow::onSliderValueChanged(int aValue)
{
  updateCopyImage(aValue);
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
void MainWindow::updateCopyImage(int aValue)
{
  QSize tSize = _OriginalImage->size();

  QImage tImage = _OriginalPixmap->toImage();

  for (int i = 0; i < tSize.width(); i++)
    for (int j = 0; j < tSize.height(); j++)
    {
      QRgb tColor = _OriginalImage->pixel(i,j);
      int tGray = qGray(tColor);
      if ( tGray <= aValue)
      {
        tImage.setPixel(i,j,Qt::black);
      }
    }

  *_CopyPixmap = _CopyPixmap->fromImage(tImage);
  _Label2->setPixmap(*_CopyPixmap);
}

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

  setMinimumSize(800,800);
}
