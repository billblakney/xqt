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
