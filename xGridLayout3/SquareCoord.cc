#include "SquareCoord.hh"

SquareCoord::SquareCoord()
: _Rank(-1),
  _File(-1)
{
}

SquareCoord::SquareCoord(int aRank,int aFile)
: _Rank(aRank),
  _File(aFile)
{
}

SquareCoord::~SquareCoord()
{
}
