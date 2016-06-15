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
}
