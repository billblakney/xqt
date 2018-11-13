#ifndef SQUARECOORD_HH_
#define SQUARECOORD_HH_

class SquareCoord {
public:
  int _Rank;
  int _File;
  SquareCoord();
  SquareCoord(int aRank,int aFile);
  virtual ~SquareCoord();
};

#endif /* SQUARECOORD_HH_ */
