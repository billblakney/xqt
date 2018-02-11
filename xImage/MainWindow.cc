#include <algorithm>
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
#include "Board.hh"

//  std::cout << "_checkBox: " << qPrintable(tChecked) << std::endl;

//-----------------------------------------------------------------------------
// constructor
//-----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *aParent)
: QWidget(aParent),
  _Slider(0),
  _Label2(0),
  _Board(0)
{
  std::cout << "MainWindow ctor" << std::endl;
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
//-----------------------------------------------------------------------------
void MainWindow::onSliderValueChanged(int aValue)
{
  _Board->processImage();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MainWindow::setupView(std::string aFilename)
{
  std::cout << "setupView" << std::endl;

  _Board = new Board(aFilename);
  _Board->processImage();

  QImage *tOriginalImage = _Board->getOriginalImage();

  /*
   * Create the images widget.
   */
  QWidget *tImagesWidget = new QWidget(this);

  QHBoxLayout *tImagesLayout = new QHBoxLayout(tImagesWidget);

  QLabel *tLabel1 = new QLabel(this);
  tLabel1->setPixmap(*_Board->getOriginalPixmap());
  tImagesLayout->addWidget(tLabel1);

  _Label2 = new QLabel(this);
  _Label2->setPixmap(*_Board->getCopyPixmap());
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

  QSize tSize = tOriginalImage->size();
  std::cout << "Image size: " << tSize.width() << "," << tSize.height() << std::endl;

  std::map<int,int>::iterator tIter;
  std::map<int,int> tColorCounts; // key qGray, value count

  for (int i = 0; i < tSize.width(); i++)
    for (int j = 0; j < tSize.height(); j++)
    {
      QRgb tColor = tOriginalImage->pixel(i,j);
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

  setMinimumSize(1400,800);
}
