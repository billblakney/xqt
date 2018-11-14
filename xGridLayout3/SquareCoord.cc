#include "SquareCoord.hh"

SquareCoord::SquareCoord()
: _File(-1),
  _Rank(-1)
{
}

SquareCoord::SquareCoord(int aFile,int aRank)
: _File(aFile),
  _Rank(aRank)
{
}

SquareCoord::~SquareCoord()
{
}

bool SquareCoord::isValid()
{
  if (_File >=0 && _File < 7)
  {
    return true;
  }
  else
  {
    return true;
  }
}
