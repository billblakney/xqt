#include <cstdio>
#include <iostream>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QGridLayout>
#include "Square.hh"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
Square::Square(QWidget *aParent,QPalette aPalette,int aRow,int aCol,
    QString aText)
: QLabel(aParent),
  _Row(aRow),
  _Col(aCol),
  _Palette(aPalette),
  _Text(aText)
{
#ifdef TO_FRAME
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
#endif

//  _Label.setText(_Text);
//  _Label.setAlignment(Qt::AlignCenter);
//  _Label.setAutoFillBackground(true);
//  _Label.setMinimumWidth(60);
//  _Label.setContentsMargins(0,0,0,0);
//  _Label.setSizePolicy(QSizePolicy::MinimumExpanding,
//      QSizePolicy::MinimumExpanding);

  setText(_Text);
  setAlignment(Qt::AlignCenter);
  setAutoFillBackground(true);
  setMinimumWidth(60);
  setContentsMargins(0,0,0,0);
  setSizePolicy(QSizePolicy::MinimumExpanding,
      QSizePolicy::MinimumExpanding);

#ifdef TO_FRAME
  QVBoxLayout *tBL = new QVBoxLayout(this);
  tBL->setContentsMargins(0,0,0,0);
  tBL->addWidget(&_Label);
#endif
}

void Square::mouseReleaseEvent(QMouseEvent * ev)
{
  if (ev->button() == Qt::LeftButton)
  {
    std::cout << "LEFT click on row,col = " << qPrintable(_Text) << "!!!!!!!!!!!!!!!" << std::endl;
  }
  else
  {
    std::cout << "RIGHT click on row,col = " << qPrintable(_Text) << "!!!!!!!!!!!!!!!" << std::endl;
  }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
Square::~Square()
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
QLabel *Square::getLabel()
{
  return &_Label;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Square::onClick()
{
  std::cout << "click on row,col = " << qPrintable(_Text) << "!!!!!!!!!!!!!!!" << std::endl;
//  std::cout << "_checkBox: " << qPrintable(tChecked) << std::endl;
//  std::cout << "_lineEdit1: " << qPrintable(_lineEdit1->text()) << std::endl;
}
