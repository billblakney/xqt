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
  std::cout << "Updating with value " << aValue << std::endl;
  updateCopyImage(aValue);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MainWindow::setupConnections()
{
  std::cout << "Setting up connections" << std::endl;

//  QObject::connect(_Slider, SIGNAL(valueChanged(int)),
  connect(_Slider, SIGNAL(valueChanged(int)),
      this, SLOT(onSliderValueChanged(int)) );
}

#if 0
void MainWindow::onSend()
{
  std::cout << "onSend" << std::endl;
  QString tChecked = "false";
  if (_checkBox->checkState() == Qt::Checked)
  {
    tChecked = "true";
  }
  std::cout << "_checkBox: " << qPrintable(tChecked) << std::endl;
  std::cout << "_lineEdit1: " << qPrintable(_lineEdit1->text()) << std::endl;
  std::cout << "_lineEdit2: " << qPrintable(_lineEdit2->text()) << std::endl;
}
#endif

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
//      std::cout << "tGray, aValue: " << tGray << "," << aValue << std::endl;

//      if ( tGray <= 25)
//      if ( tGray <= 171)
      if ( tGray <= aValue)
      {
        tImage.setPixel(i,j,Qt::black);
//      std::cout << "SETTING PIXEL" << std::endl;
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

  loadOriginalImage();
  _CopyImage = new QImage(_OriginalImage->copy());

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


  QWidget *tControlsWidget = new QWidget(this);

  QHBoxLayout *tControlsLayout = new QHBoxLayout(tControlsWidget);

  _Slider = new QSlider(Qt::Horizontal,tControlsWidget);
  _Slider->setMinimum(0);
  _Slider->setMaximum(255);
  _Slider->setTracking(true);
  tControlsLayout->addWidget(_Slider);

  tControlsWidget->setLayout(tControlsLayout);

  QVBoxLayout *tLayout = new QVBoxLayout(this);
//  QHBoxLayout *tLayout = new QHBoxLayout(this);
  tLayout->addWidget(tImagesWidget);
  tLayout->addWidget(tControlsWidget);

  QLabel *t3 = new QLabel("test label3",tControlsWidget);
  tLayout->addWidget(t3);

  setLayout(tLayout);

//  updateCopyImage(220);
//      if ( tGray <= 25)
//      if ( tGray <= 171)
//      if ( tGray <= 220)

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
//
////      if ( tGray <= 25)
////      if ( tGray <= 171)
//      if ( tGray <= aValue)
//      {
////        _OriginalImage->setPixel(i,j,Qt::black);
//        _CopyImage->setPixel(i,j,Qt::black);
//      }
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

//  tImage.save("/home/bill/Downloads/modified.jpg");

#if 0
  QImage tImage("/home/bill/Downloads/unnamed.jpg");

  QSize tSize = tImage.size();
  std::cout << "Image size: " << tSize.width() << "," << tSize.height() << std::endl;

  std::map<QRgb,int> tColorCounts;
  std::map<QRgb,int>::iterator tIter;

  for (int i = 0; i < tSize.width(); i++)
    for (int j = 0; j < tSize.width(); j++)
    {
      QRgb tColor = tImage.pixel(i,j);

      tIter = tColorCounts.find(tColor);

      if (tIter != tColorCounts.end())
      {
        tColorCounts[tImage.pixel(i,j)]++;
      }
      else
      {
        tColorCounts[tImage.pixel(i,j)] = 1;
      }
    }

std::cout << "Color count: " << tColorCounts.size() << std::endl;

  for (tIter = tColorCounts.begin(); tIter != tColorCounts.end(); tIter++)
  {
    std::cout << "Color/count: "
        << tIter->first << "/"
        << tIter->second << std::endl;
  }

#endif
  setMinimumSize(800,800);
#if 0
#ifdef OLD
  std::cout << "setupView" << std::endl;

  _checkBox = new QCheckBox("CheckBox");

  _label1 = new QLabel("SomeReallyReallyLongLabel",this);
  _lineEdit1 = new QLineEdit();

  _label2 = new QLabel("Label",this);
  _lineEdit2 = new QLineEdit();

  QGridLayout *tGridLayout = new QGridLayout(this);
  tGridLayout->setRowStretch(1,0);
  tGridLayout->setRowStretch(2,0);

  tGridLayout->addWidget(_checkBox,0,0);
  tGridLayout->addWidget(_label1,1,0);
  tGridLayout->addWidget(_label2,2,0);

  tGridLayout->addWidget(_lineEdit1,1,1);
  tGridLayout->addWidget(_lineEdit2,2,1);

  QWidget *tEditorsWidget = new QWidget(this);
  tEditorsWidget->setLayout(tGridLayout);


  QPushButton *tSendButton = new QPushButton(QString("Send"),this);
  tSendButton->resize(100, 30);

  QObject::connect( tSendButton, SIGNAL(clicked()), this, SLOT(onSend()) );

  QHBoxLayout *tBoxLayout = new QHBoxLayout(this);
  tBoxLayout->setStretch(0,0);
  tBoxLayout->setStretch(1,1);
  tBoxLayout->addWidget(tEditorsWidget);
  tBoxLayout->addWidget(tSendButton);

//  resize(200,120);

  setLayout(tBoxLayout);
#else
  std::cout << "setupView" << std::endl;


  const int ROWS = 6;
  const int COLS = 10;
  QFrame *tGrid[ROWS][COLS];

  QString _Notes[ROWS][COLS];
  for (int i = 0; i < ROWS; i++)
    for (int j = 0; j < COLS; j++)
    {
      _Notes[0][0] = "x";
    }
  _Notes[0][0] = "E";
  _Notes[0][1] = "F";
  _Notes[0][2] = "f#";
  _Notes[0][3] = "G";
  _Notes[0][4] = "g#";
  _Notes[0][5] = "A";
  _Notes[0][6] = "a#";
  _Notes[0][7] = "B";
  _Notes[0][8] = "b#";
  _Notes[0][9] = "C";

  for (int i = 0; i < ROWS; i++)
    for (int j = 0; j < COLS; j++)
    {
      QFrame *tFrame = new QFrame(this);
      tFrame->setFrameShape(QFrame::Box);
      tFrame->setLineWidth(2);
      tFrame->setFrameStyle(QFrame::Box | QFrame::Plain);
      if (i == 0 && j == 0)
      {
        tFrame->setContentsMargins(2,2,2,2);
tFrame->setPalette(QPalette(Qt::blue));
tFrame->setAutoFillBackground(true);
      }
      else if (i == 0)
      {
        tFrame->setContentsMargins(0,2,2,2);
      }
      else if (j == 0)
      {
        tFrame->setContentsMargins(2,0,2,2);
      }
      else
      {
        tFrame->setContentsMargins(0,0,2,2);
      }
tFrame->setSizePolicy(QSizePolicy::MinimumExpanding,
                     QSizePolicy::MinimumExpanding);


      tFrame->setMinimumSize(QSize(60,20));

//      char buff[100];
//      sprintf(buff,"hello %d,%d",i,j);
      QLabel *tLabel = new QLabel(_Notes[i][j],tFrame);
//      tLabel->setIndent(30);
      tLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight | Qt::AlignAbsolute);
//      tLabel->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
      tLabel->setPalette(QPalette(Qt::gray));
      tLabel->setAutoFillBackground(true);
tLabel->setMinimumWidth(60);
tLabel->setContentsMargins(0,0,0,0);
tLabel->setSizePolicy(QSizePolicy::MinimumExpanding,
                     QSizePolicy::MinimumExpanding);

QHBoxLayout *tBL = new QHBoxLayout(tFrame);
tBL->addWidget(tLabel);

      tGrid[i][j] = tFrame;
    }


//  _checkBox = new QCheckBox("CheckBox");
//
//  _label1 = new QLabel("SomeReallyReallyLongLabel",this);
//  _lineEdit1 = new QLineEdit();
//
//  _label2 = new QLabel("Label",this);
//  _lineEdit2 = new QLineEdit();

  QGridLayout *tGridLayout = new QGridLayout(this);
  tGridLayout->setHorizontalSpacing(0);
  tGridLayout->setVerticalSpacing(0);
tGridLayout->setContentsMargins(0,0,0,0);

  for (int i = 0; i < ROWS; i++)
    for (int j = 0; j < COLS; j++)
    {
      tGridLayout->addWidget(tGrid[i][j],i,j);
    }
//  tGridLayout->setRowStretch(1,0);
//  tGridLayout->setRowStretch(2,0);
//
//  tGridLayout->addWidget(_checkBox,0,0);
//  tGridLayout->addWidget(_label1,1,0);
//  tGridLayout->addWidget(_label2,2,0);
//
//  tGridLayout->addWidget(_lineEdit1,1,1);
//  tGridLayout->addWidget(_lineEdit2,2,1);
//
//  QWidget *tEditorsWidget = new QWidget(this);
//  tEditorsWidget->setLayout(tGridLayout);
//
//
//  QPushButton *tSendButton = new QPushButton(QString("Send"),this);
//  tSendButton->resize(100, 30);
//
//  QObject::connect( tSendButton, SIGNAL(clicked()), this, SLOT(onSend()) );

  QWidget *tEditorsWidget = new QWidget(this);
  tEditorsWidget->setLayout(tGridLayout);

  QHBoxLayout *tBoxLayout = new QHBoxLayout(this);
//  tBoxLayout->setStretch(0,0);
//  tBoxLayout->setStretch(1,1);
//  tBoxLayout->addWidget(tEditorsWidget);
//  tBoxLayout->addWidget(tSendButton);
  tBoxLayout->addWidget(tEditorsWidget);

//  resize(200,120);

  setLayout(tBoxLayout);
#endif
#endif
}
