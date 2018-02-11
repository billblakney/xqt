#include "Square.hh"

Square::Square()
//  : _Row(0),
//    _Col(0),
//    _Rect(0)
{
  init();
}

void Square::init()
{
  _Row = 0;
  _Col = 0;
  _Rect = QRect();
  _PiecePixels = 0;
  for (int i = 0; i < Board::ROWS; i++)
    for (int j = 0; j < Board::COLS; j++)
    {
      _PieceDist[i][j] = 0;
    }
}

Square::Square(int aRow,int aCol,QRect aRect)
//  : _Row(aRow),
//    _Col(aCol),
//    _Rect(aRect)
{
  init();
  _Row = aRow;
  _Col = aCol;
//  _Rect = QRect();
  _Rect = QRect(aRect.topLeft(),aRect.bottomRight());
}

Square::~Square()
{
}

Square& Square::operator=(const Square& aSquare)
{
  if (this != &aSquare)
  {
    _Row = aSquare._Row;
    _Col = aSquare._Col;
    _Rect = QRect(aSquare._Rect.topLeft(),aSquare._Rect.bottomRight());
    _PiecePixels = 0;
    for (int i = 0; i < Board::ROWS; i++)
      for (int j = 0; j < Board::COLS; j++)
      {
        _PieceDist[i][j] = 0;
      }
  }
  return *this;
}

float Square::getWeight()
{
  return (float)_PiecePixels/(float)(_Rect.width()*_Rect.height());
}

std::string Square::toString()
{
  std::string tString;
//  std::string tString("Square (" + _Row + "," + _Col + ") weight=" + _Weight);
  return tString;
}

