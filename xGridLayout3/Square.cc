#include <cstdio>
#include <iostream>
#include <QVBoxLayout>
#include <QGridLayout>
#include "Square.hh"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
Square::Square(QWidget *aParent,QPalette aPalette,int aRow,int aCol,
    QString aText)
: QFrame(aParent),
  _Row(aRow),
  _Col(aCol),
  _Palette(aPalette),
  _Text(aText)
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

  _Label.setText(_Text);
  _Label.setAlignment(Qt::AlignCenter);
  _Label.setAutoFillBackground(true);
  _Label.setMinimumWidth(60);
  _Label.setContentsMargins(0,0,0,0);
  _Label.setSizePolicy(QSizePolicy::MinimumExpanding,
      QSizePolicy::MinimumExpanding);

  QVBoxLayout *tBL = new QVBoxLayout(this);
  tBL->setContentsMargins(0,0,0,0);
  tBL->addWidget(&_Label);

//      QObject::connect(&_Label,SIGNAL(clicked()),this, SLOT(onClick()) );
}

void Square::mouseReleaseEvent(QMouseEvent * ev)
{
  std::cout << "click on row,col = " << qPrintable(_Text) << "!!!!!!!!!!!!!!!" << std::endl;
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
