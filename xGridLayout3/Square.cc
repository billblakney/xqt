#include <cstdio>
#include <iostream>
#include <QVBoxLayout>
#include <QGridLayout>
#include "Square.hh"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
Square::Square(QWidget *aParent,QPalette aPalette,int aRow,int aCol,
    std::string aLabel)
: QFrame(aParent),
  _Row(aRow),
  _Col(aCol),
  _Palette(aPalette),
  _LabelText(aLabel)
{
  // frame shape/style
  setFrameShape(QFrame::Box);
  setLineWidth(20);
  setFrameStyle(QFrame::Box | QFrame::Plain);

  // frame size
  setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);

  setMinimumSize(QSize(60,60));

  if (_Row == 0 && _Col == 0)
  {
    setContentsMargins(2,2,2,2);
  }
  else if (_Row == 0)
  {
    setContentsMargins(0,2,2,2);
  }
  else if (_Col == 0)
  {
    setContentsMargins(2,0,2,2);
  }
  else
  {
    setContentsMargins(0,0,2,2);
  }
#define SHOW_HIGHLIGHTED_MARGIN
#ifdef SHOW_HIGHLIGHTED_MARGIN
  if (_Row == 0 && _Col == 0)
  {
    setPalette(QPalette(Qt::blue));
    setContentsMargins(10,10,10,10);
    setAutoFillBackground(true);
  }
#endif

  _Label.setText(QString(_LabelText.c_str()));
  _Label.setAlignment(Qt::AlignCenter);
  _Label.setAutoFillBackground(true);
  _Label.setMinimumWidth(60);
  _Label.setContentsMargins(0,0,0,0);
  _Label.setSizePolicy(QSizePolicy::MinimumExpanding,
      QSizePolicy::MinimumExpanding);

  QVBoxLayout *tBL = new QVBoxLayout(this);
  tBL->setContentsMargins(0,0,0,0);
  tBL->addWidget(&_Label);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
Square::~Square()
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Square::onClick()
{
  std::cout << "ononClick" << std::endl;
//  std::cout << "_checkBox: " << qPrintable(tChecked) << std::endl;
//  std::cout << "_lineEdit1: " << qPrintable(_lineEdit1->text()) << std::endl;
}
