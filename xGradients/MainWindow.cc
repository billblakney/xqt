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
#ifdef QT_V5
#else
//#include <QCDEStyle>
//#include <QCleanlooksStyle>
//#include <QCommonStyle>
//#include <QGtkStyle>
//#include <QMacStyle>
//#include <QMotifStyle>
//#include <QPlastiqueStyle>
//#include <QProxyStyle>
//#include <QS60Style>
//#include <QStyle>
//#include <QWindowsCEStyle>
//#include <QWindowsMobileStyle>
//#include <QWindowsStyle>
//#include <QWindowsVistaStyle>
//#include <QWindowsXPStyle>

#include <QWindowsStyle>
#endif
#include <vector>
#include "MainWindow.hh"
#include "TestStyle.hh"

//-----------------------------------------------------------------------------
// TODO may want to note this somewhere
// Note: Setting flat to false gives button bevel with thicker lighter gray
// on top and left sides, and darker gray on bottom and right sides.
// Note: If auto fill background is set to false, button background is not
// drawn in normal state (active, unpressed, unchecked), but is when pressed
// or checked.
//-----------------------------------------------------------------------------

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
  static QColor _DefaultButtonHoverColor(0xb8cfe5); // "beau blue"
  static QColor _DefaultDisabledButtonBaseColor(0x202020); // "onyx"
  static QColor _DefaultDisabledButtonTextColor(0x999999); // "manatee"
  static QColor _DefaultDisabledButtonBorderColor(0x424242); // "dim gray"

  /*
   * The palette for a default push button.
   * Brushes are set as follows:
   * - QPalette::Button = background active, unchecked button
   * - QPalette::ButtonText = text label
   * - QPalette::Mid = background for pressed or checked button
   * - QPalette::Midlight = button border
   * - QPalette::WindowText = focus rectangle around button text
   * - QPalette::Highlight = hover highlight (the hover button border actually
   *   uses a combination of this and Midlight)
   */

  QPalette tPalette = aPalette;

  QLinearGradient tButtonGrad(QPointF(0,0),QPointF(0,1));
  tButtonGrad.setCoordinateMode(QGradient::ObjectBoundingMode);
  tButtonGrad.setColorAt(0,_DefaultButtonFadeColor);
  tButtonGrad.setColorAt(0.5,_DefaultButtonBaseColor);
  tButtonGrad.setColorAt(1,_DefaultButtonBaseColor);

  tPalette.setBrush(QPalette::Button,tButtonGrad);
  tPalette.setBrush(QPalette::Mid,_DefaultButtonCheckedColor);
  tPalette.setBrush(QPalette::ButtonText,_DefaultButtonTextColor);
  tPalette.setColor(QPalette::Midlight,_DefaultButtonBorderColor);
  tPalette.setColor(QPalette::WindowText,Qt::white);
  tPalette.setColor(QPalette::Highlight,_DefaultButtonHoverColor);

  tPalette.setBrush(QPalette::Disabled,QPalette::Button,_DefaultDisabledButtonBaseColor);
  tPalette.setBrush(QPalette::Disabled,QPalette::ButtonText,_DefaultDisabledButtonBorderColor);
  tPalette.setColor(QPalette::Disabled,QPalette::Midlight,_DefaultDisabledButtonBorderColor);

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
//-----------------------------------------------------------------------------
  QPushButton *MainWindow::createButton(
      QString aName,QStyle *aStyle,bool aIsCheckable)
  {
    QPushButton *tButton = new QPushButton(aName,this);

  tButton->setStyle(aStyle);

  tButton->setPalette(getSonarPalette(tButton->palette()));
  tButton->setAutoFillBackground(true);
  tButton->setFlat(true);
  tButton->setCheckable(aIsCheckable);

  tButton->setAttribute(Qt::WA_Hover);

  return tButton;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#ifdef QT_V5
  QPushButton *MainWindow::createButton(
      QString aName,QString aStyle,bool aIsCheckable)
  {
    QPushButton *tButton = new QPushButton(aName,this);

  tButton->setStyle(QStyleFactory::create(aStyle));

  tButton->setPalette(getSonarPalette(tButton->palette()));
  tButton->setAutoFillBackground(true);
  tButton->setFlat(true);
  tButton->setCheckable(aIsCheckable);

  tButton->setAttribute(Qt::WA_Hover);

  return tButton;
}
#endif

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

#ifdef QT_V5
#else
  tButtons.push_back(new QPushButton(QString("Default"),this));
  tButtons[tButtons.size()-1]->setStyle(new QWindowsStyle);
#endif

  tButton = new QPushButton(QString("Default Checkable"),this);
  tButton->setCheckable(true);
  tButtons.push_back(tButton);

  tButtons.push_back(createButton("SonarStyle Button #1",new TestStyle,false));
  tButtons[tButtons.size()-1]->setEnabled(false);
  tButtons.push_back(createButton("SonarStyle Button #2",new TestStyle,false));
  tButtons.push_back(createButton("SonarStyle Checkable Button #1",new TestStyle,true));
  tButtons.push_back(createButton("SonarStyle Checkable Button #2",new TestStyle,true));

#ifdef QT_V5
  tButtons.push_back(createButton(
      "MotifStyle Button",QStyleFactory::create("motif"),false));
  tButtons.push_back(createButton(
      "MotifStyle Button",QStyleFactory::create("motif"),true));
#else
  tButtons.push_back(createButton("MotifStyle Button",new QMotifStyle,false));
  tButtons.push_back(createButton("MotifStyle Button",new QMotifStyle,true));
#endif

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
/*
 * Style classes on Dell laptop ubuntu:
 *
 ******* /usr/include/qt5/QWidgets *****
 * QProxyStyle
 * QCommonStyle
 * QStyle
 *
 ******* at/usr/include/qt4/QtGui *****
 * QProxyStyle
 * QWindowsStyle
 * QWindowsMobileStyle
 * QWindowsVistaStyle
 * QWindowsXPStyle
 * QGtkStyle
 * QCommonStyle
 * QCleanlooksStyle
 * QStyle
 * QWindowsCEStyle
 * QCDEStyle
 * QMacStyle
 * QMotifStyle
 * QPlastiqueStyle
 * QS60Style
*/
