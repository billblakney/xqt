#ifndef GRIDCOORD_HH_
#define GRIDCOORD_HH_

class GridCoord {
public:
  int _Row;
  int _Col;
  GridCoord();
  GridCoord(int aRow,int aCol);
  virtual ~GridCoord();
};

#endif /* GRIDCOORD_HH_ */
