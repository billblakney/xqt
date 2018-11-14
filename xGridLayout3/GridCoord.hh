#ifndef GRIDCOORD_HH_
#define GRIDCOORD_HH_

class GridCoord {
public:
  int _x;
  int _y;
  GridCoord();
  GridCoord(int aX,int aY);
  virtual ~GridCoord();
};

#endif /* GRIDCOORD_HH_ */
