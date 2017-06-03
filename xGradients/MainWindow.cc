#include <cstdio>
#include <iostream>
#include <QString>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLinearGradient>
#include <QPalette>
#include <QPointF>
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

//void MainWindow::onSend()
//{
//  std::cout << "onSend" << std::endl;
//  QString tChecked = "false";
//  if (_checkBox->checkState() == Qt::Checked)
//  {
//    tChecked = "true";
//  }
//  std::cout << "_checkBox: " << qPrintable(tChecked) << std::endl;
//  std::cout << "_lineEdit1: " << qPrintable(_lineEdit1->text()) << std::endl;
//  std::cout << "_lineEdit2: " << qPrintable(_lineEdit2->text()) << std::endl;
//}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
QPushButton *MainWindow::createButton1()
{
  QPushButton *tButton = new QPushButton(QString("Button1"),this);

  tButton->setFlat(true);
  tButton->setAutoFillBackground(true);

  QPalette tPalette = tButton->palette();
  tPalette.setBrush(QPalette::Active, QPalette::Button,QBrush(Qt::red));
  tPalette.setBrush(QPalette::Active, QPalette::Button,QBrush(Qt::red));
  tPalette.setBrush(QPalette::Inactive, QPalette::Button,QBrush(Qt::blue));

  tButton->setPalette(tPalette);

  return tButton;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
QPushButton *MainWindow::createButton2()
{
  return new QPushButton(QString("Button2"),this);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
QPushButton *MainWindow::createButton3()
{
  return NULL;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MainWindow::setupView()
{
  std::cout << "setupView" << std::endl;

  _DefaultButton = new QPushButton(QString("Default"),this);

  _button1 = createButton1();
  _button2 = createButton2();

  QPalette tPalette = _button1->palette();
  tPalette.setColor(QPalette::Window, Qt::blue);
  tPalette.setBrush(QPalette::Window, Qt::red);
  tPalette.setBrush(QPalette::Button, Qt::green);

  QBrush tBrushRed(Qt::red);
  tBrushRed.setStyle(Qt::SolidPattern);

  tPalette.setBrush(QPalette::Active, QPalette::Button, tBrushRed);
  tPalette.setBrush(QPalette::Inactive, QPalette::Button, tBrushRed);
  tPalette.setBrush(QPalette::Disabled, QPalette::Button, tBrushRed);

  QBrush tBrushCyan(Qt::cyan);
  tBrushCyan.setStyle(Qt::SolidPattern);

  tPalette.setBrush(QPalette::Active, QPalette::Window, tBrushCyan);
  tPalette.setBrush(QPalette::Inactive, QPalette::Window, tBrushCyan);
  tPalette.setBrush(QPalette::Disabled, QPalette::Window, tBrushCyan);

  _button3 = new QPushButton(QString("Button3"),this);
  _button3->setFlat(true);
  _button3->setAutoFillBackground(true);
_button3->setCheckable(true);

  QLinearGradient tGradient(QPointF(0,0),QPointF(0,1));
  tGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
//  QLinearGradient tGradient(QPointF(0,0),QPointF(50,50));
  tGradient.setColorAt(0,Qt::yellow);
  tGradient.setColorAt(1,Qt::blue);

//  tPalette.setBrush(QPalette::Window, QBrush(tGradient));
//  tPalette.setBrush(QPalette::Button, QBrush(tGradient));
//  tPalette.setBrush(QPalette::ButtonText, QBrush(tGradient));

//  tPalette.setColor(QPalette::WindowText, Qt::yellow);

  QPalette tPaletteG = _button3->palette();
//  tPaletteG.setBrush(_button1->backgroundRole(),tGradient);
//  tPaletteG.setBrush(_button1->foregroundRole(),tGradient);
//  tPaletteG.setColor(_button1->backgroundRole(), Qt::yellow);
//  tPaletteG.setColor(_button1->foregroundRole(), Qt::yellow);
  tPaletteG.setBrush(QPalette::Button,tGradient);
  tPaletteG.setBrush(QPalette::Button,tGradient);
//  tPaletteG.setColor(QPalette::Button, Qt::yellow);
//  tPaletteG.setColor(QPalette::Button, Qt::yellow);

  _button3->setPalette(tPaletteG);
  _button3->update();

  setPalette(tPalette);


  QVBoxLayout *tBoxLayout = new QVBoxLayout(this);
  tBoxLayout->addWidget(_DefaultButton);
  tBoxLayout->addWidget(_button1);
  tBoxLayout->addWidget(_button2);
  tBoxLayout->addWidget(_button3);

#if 0
  _checkBox = new QCheckBox("CheckBox");

  _label1 = new QLabel("SomeReallyReallyLongLabel",this);
  _lineEdit1 = new QLineEdit();

  _label2 = new QLabel("Label",this);
  _lineEdit2 = new QLineEdit();

  QVGridLayout *tGridLayout = new QGridLayout(this);
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
#endif

//  resize(200,120);

  setLayout(tBoxLayout);
}
