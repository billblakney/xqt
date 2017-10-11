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

  const int ROWS = 6;
  const int COLS = 10;
  QFrame *tGrid[ROWS][COLS];

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

      char buff[100];
      sprintf(buff,"hello %d,%d",i,j);
      QLabel *tLabel = new QLabel(buff,tFrame);
//      tLabel->setIndent(30);
      tLabel->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
//      tLabel->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
      tLabel->setPalette(QPalette(Qt::gray));
      tLabel->setAutoFillBackground(true);
tLabel->setMinimumWidth(60);
tLabel->setContentsMargins(0,0,0,0);
tLabel->setSizePolicy(QSizePolicy::MinimumExpanding,
                     QSizePolicy::MinimumExpanding);

QVBoxLayout *tBL = new QVBoxLayout(tFrame);
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
