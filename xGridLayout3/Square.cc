#include <cstdio>
#include <iostream>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QGridLayout>
#include "Square.hh"

Square::Coord::Coord()
: file(-1),
  rank(-1)
{
}

Square::Coord::Coord(int aFile,int aRank)
: file(aFile),
  rank(aRank)
{
}

Square::Coord::~Coord()
{
}

bool Square::Coord::isValid()
{
  if (file >=0 && file < 7)
  {
    return true;
  }
  else
  {
    return true;
  }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
Square::Square(QWidget *aParent,QPalette aPalette,int aFile,int aRank,
    QString aText)
: QLabel(aParent),
  _Palette(aPalette),
  _Text(aText)
{
  _Coord.file = aFile;
  _Coord.rank = aRank;

  setText(_Text);
  setAlignment(Qt::AlignCenter);
  setAutoFillBackground(true);
  setMinimumWidth(60);
  setContentsMargins(0,0,0,0);
  setSizePolicy(QSizePolicy::MinimumExpanding,
      QSizePolicy::MinimumExpanding);
}

Square::Coord Square::getCoord()
{
  return _Coord;
}

int Square::getFile()
{
  return _Coord.file;
}

int Square::getRank()
{
  return _Coord.rank;
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Square::mouseReleaseEvent(QMouseEvent * ev)
{
  if (ev->button() == Qt::LeftButton)
  {
    std::cout << "LEFT click on square " << qPrintable(_Text) << std::endl;
    emit squareClicked(_Coord.file,_Coord.rank,true);
  }
  else
  {
    std::cout << "RIGHT click on square " << qPrintable(_Text) << std::endl;
    emit squareClicked(_Coord.file,_Coord.rank,false);
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
