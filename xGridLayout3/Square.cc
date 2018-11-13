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
  setText(_Text);
  setAlignment(Qt::AlignCenter);
  setAutoFillBackground(true);
  setMinimumWidth(60);
  setContentsMargins(0,0,0,0);
  setSizePolicy(QSizePolicy::MinimumExpanding,
      QSizePolicy::MinimumExpanding);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
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
void Square::onClick()
{
  std::cout << "click on row,col = " << qPrintable(_Text) << "!!!!!!!!!!!!!!!" << std::endl;
}
