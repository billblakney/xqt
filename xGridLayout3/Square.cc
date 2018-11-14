#include <cstdio>
#include <iostream>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QGridLayout>
#include "Square.hh"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
Square::Square(QWidget *aParent,QPalette aPalette,int aFile,int aRank,
    QString aText)
: QLabel(aParent),
  _File(aFile),
  _Rank(aRank),
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
    std::cout << "LEFT click on square " << qPrintable(_Text) << std::endl;
    emit squareClicked(_File,_Rank,true);
  }
  else
  {
    std::cout << "RIGHT click on square " << qPrintable(_Text) << std::endl;
    emit squareClicked(_File,_Rank,false);
  }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
Square::~Square()
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Square::setPalette(QPalette aPalette)
{
  _Palette = aPalette;
  QLabel::setPalette(aPalette);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Square::onClick()
{
  std::cout << "click on file,rank = " << qPrintable(_Text) << "!!!!!!!!!!!!!!!" << std::endl;
}
