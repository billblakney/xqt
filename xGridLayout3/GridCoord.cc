#include "GridCoord.hh"

GridCoord::GridCoord()
: _Row(-1),
  _Col(-1)
{
}

GridCoord::GridCoord(int aRow,int aCol)
: _Row(aRow),
  _Col(aCol)
{
}

GridCoord::~GridCoord()
{
}
