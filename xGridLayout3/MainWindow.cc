#include <cstdio>
#include <iostream>
#include <QString>
#include <QVBoxLayout>
#include <QGridLayout>
#include "MainWindow.hh"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *aParent)
: QWidget(aParent)
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
}

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

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MainWindow::setupView()
{
setMinimumSize(QSize(640,600));
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

  QVBoxLayout *tBoxLayout = new QVBoxLayout(this);
  tBoxLayout->setStretch(0,0);
  tBoxLayout->setStretch(1,1);
  tBoxLayout->addWidget(tEditorsWidget);
  tBoxLayout->addWidget(tSendButton);

//  resize(200,120);

  setLayout(tBoxLayout);
#else
  std::cout << "setupView" << std::endl;


  const int ROWS = 8;
  const int COLS = 8;
  QFrame *tGrid[ROWS][COLS];

  QPalette tBlackPalette = palette();
//  tBlackPalette.setColor(QPalette::Background, Qt::black);
  tBlackPalette.setColor(QPalette::Background, QColor(90,90,90));
  tBlackPalette.setColor(QPalette::Foreground, Qt::white);
  QPalette tWhitePalette = palette();
  tWhitePalette.setColor(QPalette::Background, Qt::white);
  tWhitePalette.setColor(QPalette::Foreground, Qt::black);

  QString _Notes[ROWS][COLS];
  for (int i = 0; i < ROWS; i++)
    for (int j = 0; j < COLS; j++)
    {
      _Notes[i][j] = "x";
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

      // frame shape/style
      tFrame->setFrameShape(QFrame::Box);
      tFrame->setLineWidth(20);
      tFrame->setFrameStyle(QFrame::Box | QFrame::Plain);

      // frame size
      tFrame->setSizePolicy(QSizePolicy::MinimumExpanding,
          QSizePolicy::MinimumExpanding);

      tFrame->setMinimumSize(QSize(60,60));

      if (i == 0 && j == 0)
      {
        tFrame->setContentsMargins(2,2,2,2);
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
#define SHOW_HIGHLIGHTED_MARGIN
#ifdef SHOW_HIGHLIGHTED_MARGIN
      if (i == 0 && j == 0)
      {
        tFrame->setPalette(QPalette(Qt::blue));
        tFrame->setContentsMargins(10,10,10,10);
        tFrame->setAutoFillBackground(true);
      }
#endif

      QLabel *tLabel = new QLabel(_Notes[i][j],tFrame);
      tLabel->setAlignment(Qt::AlignCenter);
      if ((i+j)%2 == 0)
      {
        tLabel->setPalette(tWhitePalette);
      }
      else
      {
//        tLabel->setPalette(tBlackPalette);
        tLabel->setPalette(tWhitePalette);
      }
      tLabel->setAutoFillBackground(true);
tLabel->setMinimumWidth(60);
tLabel->setContentsMargins(0,0,0,0);
tLabel->setSizePolicy(QSizePolicy::MinimumExpanding,
                     QSizePolicy::MinimumExpanding);

QVBoxLayout *tBL = new QVBoxLayout(tFrame);
//tBL->setHorizontalSpacing(0);
//tBL->setVerticalSpacing(0);
tBL->setContentsMargins(0,0,0,0);
tBL->addWidget(tLabel);

      tGrid[i][j] = tFrame;
//      tGrid[i][j] = tLabel;
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

  QVBoxLayout *tBoxLayout = new QVBoxLayout(this);
//  tBoxLayout->setStretch(0,0);
//  tBoxLayout->setStretch(1,1);
//  tBoxLayout->addWidget(tEditorsWidget);
//  tBoxLayout->addWidget(tSendButton);
  tBoxLayout->addWidget(tEditorsWidget);

//  resize(200,120);

  setLayout(tBoxLayout);
#endif
}
