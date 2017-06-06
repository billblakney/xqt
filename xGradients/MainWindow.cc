#include <cstdio>
#include <iostream>
#include <QString>
#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLinearGradient>
#include <QPalette>
#include <QPointF>
#include <QStyleFactory>
#include <QMotifStyle>
#include <vector>
#include "MainWindow.hh"
#include "TestStyle.hh"

//#define USE_FUNKY

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

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
QPalette MainWindow::getFunkyPalette(QPalette aPalette)
{
  QPalette tPalette = aPalette;

  QLinearGradient tButtonGrad(QPointF(0,0),QPointF(0,1));
  tButtonGrad.setCoordinateMode(QGradient::ObjectBoundingMode);
  tButtonGrad.setColorAt(0,Qt::cyan);
  tButtonGrad.setColorAt(0.67,Qt::gray);
  tButtonGrad.setColorAt(1.0,Qt::blue);

  tPalette.setBrush(QPalette::Button,tButtonGrad);

  QLinearGradient tMidGrad(QPointF(0,0),QPointF(0,1));
  tMidGrad.setCoordinateMode(QGradient::ObjectBoundingMode);
  tMidGrad.setColorAt(0,Qt::yellow);
  tMidGrad.setColorAt(0.67,Qt::green);
  tMidGrad.setColorAt(1.0,Qt::darkGreen);

  tPalette.setBrush(QPalette::Mid,tMidGrad);

  tPalette.setBrush(QPalette::Highlight,Qt::yellow);

  return tPalette;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
QPalette MainWindow::getSonarPalette(QPalette aPalette)
{
  static QColor _DefaultButtonBaseColor(0x2b2b2b); // "med jungle green"
  static QColor _DefaultButtonFadeColor(0x747474); // "old lavender"
  static QColor _DefaultButtonBorderColor(0x7a8a99); // "lt slate gray"
  static QColor _DefaultButtonCheckedColor(0x404040); // "payne's gray"
  static QColor _DefaultButtonTextColor(0xc0c0c0); // "silver"

  QPalette tPalette = aPalette;

  /*
   * Setup QPalette::Button brush, which is used for button background
   * when button is "normal", i.e. active and not pressed or checked
   */
  QLinearGradient tButtonGrad(QPointF(0,0),QPointF(0,1));
  tButtonGrad.setCoordinateMode(QGradient::ObjectBoundingMode);
  tButtonGrad.setColorAt(0,_DefaultButtonFadeColor);
  tButtonGrad.setColorAt(0.5,_DefaultButtonBaseColor);
  tButtonGrad.setColorAt(1,_DefaultButtonBaseColor);
  tPalette.setBrush(QPalette::Button,tButtonGrad);

  /*
   * Setup QPalette::Mid brush, which is used for button background
   * when button is pressed
   */
  tPalette.setBrush(QPalette::Mid,_DefaultButtonCheckedColor);

  /*
   * Setup QPalette::Text brush, which is used for button text
   */
  tPalette.setBrush(QPalette::ButtonText,_DefaultButtonTextColor);

  /*
   * Setup QPalette::WindowText brush, which is used for the focus rectangle
   * that goes around the label of the in-focus widget.
   */
  tPalette.setColor(QPalette::WindowText, Qt::white);

  /*
   * Setup QPalette::Highlight brush, which is used for...
   */
//  tPalette.setBrush(QPalette::Highlight,Qt::yellow);
//  tPalette.setBrush(QPalette::Shadow,Qt::yellow);
//  tPalette.setBrush(QPalette::Light,Qt::yellow);
//  tPalette.setBrush(QPalette::BrightText,Qt::yellow);

  tPalette.setBrush(QPalette::Light,Qt::blue); // bottom right focus rect
//  tPalette.setBrush(QPalette::Midlight,Qt::yellow);
  tPalette.setBrush(QPalette::Dark,Qt::yellow); // top, left focus rect
//  tPalette.setBrush(QPalette::Mid,Qt::yellow); set above
//  tPalette.setBrush(QPalette::Shadow,Qt::yellow);

  return tPalette;
}

//-----------------------------------------------------------------------------
// TODO may want to note this somewhere
// Note: Setting flat to false gives button bevel with thicker lighter gray
// on top and left sides, and darker gray on bottom and right sides.
// Note: If auto fill background is set to false, button background is not
// drawn in normal state (active, unpressed, unchecked), but is when pressed
// or checked.
//-----------------------------------------------------------------------------
#ifndef QT_V5
  QPushButton *MainWindow::createButton(
      QString aName,QStyle *aStyle,bool aIsCheckable)
#else
  QPushButton *MainWindow::createButton(QString aName,QString aStyle)
#endif
  {
    QPushButton *tButton = new QPushButton(aName,this);

#ifndef QT_V5
  tButton->setStyle(aStyle);
#else
  tButton->setStyle(QStyleFactor::create(aStyle);
#endif

  tButton->setPalette(getSonarPalette(tButton->palette()));
  tButton->setAutoFillBackground(true);
  tButton->setFlat(true);
  tButton->setCheckable(aIsCheckable);

  return tButton;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
QPushButton *MainWindow::createButtonWithColorGroups()
{
  QPushButton *tButton =
      new QPushButton(QString("Button Active/Inactive Palette"),this);

  tButton->setFlat(true);
  tButton->setAutoFillBackground(true);

  QPalette tPalette = tButton->palette();

  // when app window is in focus, Active palette is used
  tPalette.setBrush(QPalette::Active, QPalette::Button,QBrush(Qt::red));

  // when app window is not in focus, Inactive palette is used
  tPalette.setBrush(QPalette::Inactive, QPalette::Button,QBrush(Qt::gray));

  // When widget is disabled, Disabled palette is always used.
  tPalette.setBrush(QPalette::Disabled, QPalette::Button,QBrush(Qt::darkGray));
//  tButton->setEnabled(false); // disable the button

  tButton->setPalette(tPalette);

  return tButton;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MainWindow::setupView()
{
  /*
   * Create buttons.
   */
  std::vector<QPushButton *> tButtons;
  QPushButton *tButton = NULL;

  tButtons.push_back(new QPushButton(QString("Default"),this));

  tButton = new QPushButton(QString("Default Checkable"),this);
  tButton->setCheckable(true);
  tButtons.push_back(tButton);

  tButtons.push_back(createButton("SonarStyle Button #1",new TestStyle,false));
  tButtons.push_back(createButton("SonarStyle Button #2",new TestStyle,false));
  tButtons.push_back(createButton("SonarStyle Checkable Button #1",new TestStyle,true));
  tButtons.push_back(createButton("SonarStyle Checkable Button #2",new TestStyle,true));

  tButtons.push_back(createButton("MotifStyle Button",new QMotifStyle,false));
  tButtons.push_back(createButton("MotifStyle Button",new QMotifStyle,true));

  tButtons.push_back(createButtonWithColorGroups());

  /*
   * Add buttons to the layout.
   */
  QVBoxLayout *tBoxLayout = new QVBoxLayout(this);
  for (size_t i = 0; i < tButtons.size(); i++)
  {
    tBoxLayout->addWidget(tButtons[i]);
  }

  setLayout(tBoxLayout);

  /*
   * Set overall background.
   */
  QPalette pal = palette();
  // set black background
  pal.setColor(QPalette::Background, Qt::black);
  setAutoFillBackground(true);
  setPalette(pal);

//  resize(200,120);
}
