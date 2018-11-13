#include <cstdio>
#include <iostream>
#include <QString>
#include <QVBoxLayout>
#include <QGridLayout>
#include "MainWindow.hh"
#include "Square.hh"

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
  std::cout << "setupView" << std::endl;
  setMinimumSize(QSize(640,600));

//  const int RANKS = 8;
  const int FILES = 8;
  QFrame *tGrid[RANKS][FILES];

  QPalette tBlackPalette = palette();
//  tBlackPalette.setColor(QPalette::Background, Qt::black);
  tBlackPalette.setColor(QPalette::Background, QColor(90,90,90));
  tBlackPalette.setColor(QPalette::Foreground, Qt::white);
  QPalette tWhitePalette = palette();
  tWhitePalette.setColor(QPalette::Background, Qt::white);
  tWhitePalette.setColor(QPalette::Foreground, Qt::black);

  for (int i = 0; i < RANKS; i++)
    for (int j = 0; j < FILES; j++)
    {
std::cout << "Adding _Squares[" << i << ", " << j << "]" <<std::endl;
      Square *tSquare = new Square(this,tWhitePalette,i,j,
          _FileNames[i] + _RankNames[j]);
      _Squares[i][j] = tSquare;
    }

  QGridLayout *tGridLayout = new QGridLayout(this);
  tGridLayout->setHorizontalSpacing(0);
  tGridLayout->setVerticalSpacing(0);
  tGridLayout->setContentsMargins(0,0,0,0);

  for (int i = 0; i < RANKS; i++)
    for (int j = 0; j < FILES; j++)
    {
#define TO_FRAME
#ifdef TO_FRAME
  // frame shape/style
      QFrame *tFrame = new QFrame(this);
  tFrame->setFrameShape(QFrame::Box);
  tFrame->setLineWidth(20);
  tFrame->setFrameStyle(QFrame::Box | QFrame::Plain);

  // frame size
  tFrame->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);

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
#endif
#ifdef TO_FRAME
  QVBoxLayout *tBL = new QVBoxLayout(tFrame);
  tBL->setContentsMargins(0,0,0,0);
  tBL->addWidget(_Squares[i][j]);
#endif
std::cout << "Adding to layout " << i << ", " << j <<std::endl;
//      tGridLayout->addWidget(tGrid[i][j],RANKS-1-i,j);
      tGridLayout->addWidget(tFrame,RANKS-1-i,j);
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
}
